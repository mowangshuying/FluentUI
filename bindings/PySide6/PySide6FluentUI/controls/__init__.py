"""FluentUI control classes re-exported from the native PySide6FluentUI module.

Everything bound from ``controls/`` is exposed here; the helper classes bound
from ``utils/`` are only reachable through :mod:`PySide6FluentUI.utils`.
"""

import enum

from .. import PySide6FluentUI as _native
from ..PySide6FluentUI import *  # noqa: F401,F403

# Helper classes that belong to PySide6FluentUI.utils, not to this subpackage
_UTILS_CLASSES = frozenset({
    "FluConfigUtils",
    "FluEmoijUtils",
    "FluIconUtils",
    "FluLogUtils",
    "FluObjectPtrUtils",
    "FluStyleSheetUtils",
    "FluThemeUtils",
    "FluTranslatorUtils",
})


def _is_control_class(name, value):
    if not name.startswith("Flu") or name in _UTILS_CLASSES:
        return False
    if not isinstance(value, type) or issubclass(value, enum.Enum):
        return False
    return True


__all__ = sorted(
    _name
    for _name in dir(_native)
    if _is_control_class(_name, getattr(_native, _name))
)

# Drop the star-imported helpers so this namespace only holds controls
for _name in _UTILS_CLASSES:
    globals().pop(_name, None)
del _name