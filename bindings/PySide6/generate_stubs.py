"""Generate .pyi type stubs for PySide6FluentUI by runtime introspection.

Usage: python generate_stubs.py <build_dir> <qt_path> <output_pkg_dir>
"""
import sys
import os
import inspect


def main():
    if len(sys.argv) < 4:
        print("Usage: python generate_stubs.py <build_dir> <qt_path> <output_pkg_dir>")
        sys.exit(1)

    build_dir = sys.argv[1]
    qt_path = sys.argv[2].replace("/", "\\")
    output_pkg_dir = sys.argv[3]

    # Setup DLL paths
    pyd_dir = os.path.join(build_dir, "bindings", "PySide6", "Release")
    bin_dir = os.path.join(build_dir, "bin")
    qt_bin = os.path.join(qt_path, "bin")

    sys.path.insert(0, pyd_dir)
    os.add_dll_directory(pyd_dir)
    os.add_dll_directory(bin_dir)
    os.add_dll_directory(qt_bin)

    import PySide6
    os.add_dll_directory(os.path.dirname(PySide6.__file__))
    import shiboken6
    os.add_dll_directory(os.path.dirname(shiboken6.__file__))

    # Also add the package dir (for bundled DLLs)
    if os.path.isdir(output_pkg_dir):
        os.add_dll_directory(output_pkg_dir)

    import PySide6FluentUI

    lines = [
        '"""Type stubs for PySide6FluentUI - Fluent Design UI widgets for PySide6."""',
        '',
        'from PySide6.QtWidgets import QWidget, QFrame, QDialog, QMenu, QMenuBar, QScrollArea',
        'from PySide6.QtWidgets import QTabWidget, QTableView, QTreeView, QComboBox, QSpinBox',
        'from PySide6.QtWidgets import QLineEdit, QTextEdit, QSlider, QProgressBar, QCalendarWidget',
        'from PySide6.QtWidgets import QAbstractScrollArea, QAbstractItemView, QSystemTrayIcon',
        'from PySide6.QtCore import QObject, QTimer, QPoint, QSize, QRect, Qt, Signal',
        'from PySide6.QtGui import QColor, QIcon, QPainter, QAction',
        'from typing import Optional, List, Any',
        '',
    ]

    class_count = 0
    seen_classes = set()

    for name in sorted(dir(PySide6FluentUI)):
        if name.startswith('_'):
            continue
        obj = getattr(PySide6FluentUI, name)
        if not inspect.isclass(obj):
            continue
        if not obj.__module__ or 'PySide6FluentUI' not in str(obj.__module__):
            continue
        if name in seen_classes:
            continue
        seen_classes.add(name)

        class_count += 1
        bases = [b.__name__ for b in obj.__bases__]
        base_str = ', '.join(bases) if bases else 'object'
        lines.append(f'class {name}({base_str}):')
        lines.append(f'    """FluentUI {name} widget."""')

        methods_added = False
        seen_methods = set()
        for mname in sorted(dir(obj)):
            if mname.startswith('_') and mname != '__init__':
                continue
            if mname in seen_methods:
                continue
            seen_methods.add(mname)
            try:
                m = getattr(obj, mname)
                if not callable(m) or isinstance(m, type):
                    continue
                try:
                    sig = inspect.signature(m)
                    params = []
                    for pname, param in sig.parameters.items():
                        if pname in ('self', 'cls'):
                            continue
                        if param.default is inspect.Parameter.empty:
                            params.append(f'{pname}: Any')
                        else:
                            params.append(f'{pname}: Any = ...')
                    sig_str = f"({', '.join(params)})"
                except (ValueError, TypeError):
                    sig_str = '(*args: Any, **kwargs: Any)'

                if mname == '__init__':
                    lines.append(f'    def __init__{sig_str} -> None: ...')
                else:
                    lines.append(f'    def {mname}{sig_str} -> Any: ...')
                methods_added = True
            except Exception:
                pass

        if not methods_added:
            lines.append('    ...')
        lines.append('')
        lines.append('')

    out_path = os.path.join(output_pkg_dir, 'PySide6FluentUI.pyi')
    with open(out_path, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines))

    print(f'Generated: {out_path}')
    print(f'Classes: {class_count}, Lines: {len(lines)}')


if __name__ == '__main__':
    main()
