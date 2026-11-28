#!/usr/bin/env python
r"""FluentUI Python bindings test.

Covers the native ``PySide6FluentUI`` extension *and* the Python package layer
built on top of it: the package ``__init__``, ``PySide6FluentUI.controls`` and
``PySide6FluentUI.utils``.

Path resolution (no hardcoded machine paths):
  - Build dir:    argv[1] or FLUENTUI_BINDINGS_BUILD_DIR,
                  defaults to <repo>/build-bindings (relative to this script)
  - Qt dir:       FLUENTUI_QT_DIR, defaults to C:\Qt\6.9.0\msvc2022_64
  - Extension:    <package dir>\PySide6FluentUI.pyd (wheel layout) or
                  <build dir>\bindings\PySide6\<Release|Debug>\PySide6FluentUI.pyd

Set FLUENTUI_BINDINGS_SMOKE=1 to additionally instantiate a widget offscreen.
"""

import importlib.util
import os
import sys
import types

DEFAULT_QT_DIR = r"C:\Qt\6.9.0\msvc2022_64"
NATIVE_NAME = "PySide6FluentUI"
EXTENSION_FILE = NATIVE_NAME + ".pyd"

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.normpath(os.path.join(SCRIPT_DIR, "..", ".."))
PACKAGE_DIR = os.path.join(SCRIPT_DIR, NATIVE_NAME)
PACKAGE_INIT = os.path.join(PACKAGE_DIR, "__init__.py")

REQUIRED_CLASSES = [
    "FluWidget",
    "FluPushButton",
    "FluIconButton",
    "FluInfoBar",
    "FluDotInfoBadge",
    "FluToggleSwitch",
    "FluThemeUtils",
]

UTIL_CLASSES = [
    "FluConfigUtils",
    "FluEmoijUtils",
    "FluIconUtils",
    "FluLogUtils",
    "FluObjectPtrUtils",
    "FluStyleSheetUtils",
    "FluThemeUtils",
    "FluTranslatorUtils",
]

CONTROL_CLASSES = [name for name in REQUIRED_CLASSES if name not in UTIL_CLASSES]


def add_dll_dir(path):
    """Register a DLL search directory (Windows only, silently skip missing)."""
    if sys.platform != "win32" or not os.path.isdir(path):
        return
    try:
        os.add_dll_directory(path)
    except OSError:
        pass


def resolve_build_dir():
    if len(sys.argv) > 1:
        return os.path.abspath(sys.argv[1])
    env = os.environ.get("FLUENTUI_BINDINGS_BUILD_DIR")
    if env:
        return os.path.abspath(env)
    return os.path.join(REPO_ROOT, "build-bindings")


def extension_candidates(build_dir):
    return [
        os.path.join(PACKAGE_DIR, EXTENSION_FILE),
        os.path.join(build_dir, "bindings", "PySide6", "Release", EXTENSION_FILE),
        os.path.join(build_dir, "bindings", "PySide6", "Debug", EXTENSION_FILE),
    ]


def find_extension(build_dir):
    for candidate in extension_candidates(build_dir):
        if os.path.isfile(candidate):
            return candidate
    return None


def load_package(extension_path):
    """Import the Python package with the native module injected as a submodule.

    The CMake build writes the extension outside the source tree, while the
    package imports it as ``PySide6FluentUI.PySide6FluentUI`` (the wheel
    layout). Registering the extension under that name keeps both layouts
    working and makes the real package ``__init__`` run, so the subpackages
    are exercised instead of the bare extension.
    """
    sys.modules.pop(NATIVE_NAME, None)
    package = types.ModuleType(NATIVE_NAME)
    package.__path__ = [PACKAGE_DIR]
    package.__package__ = NATIVE_NAME
    package.__file__ = PACKAGE_INIT
    sys.modules[NATIVE_NAME] = package

    submodule_name = "{0}.{0}".format(NATIVE_NAME)
    spec = importlib.util.spec_from_file_location(submodule_name, extension_path)
    if spec is None or spec.loader is None:
        raise SystemExit("Error: cannot load the native module from {0}".format(extension_path))
    native = importlib.util.module_from_spec(spec)
    sys.modules[submodule_name] = native
    spec.loader.exec_module(native)
    package.PySide6FluentUI = native

    with open(PACKAGE_INIT, encoding="utf-8") as stream:
        code = compile(stream.read(), PACKAGE_INIT, "exec")
    exec(code, package.__dict__)
    return package, native


def run_smoke(package, failures):
    """Instantiate a widget offscreen (opt-in via FLUENTUI_BINDINGS_SMOKE=1)."""
    os.environ.setdefault("QT_QPA_PLATFORM", "offscreen")
    try:
        from PySide6.QtWidgets import QApplication

        QApplication.instance() or QApplication([])
        button = package.FluPushButton()
        button.setText("smoke")
        print("OK: FluPushButton instantiated (text={0!r})".format(button.text()))
    except Exception as exc:  # noqa: BLE001 - report instead of crashing the run
        failures.append("widget smoke test failed: {0}".format(exc))
        print("FAIL: widget smoke test failed: {0}".format(exc))


def main():
    build_dir = resolve_build_dir()
    qt_dir = os.environ.get("FLUENTUI_QT_DIR", DEFAULT_QT_DIR)

    add_dll_dir(os.path.join(qt_dir, "bin"))
    for module_name in ("PySide6", "shiboken6"):
        try:
            module = __import__(module_name)
        except ImportError:
            continue
        add_dll_dir(os.path.dirname(module.__file__))

    extension_path = find_extension(build_dir)
    if extension_path is None:
        print("Error: {0} not found. Looked in:".format(EXTENSION_FILE))
        for candidate in extension_candidates(build_dir):
            print("  {0}".format(candidate))
        print("Build the bindings first, or override the paths via:")
        print("  argv[1] / FLUENTUI_BINDINGS_BUILD_DIR  (build directory)")
        print("  FLUENTUI_QT_DIR                        (Qt installation directory)")
        return 1

    add_dll_dir(os.path.dirname(extension_path))

    print("FluentUI Python bindings test started!")
    print("Python: {0}".format(sys.version.split()[0]))
    print("Extension: {0}".format(extension_path))

    package, native = load_package(extension_path)
    print("Package: {0}".format(package.__file__))
    print("Native exports: {0}".format(len([n for n in dir(native) if n.startswith("Flu")])))

    failures = []

    for name in REQUIRED_CLASSES:
        if hasattr(package, name):
            print("OK: {0} is exported by the package".format(name))
        else:
            failures.append("{0} is not exported by the package".format(name))
            print("FAIL: {0} is not exported by the package".format(name))

    import PySide6FluentUI.controls as controls
    import PySide6FluentUI.utils as utils

    missing_utils = [name for name in UTIL_CLASSES if not hasattr(utils, name)]
    if missing_utils:
        failures.append("utils is missing: {0}".format(missing_utils))
        print("FAIL: utils is missing {0}".format(missing_utils))
    if sorted(utils.__all__) != sorted(UTIL_CLASSES):
        failures.append("utils.__all__ does not match the expected helper list")
        print("FAIL: utils.__all__ = {0}".format(sorted(utils.__all__)))
    else:
        print("OK: utils exports the {0} helper classes".format(len(UTIL_CLASSES)))

    leaked = [name for name in UTIL_CLASSES if hasattr(controls, name)]
    if leaked:
        failures.append("controls leaks helper classes: {0}".format(leaked))
        print("FAIL: controls leaks helper classes {0}".format(leaked))

    missing_controls = [name for name in CONTROL_CLASSES if not hasattr(controls, name)]
    if missing_controls:
        failures.append("controls is missing: {0}".format(missing_controls))
        print("FAIL: controls is missing {0}".format(missing_controls))

    controls_exported = sorted(controls.__all__)
    overlap = sorted(set(controls_exported) & set(UTIL_CLASSES))
    if overlap:
        failures.append("controls.__all__ overlaps utils: {0}".format(overlap))
        print("FAIL: controls.__all__ overlaps utils {0}".format(overlap))
    else:
        print("OK: controls exports {0} control classes, no helper classes".format(
            len(controls_exported)))

    if os.environ.get("FLUENTUI_BINDINGS_SMOKE") == "1":
        run_smoke(package, failures)

    if failures:
        print("\n{0} check(s) failed".format(len(failures)))
        return 1

    print("FluentUI Python bindings test passed!")
    return 0


if __name__ == "__main__":
    sys.exit(main())