"""
FluentUI for PySide6
A Python binding for the FluentUI C++ library
"""

__version__ = "1.0.0"
__author__ = "FluentUI Team"

# Import submodules
from . import controls
from . import utils

# Import commonly used classes for convenience
from .controls import FluPushButton, FluIconButton
from .utils import FluThemeUtils

__all__ = [
    'controls',
    'utils',
    'FluPushButton',
    'FluIconButton',
    'FluThemeUtils',
]
