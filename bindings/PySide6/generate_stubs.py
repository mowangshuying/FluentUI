#!/usr/bin/env python
"""Generate .pyi type stubs for PySide6FluentUI.

Usage: python generate_stubs.py <build_dir> <qt_path> <output_pkg_dir>

Hybrid strategy:

  * runtime introspection decides *structure* -- which classes and members the
    built extension really exposes, and whether a member is an instance,
    class or static method;
  * the C++ headers (``header_signatures.py``) supply the *types*, because
    ``inspect.signature`` on a Shiboken method almost never recovers C++ return
    or argument types, which is what left the previous stub ~99.7% ``-> Any``.

Output rules that keep VSCode/Pylance happy:

  * every class is emitted exactly once (duplicates make the language server
    pick one body at random -- the classic "completion works sometimes");
  * classes are topologically ordered so a ``Flu*`` base precedes its
    subclasses (alphabetical order put ``FluWidget`` last and broke 100+
    inheritances);
  * foreign base classes are imported from their real module, and self
    references are never emitted;
  * Qt signals and Q_PROPERTY members are declared as *attributes*
    (``clicked: SignalInstance``), not as ``def``, so ``btn.clicked.connect``
    resolves;
  * members inherited from Qt bases are not copied in -- PySide6's own stubs
    type them precisely and an ``-> Any`` copy would shadow that;
  * any header type that cannot be resolved inside the stub (e.g. a nested
    ``enum class State``) is degraded to ``Any`` rather than emitted as an
    undefined name.
"""

import inspect
import os
import re
import sys

if __package__ in (None, ""):
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import header_signatures  # noqa: E402

STUB_HEADER = '"""Type stubs for PySide6FluentUI - Fluent Design UI widgets for PySide6."""'

EXTERNAL_MODULE_PREFIXES = ("PySide6", "shiboken6")

PRIMITIVES = {
    "Any", "None", "bool", "int", "float", "str", "bytes", "object",
    "dict", "list", "set", "tuple", "SignalInstance",
}

_QUALIFIED = re.compile(r"[A-Za-z_][A-Za-z0-9_]*(?:\.[A-Za-z_][A-Za-z0-9_]*)*")

SIGNAL_TYPE_NAMES = frozenset({"Signal", "SignalInstance"})


def is_bound_class(obj):
    return inspect.isclass(obj) and obj.__module__ and any(
        part in str(obj.__module__) for part in ("PySide6FluentUI", "FluentUI")
    )


def collect_classes(module):
    """Return {name: class} for every class owned by the bindings module."""
    classes = {}
    for name in dir(module):
        if name.startswith("_"):
            continue
        obj = getattr(module, name, None)
        if is_bound_class(obj):
            classes[name] = obj
    return classes


def external_bases(classes):
    """Map every foreign base class to the module it must be imported from."""
    own = set(classes)
    imports = {}
    for obj in classes.values():
        for base in obj.__bases__:
            name = base.__name__
            if name in own or name == "object" or is_bound_class(base):
                continue
            module = getattr(base, "__module__", "") or ""
            if module.startswith(EXTERNAL_MODULE_PREFIXES):
                imports.setdefault(module, set()).add(name)
    return imports


def inherited_foreign_members(obj):
    """Members coming from non-bound bases (QWidget, QObject, ...).

    They must not be re-declared: PySide6's own stubs already type them, and an
    ``-> Any`` copy would shadow that and bloat the file.
    """
    names = set()
    for base in obj.__mro__[1:]:
        if not is_bound_class(base):
            names.update(vars(base))
    return names


def order_classes(classes):
    """Topologically sort class names so bases defined in the stub come first."""
    names = set(classes)
    ordered = []
    state = {}

    def visit(name, stack):
        if state.get(name) == "done":
            return
        if name in stack:  # defensive: never loop on a cyclic hierarchy
            state[name] = "done"
            return
        stack.add(name)
        for base in classes[name].__bases__:
            base_name = base.__name__
            if base_name in names and base_name != name:
                visit(base_name, stack)
        stack.discard(name)
        state[name] = "done"
        ordered.append(name)

    for name in sorted(names):
        visit(name, set())
    return ordered


def _method_kind(obj, name):
    """Classify a class attribute as instance / class / static method."""
    raw = inspect.getattr_static(obj, name, None)
    if isinstance(raw, staticmethod):
        return "static"
    if isinstance(raw, classmethod):
        return "class"
    return "instance"


def _is_signal(attribute):
    """A Qt signal lives on the class but is *not* callable.

    Shiboken stores ``Signal`` objects in the class ``__dict__``; filtering on
    ``callable()`` alone silently deletes every signal, so ``btn.clicked`` has no
    completion and ``btn.clicked.connect`` is untyped.
    """
    return type(attribute).__name__ in SIGNAL_TYPE_NAMES


def has_own_signals(classes):
    for obj in classes.values():
        for value in vars(obj).values():
            if _is_signal(value):
                return True
    return False


def render_signature(obj, name):
    """Introspection-only fallback signature (no C++ type information)."""
    kind = _method_kind(obj, name)
    attribute = inspect.getattr_static(obj, name)
    target = attribute.__func__ if isinstance(attribute, (classmethod, staticmethod)) else attribute

    try:
        parameters = list(inspect.signature(target).parameters.values())
    except (TypeError, ValueError):
        parameters = None

    prefix = {"instance": ["self"], "class": ["cls"], "static": []}[kind]
    if parameters is None:
        return "({0})".format(", ".join(prefix + ["*args: Any", "**kwargs: Any"]))

    rendered = list(prefix)
    for param in parameters:
        if param.name in ("self", "cls"):
            continue
        if param.kind is inspect.Parameter.VAR_POSITIONAL:
            rendered.append("*{0}: Any".format(param.name))
        elif param.kind is inspect.Parameter.VAR_KEYWORD:
            rendered.append("**{0}: Any".format(param.name))
        elif param.kind is inspect.Parameter.KEYWORD_ONLY:
            if "*" not in rendered:
                rendered.append("*")
            if param.default is inspect.Parameter.empty:
                rendered.append("{0}: Any".format(param.name))
            else:
                rendered.append("{0}: Any = ...".format(param.name))
        elif param.default is inspect.Parameter.empty:
            rendered.append("{0}: Any".format(param.name))
        else:
            rendered.append("{0}: Any = ...".format(param.name))
    return "({0})".format(", ".join(rendered))


def sanitize_type(py_type, available, used):
    """Keep only type names that resolve inside the stub; degrade the rest."""
    if not py_type:
        return "Any"

    def replace(match):
        token = match.group(0)
        head = token.split(".")[0]
        if head in available:
            if head not in PRIMITIVES:
                used.add(head)
            return token
        return "Any"

    return _QUALIFIED.sub(replace, py_type)


def _self_prefix(kind):
    return {"instance": ["self"], "class": ["cls"], "static": []}[kind]


def render_header_signature(signature, kind, available, used):
    """Render one method from a parsed C++ signature."""
    parts = _self_prefix(kind)
    for name, py_type, default in signature["params"]:
        piece = "{0}: {1}".format(name, sanitize_type(py_type, available, used))
        if default is None:
            parts.append(piece)
            continue
        rendered_default = sanitize_type(default, available, used) if default != "..." else "..."
        if rendered_default == "Any":
            rendered_default = "..."
        parts.append("{0} = {1}".format(piece, rendered_default))
    returns = sanitize_type(signature["returns"] or "None", available, used)
    return "({0}) -> {1}".format(", ".join(parts), returns)


def render_class(name, obj, header_entry, available, used):
    bases = [base.__name__ for base in obj.__bases__] or ["object"]
    # a base class is a use of its name: without this the import for QWidget or
    # QObject is dropped and the whole class becomes unresolvable
    for base in obj.__bases__:
        if base.__name__ != "object" and base.__name__ in available:
            used.add(base.__name__)
    lines = ["class {0}({1}):".format(name, ", ".join(bases))]
    lines.append('    """FluentUI {0} widget."""'.format(name))

    header_methods = (header_entry or {}).get("methods", {})
    header_properties = (header_entry or {}).get("properties", {})
    header_ctors = (header_entry or {}).get("ctors", [])

    inherited = inherited_foreign_members(obj)
    own = set(vars(obj))
    emitted = False
    needs_overload = False
    emitted_members = set()

    for member in sorted(dir(obj)):
        if member.startswith("_") and member != "__init__":
            continue
        emitted_members.add(member)
        if member in inherited and member not in own:
            continue  # inherited from Qt: keep the real PySide6 typing
        try:
            attribute = inspect.getattr_static(obj, member)
        except AttributeError:
            continue
        if isinstance(attribute, type):
            continue
        if _is_signal(attribute):
            used.add("SignalInstance")
            lines.append("    {0}: SignalInstance".format(member))
            emitted = True
            continue
        if isinstance(attribute, property):
            py_type = header_properties.get(member, "Any")
            lines.append("    {0}: {1}".format(member, sanitize_type(py_type, available, used)))
            emitted = True
            continue
        if not (callable(attribute) or isinstance(attribute, (classmethod, staticmethod))):
            continue  # skip plain data attributes

        kind = _method_kind(obj, member)
        signatures = header_ctors if member == "__init__" else header_methods.get(member)

        if signatures:
            if len(signatures) > 1:
                needs_overload = True
                for signature in signatures:
                    lines.append("    @overload")
                    lines.append("    def {0}{1}: ...".format(
                        member, render_header_signature(signature, kind, available, used)))
            else:
                decorator = {"static": "    @staticmethod", "class": "    @classmethod"}.get(kind)
                if decorator:
                    lines.append(decorator)
                lines.append("    def {0}{1}: ...".format(
                    member, render_header_signature(signatures[0], kind, available, used)))
        else:
            returns = "None" if member == "__init__" else "Any"
            lines.append("    def {0}{1} -> {2}: ...".format(
                member, render_signature(obj, member), returns))
        emitted = True

    # Q_PROPERTY and signals declared in the headers are not reliably visible
    # through runtime introspection of the built extension, so the header is the
    # authoritative source for them: emit whatever the member loop missed.
    for member in sorted(header_properties):
        if member in emitted_members:
            continue
        lines.append("    {0}: {1}".format(
            member, sanitize_type(header_properties[member], available, used)))
        emitted = True

    header_signals = (header_entry or {}).get("signals", {})
    for member in sorted(header_signals):
        if member in emitted_members:
            continue
        used.add("SignalInstance")
        lines.append("    {0}: SignalInstance".format(member))
        emitted = True

    if not emitted:
        lines.append("    ...")
    lines.append("")
    lines.append("")
    return lines, needs_overload


def build_available(classes, base_imports, header_imports):
    """Names a type annotation may legally use inside the generated stub."""
    available = set(classes) | set(PRIMITIVES)
    mapping = {}
    for module, names in base_imports.items():
        for name in names:
            mapping.setdefault(name, module)
    for module, names in header_imports.items():
        for name in names:
            mapping.setdefault(name, module)
    return available | set(mapping), mapping


def render_imports(base_imports, header_imports, used, needs_overload):
    """Emit only the imports whose names actually appear in the stub."""
    pool = {}
    for module, names in header_imports.items():
        for name in names:
            pool.setdefault(name, module)
    for module, names in base_imports.items():
        for name in names:
            pool[name] = module  # a real base class wins over a header mention

    grouped = {}
    for name in used:
        module = pool.get(name)
        if module:
            grouped.setdefault(module, set()).add(name)

    lines = []
    for module in sorted(grouped):
        lines.append("from {0} import {1}".format(module, ", ".join(sorted(grouped[module]))))
    typing_names = ["Any"]
    if needs_overload:
        typing_names.append("overload")
    lines.append("from typing import {0}".format(", ".join(typing_names)))
    lines.append("")
    return lines


def render_stub(module, header_index=None, header_imports=None):
    classes = collect_classes(module)
    base_imports = external_bases(classes)
    header_imports = header_imports or {}
    if has_own_signals(classes):
        base_imports.setdefault("PySide6.QtCore", set()).add("SignalInstance")

    available, _ = build_available(classes, base_imports, header_imports)

    used = set()
    bodies = []
    needs_overload = False
    for name in order_classes(classes):
        entry = (header_index or {}).get(name)
        lines, overload = render_class(name, classes[name], entry, available, used)
        needs_overload = needs_overload or overload
        bodies.extend(lines)

    # SignalInstance may be referenced by header-declared signals even when the
    # introspected class exposes none of them, so gate the import on actual use
    if "SignalInstance" in used:
        base_imports.setdefault("PySide6.QtCore", set()).add("SignalInstance")

    lines = [STUB_HEADER, ""]
    lines.extend(render_imports(base_imports, header_imports, used, needs_overload))
    lines.extend(bodies)
    return "\n".join(lines), len(classes)


def load_header_index(repo_root):
    """Parse the C++ headers; return ({class: parsed}, {module: {names}})."""
    try:
        index, imports = header_signatures.parse_headers(repo_root)
    except Exception as exc:  # noqa: BLE001 - stubs must still build without headers
        print("WARNING: header type injection disabled: {0}".format(exc))
        return {}, {}
    pool = {}
    for module, name in imports:
        pool.setdefault(module, set()).add(name)
    return index, pool


def main():
    if len(sys.argv) < 4:
        print("Usage: python generate_stubs.py <build_dir> <qt_path> <output_pkg_dir>")
        sys.exit(1)

    build_dir = sys.argv[1]
    qt_path = sys.argv[2].replace("/", "\\")
    output_pkg_dir = sys.argv[3]

    # Setup DLL paths
    pyd_dir = os.path.join(build_dir, "bindings", "PySide6", "Release")
    debug_dir = os.path.join(build_dir, "bindings", "PySide6", "Debug")
    bin_dir = os.path.join(build_dir, "bin")
    qt_bin = os.path.join(qt_path, "bin")

    for directory in (pyd_dir, debug_dir, bin_dir, qt_bin):
        if os.path.isdir(directory):
            sys.path.insert(0, directory)
            if sys.platform == "win32":
                os.add_dll_directory(directory)

    import PySide6
    os.add_dll_directory(os.path.dirname(PySide6.__file__))
    import shiboken6
    os.add_dll_directory(os.path.dirname(shiboken6.__file__))

    # Also add the package dir (for bundled DLLs)
    if os.path.isdir(output_pkg_dir) and sys.platform == "win32":
        os.add_dll_directory(output_pkg_dir)

    import PySide6FluentUI

    repo_root = os.path.normpath(
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
    header_index, header_imports = load_header_index(repo_root)
    print("Header type index: {0} classes parsed".format(len(header_index)))

    text, class_count = render_stub(PySide6FluentUI, header_index, header_imports)

    out_path = os.path.join(output_pkg_dir, "PySide6FluentUI.pyi")
    with open(out_path, "w", encoding="utf-8") as handle:
        handle.write(text)

    typed = len(re.findall(r"-> (?!Any|None)\w", text))
    print("Generated: {0}".format(out_path))
    print("Classes: {0}, typed returns: {1}".format(class_count, typed))


if __name__ == "__main__":
    main()
