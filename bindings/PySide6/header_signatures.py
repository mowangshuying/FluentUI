"""Parse the FluentUI C++ headers to recover the types runtime introspection loses.

Shiboken exposes structure (which classes and members exist) but almost never a
usable Python signature, so a runtime-only stub ends up ~99.7% ``-> Any``. The
C++ headers do carry the real types, so this module is the second input of
``generate_stubs.py``: introspection decides *what* exists, headers decide *what
type* it has.

The scanner is brace/paren aware and multiline, because these headers define a
lot of methods inline -- a signature ends with ``)`` followed by a ``{}`` body,
not with ``;``. Class bodies are descended into (not skipped), while function
bodies are skipped. Qt macros (``Q_OBJECT``, ``Q_PROPERTY(...)``) carry no
trailing semicolon, so they are flushed on their own line.
"""

import os
import re

# C++ scalar / well-known types -> Python. None means "returns None".
SCALARS = {
    "void": None,
    "bool": "bool",
    "char": "str",
    "int": "int",
    "short": "int",
    "long": "int",
    "uint": "int",
    "ulong": "int",
    "qint8": "int",
    "qint16": "int",
    "qint32": "int",
    "qint64": "int",
    "quint8": "int",
    "quint16": "int",
    "quint32": "int",
    "quint64": "int",
    "size_t": "int",
    "float": "float",
    "double": "float",
    "qreal": "float",
    "QString": "str",
    "QChar": "str",
    "QStringList": "list[str]",
    "QVariant": "Any",
    "QUrl": "str",
    "QByteArray": "bytes",
    "QJsonObject": "dict[str, Any]",
    "QJsonArray": "list[Any]",
    "QJsonValue": "Any",
}

# Types that must be imported from a concrete PySide6 module.
QT_MODULES = {
    "QAction": "PySide6.QtGui",
    "QBrush": "PySide6.QtGui",
    "QColor": "PySide6.QtGui",
    "QFont": "PySide6.QtGui",
    "QIcon": "PySide6.QtGui",
    "QKeyEvent": "PySide6.QtGui",
    "QMouseEvent": "PySide6.QtGui",
    "QPaintEvent": "PySide6.QtGui",
    "QPainter": "PySide6.QtGui",
    "QPen": "PySide6.QtGui",
    "QPixmap": "PySide6.QtGui",
    "QPoint": "PySide6.QtCore",
    "QPolygon": "PySide6.QtGui",
    "QWheelEvent": "PySide6.QtGui",
    "QDate": "PySide6.QtCore",
    "QDateTime": "PySide6.QtCore",
    "QEvent": "PySide6.QtCore",
    "QMargins": "PySide6.QtCore",
    "QObject": "PySide6.QtCore",
    "QRect": "PySide6.QtCore",
    "QSize": "PySide6.QtCore",
    "QString": "PySide6.QtCore",
    "Qt": "PySide6.QtCore",
    "QTime": "PySide6.QtCore",
    "QTimer": "PySide6.QtCore",
    "QVariant": "PySide6.QtCore",
    "QAbstractButton": "PySide6.QtWidgets",
    "QHBoxLayout": "PySide6.QtWidgets",
    "QLabel": "PySide6.QtWidgets",
    "QLayout": "PySide6.QtWidgets",
    "QListView": "PySide6.QtWidgets",
    "QMenu": "PySide6.QtWidgets",
    "QMessageBox": "PySide6.QtWidgets",
    "QPushButton": "PySide6.QtWidgets",
    "QScrollArea": "PySide6.QtWidgets",
    "QVBoxLayout": "PySide6.QtWidgets",
    "QWidget": "PySide6.QtWidgets",
}

CONTAINERS = {
    "QList": "list",
    "QVector": "list",
    "std::vector": "list",
    "QSet": "set",
    "QMap": "dict",
    "QHash": "dict",
    "std::map": "dict",
    "std::unordered_map": "dict",
}

_ACCESS = re.compile(
    r"^[ \t]*(public|protected|private|signals|slots|Q_SLOTS|Q_SIGNALS|Q_SLOT)"
    r"[ \t]*(\([^)]*\))?[ \t]*:",
    re.M,
)
_COMMENT_BLOCK = re.compile(r"/\*.*?\*/", re.S)
_COMMENT_LINE = re.compile(r"//[^\n]*")
_PREPROCESSOR = re.compile(r"^[ \t]*#[^\n]*", re.M)
_Q_PROPERTY = re.compile(
    r"Q_PROPERTY\s*\(\s*(.+?)\s+(\w+)\s+(?:READ|WRITE|MEMBER|CONSTANT)\b", re.S)
_TEMPLATE = re.compile(r"^([A-Za-z_][\w:]*)\s*<(.*)>$", re.S)
_MACRO_LINE = re.compile(r"^(?:Q_\w+\s*\(.*\)|Q_OBJECT|Q_SLOTS|Q_SIGNALS)$", re.S)

_NOISE_WORDS = {"friend", "using", "typedef", "namespace", "static_assert",
                "Q_DISABLE", "template", "explicit operator"}


def _strip_noise(text):
    text = _COMMENT_BLOCK.sub(" ", text)
    text = _COMMENT_LINE.sub(" ", text)
    text = _PREPROCESSOR.sub("", text)

    def replace(match):
        raw = match.group(0)
        if "signals" in raw or "Q_SIGNALS" in raw:
            kind = "signals"
        elif "slots" in raw or "Q_SLOT" in raw:
            kind = "slots"
        else:
            kind = match.group(1)
        return "\n@@ACCESS:%s@@\n" % kind

    return _ACCESS.sub(replace, text)


def _split_top_level(text, separator=","):
    parts, depth, current = [], 0, []
    for char in text:
        if char in "(<[":
            depth += 1
        elif char in ")>]":
            depth -= 1
        if char == separator and depth == 0:
            parts.append("".join(current))
            current = []
        else:
            current.append(char)
    if "".join(current).strip():
        parts.append("".join(current))
    return parts


def _skip_block(text, start):
    """Index just past the brace block that opens at `start`."""
    depth = 0
    index = start
    while index < len(text):
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return index + 1
        index += 1
    return index


def _units(text):
    """Yield (kind, payload): class / enum / body / decl / endclass.

    `body` is the signature of a function whose inline body followed it.
    """
    index, length = 0, len(text)
    buffer = []
    paren = 0
    while index < length:
        char = text[index]
        if char == "(":
            paren += 1
            buffer.append(char)
        elif char == ")":
            paren = max(0, paren - 1)
            buffer.append(char)
        elif char == "\n" and paren == 0:
            statement = "".join(buffer).strip()
            if statement.startswith("@@ACCESS:") or _MACRO_LINE.match(statement):
                buffer = []
                yield "decl", statement
            else:
                buffer.append(char)
        elif char == "{" and paren == 0:
            statement = " ".join("".join(buffer).split())
            buffer = []
            if re.match(r"^(?:/\*\s*)?enum\b", statement):
                index = _skip_block(text, index)
                yield "enum", statement
            elif re.search(r"\b(class|struct)\b", statement) and "(" not in statement:
                # enter the class body instead of skipping it
                yield "class", statement
                index += 1
            elif re.search(r"\b(namespace)\b", statement):
                index = _skip_block(text, index)
                yield "namespace", statement
            else:
                index = _skip_block(text, index)
                if statement:
                    yield "body", statement
            continue
        elif char == "}" and paren == 0:
            statement = "".join(buffer).strip()
            buffer = []
            if statement:
                yield "decl", statement
            yield "endclass", ""
        elif char == ";" and paren == 0:
            statement = "".join(buffer).strip()
            buffer = []
            if statement:
                yield "decl", statement
        else:
            buffer.append(char)
        index += 1
    tail = "".join(buffer).strip()
    if tail:
        yield "decl", tail


def map_type(cpp_type, imports, nullable=False):
    """Translate one C++ type spelling into a Python annotation."""
    if cpp_type is None:
        return "Any"
    base = " ".join(cpp_type.split())
    if not base:
        return "None"

    pointer = "*" in base
    base = re.sub(r"\bconst\b", " ", base)
    base = base.replace("*", " ").replace("&", " ")
    base = " ".join(base.split())
    if not base or base in _NOISE_WORDS:
        return "Any"

    template = _TEMPLATE.match(base)
    if template:
        outer, inner = template.group(1), template.group(2)
        if outer == "std::optional":
            return map_type(inner, imports, True) + " | None"
        python_outer = CONTAINERS.get(outer)
        if python_outer:
            args = [map_type(part, imports) for part in _split_top_level(inner)]
            return "{0}[{1}]".format(python_outer, ", ".join(args)) if args else python_outer
        if outer in QT_MODULES:
            imports.add((QT_MODULES[outer], outer))
        return outer

    if base.startswith("Qt::"):
        imports.add(("PySide6.QtCore", "Qt"))
        return "Qt." + base.split("::", 1)[1]
    if base in SCALARS:
        return SCALARS[base] or "None"
    if base in QT_MODULES:
        imports.add((QT_MODULES[base], base))
        return base if not (nullable or pointer) else base + " | None"
    if base.startswith("Flu") or (base and base[0].isupper()):
        return base if not (nullable or pointer) else base + " | None"
    return "Any"


def map_default(raw, imports):
    """Translate a C++ default argument into a Python one, or ``...``."""
    value = " ".join(raw.split())
    if not value:
        return None
    if value in ("nullptr", "NULL"):
        return "None"
    if value == "true":
        return "True"
    if value == "false":
        return "False"
    if re.fullmatch(r"-?\d+", value):
        return value
    if re.fullmatch(r"-?\d+\.\d+([eE][-+]?\d+)?[fF]?", value):
        return value.rstrip("fF")
    if re.fullmatch(r'"(?:[^"\\]|\\.)*"', value):
        return value
    enum_match = re.fullmatch(r"([A-Za-z_]\w*)::(\w+)", value)
    if enum_match:
        owner = enum_match.group(1)
        if owner in QT_MODULES:
            imports.add((QT_MODULES[owner], owner))
        return "{0}.{1}".format(owner, enum_match.group(2))
    return "..."


def _parse_params(text, imports):
    params = []
    for position, piece in enumerate(_split_top_level(text or "")):
        chunk = piece.strip()
        if not chunk or chunk == "void":
            continue
        default = None
        if "=" in chunk:
            chunk, raw_default = chunk.split("=", 1)
            default = map_default(raw_default, imports)
        chunk = " ".join(chunk.split())
        match = re.match(r"^(.*?)([A-Za-z_]\w*)$", chunk)
        if match and match.group(1).strip():
            cpp_type, name = match.group(1), match.group(2)
        else:
            cpp_type, name = chunk, "arg_{0}".format(position)
        nullable = default == "None"
        params.append((name, map_type(cpp_type, imports, nullable), default))
    return params


_METHOD = re.compile(
    r"^(?P<static>static\s+)?(?P<ret>.+?)\s+(?P<name>~?[A-Za-z_]\w*)\s*"
    r"\((?P<params>.*)\)\s*(?P<const>const)?\s*$",
    re.S,
)


def _parse_method(statement, class_name, imports):
    statement = " ".join(statement.split())
    statement = re.sub(r"\boverride\b|\bfinal\b|\bnoexcept\b|\bQ_INVOKABLE\b", "", statement).strip()
    if statement.endswith(";"):
        statement = statement[:-1].strip()
    match = _METHOD.match(statement)
    if not match:
        return None
    name = match.group("name")
    if name in ("if", "for", "while", "switch", "return", "delete", "new"):
        return None
    if name == class_name or name == "~" + class_name:
        return None
    returns = map_type(match.group("ret"), imports)
    if returns == "Any" and " " in match.group("ret"):
        return None  # looked like a statement, not a declaration
    return {
        "name": name,
        "params": _parse_params(match.group("params"), imports),
        "returns": returns,
        "static": bool(match.group("static")),
    }


def parse_header(path):
    """Return ({class_name: parsed}, imports) for one header."""
    with open(path, encoding="utf-8", errors="replace") as handle:
        text = _strip_noise(handle.read())

    imports = set()
    results = {}
    stack = []          # (class_name_or_None, access_before_the_block)
    access = "public"

    for kind, payload in _units(text):
        if kind == "class":
            match = re.search(r"\bclass\s+(?:\w+\s+)?(\w+)", payload)
            name = match.group(1) if match else None
            if not name:
                stack.append((None, access))
                continue
            bases = re.findall(
                r":\s*(?:virtual\s+)?(?:public|protected|private)\s+([\w:]+)", payload)
            results.setdefault(name, {
                "bases": list(bases),
                "methods": {},
                "ctors": [],
                "signals": {},
                "properties": {},
            })
            stack.append((name, access))
            # a class body starts private unless the declaration said otherwise
            access = "private"
            continue
        if kind in ("enum", "namespace"):
            # their bodies were already consumed by _skip_block, so no matching
            # endclass will ever arrive: pushing here would corrupt the stack
            # and silently drop every member declared after the first enum
            continue
        if kind == "endclass":
            if stack:
                _, access = stack.pop()
            continue

        if payload.startswith("@@ACCESS:"):
            access = payload.split(":", 1)[1].strip("@ \n")
            continue

        current_class = stack[-1][0] if stack else None
        if current_class is None:
            continue

        entry = results[current_class]
        statement = payload.rstrip(";").strip()

        property_match = _Q_PROPERTY.search(statement)
        if property_match:
            entry["properties"][property_match.group(2)] = map_type(
                property_match.group(1), imports)
            continue
        if statement.startswith("Q_"):
            continue
        if "(" not in statement:
            continue

        if statement.startswith(current_class + "(") or \
                re.match(r"^explicit\s+" + re.escape(current_class) + r"\s*\(", statement):
            match = re.match(r"^(?:explicit\s+)?" + re.escape(current_class)
                             + r"\s*\((.*)\)$", statement, re.S)
            if match:
                entry["ctors"].append({
                    "name": "__init__",
                    "params": _parse_params(match.group(1), imports),
                    "returns": None,
                    "static": False,
                })
            continue

        if access == "signals":
            match = re.match(r"^\s*void\s+(\w+)\s*\((.*)\)$", statement, re.S)
            if match:
                entry["signals"][match.group(1)] = _parse_params(match.group(2), imports)
            continue

        signature = _parse_method(statement, current_class, imports)
        if signature:
            bucket = entry["methods"].setdefault(signature["name"], [])
            if signature not in bucket:
                bucket.append(signature)

    return results, imports


def parse_headers(repo_root, directories=("controls", "utils")):
    """Parse every header under the given directories, keyed by class name."""
    index = {}
    imports = set()
    for directory in directories:
        base = os.path.join(repo_root, directory)
        if not os.path.isdir(base):
            continue
        for file_name in sorted(os.listdir(base)):
            if not file_name.endswith(".h"):
                continue
            parsed, file_imports = parse_header(os.path.join(base, file_name))
            imports.update(file_imports)
            for class_name, entry in parsed.items():
                if class_name not in index:
                    index[class_name] = entry
                    continue
                merged = index[class_name]
                merged["bases"] = merged["bases"] or entry["bases"]
                merged["methods"].update(entry["methods"])
                merged["signals"].update(entry["signals"])
                merged["properties"].update(entry["properties"])
                merged["ctors"].extend(entry["ctors"])
    return index, imports
