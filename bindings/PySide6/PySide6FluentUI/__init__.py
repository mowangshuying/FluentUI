"""
PySide6FluentUI - Fluent Design UI widgets for PySide6

This package provides Python bindings for the FluentUI C++ library,
implementing Microsoft's Fluent Design System using Qt/PySide6.

Usage:
    from PySide6FluentUI import FluPushButton, FluWidget, FluThemeUtils
"""

import os
import sys

# Add DLL directories for Windows (Qt DLLs, PySide6, shiboken6)
if sys.platform == "win32":
    # PySide6 DLLs
    try:
        import PySide6
        os.add_dll_directory(os.path.dirname(PySide6.__file__))
    except (ImportError, OSError):
        pass
    # shiboken6 DLLs
    try:
        import shiboken6
        os.add_dll_directory(os.path.dirname(shiboken6.__file__))
    except (ImportError, OSError):
        pass

# Import all bound classes from the native module
from .PySide6FluentUI import *  # noqa: F401,F403

__version__ = "1.0.0"
__all__ = []  # Populated by the star import above
