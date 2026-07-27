# PySide6FluentUI

Fluent Design UI widgets for PySide6 — Python bindings for the FluentUI C++ library.

## Installation

### From Wheel (Windows)

```bash
pip install PySide6FluentUI
```

Or from GitHub Releases:

```bash
pip install https://github.com/mowangshuying/FluentUI/releases/download/v1.0.0/PySide6FluentUI-1.0.0-cp313-cp313-win_amd64.whl
```

> PySide6 6.8.3 and shiboken6 6.8.3 will be installed automatically as dependencies.

### Build from Source

#### Prerequisites

| Dependency | Version | Install |
|------------|---------|---------|
| Python | 3.13 | https://python.org |
| Qt | 6.8.1 | https://qt.io (need `qtcharts` + `qt5compat` modules) |
| Visual Studio 2022 | MSVC v143 | https://visualstudio.microsoft.com |
| CMake | >= 3.20 | Bundled with VS or standalone |
| PySide6 | 6.8.3 | `pip install PySide6==6.8.3` |
| Shiboken6 Generator | 6.8.3 | `pip install shiboken6-generator==6.8.3` |

#### Build Steps

```bash
# 1. Clone the repository
git clone https://github.com/mowangshuying/FluentUI.git
cd FluentUI

# 2. Install Python dependencies
pip install PySide6==6.8.3 shiboken6==6.8.3 shiboken6-generator==6.8.3

# 3. Configure CMake (adjust Qt path to your installation)
cmake -DBUILD_PYTHON_BINDINGS=ON \
      -DCMAKE_PREFIX_PATH=C:/Qt/6.8.1/msvc2022_64 \
      -G"Visual Studio 17 2022" -A x64 \
      -B build

# 4. Build the Python module
cmake --build build --config Release --target PySide6FluentUI

# 5. Output
# → build/bindings/PySide6/Release/PySide6FluentUI.pyd
```

#### Build Wheel (for distribution)

```bash
cd bindings/PySide6
build_wheel.bat [Qt_PATH]
# → dist/PySide6FluentUI-1.0.0-cp313-cp313-win_amd64.whl
```

## Quick Start

```python
import sys
from PySide6.QtWidgets import QApplication
from PySide6FluentUI import FluPushButton, FluThemeUtils

app = QApplication(sys.argv)

# Set theme (Light / Dark / AtomOneDark)
FluThemeUtils.setTheme(FluThemeUtils.Light)

# Create a Fluent Design button
button = FluPushButton()
button.setText("Hello FluentUI!")
button.show()

sys.exit(app.exec())
```

## Examples

See `bindings/PySide6/examples/` for demo scripts:

| Script | Description |
|--------|-------------|
| `demo_all_controls.py` | Showcase of all bound widgets |
| `demo_input.py` | Input controls (LineEdit, ComboBox, SpinBox...) |
| `demo_navigation.py` | Navigation views (TabBar, Pivot, VNavigation...) |
| `demo_dialogs.py` | Dialogs and flyouts |
| `demo_theme.py` | Theme switching demo |

Run an example:

```bash
cd bindings/PySide6/examples
python demo_all_controls.py
```

## Bound Classes (152 total)

### Utils
`FluThemeUtils`, `FluConfigUtils`, `FluStyleSheetUtils`, `FluIconUtils`, `FluLogUtils`, `FluTranslatorUtils`, `FluEmoijUtils`, `FluObjectPtrUtils`

### Buttons
`FluPushButton`, `FluIconButton`, `FluCheckBox`, `FluRadioButton`, `FluToggleButton`, `FluDropDownButton`, `FluSplitButton`, `FluRepeatButton`, `FluHyperLinkButton`, `FluAppBarButton`, `FluAppBarToggleButton`, `FluStyleButton`, `FluScaleButton`, `FluRotationButton`, `FluGraphicalButton`, `FluThemeButton`, `FluPPushButton`, `FluWindowkitButton`

### Input
`FluLineEdit`, `FluTextEdit`, `FluTextEditWrap`, `FluSpinBox`, `FluDoubleSpinBox`, `FluPasswordBox`, `FluSearchLineEdit`, `FluComboBox`, `FluComboBoxEx`, `FluSlider`, `FluRatingControl`, `FluAutoSuggestBox`

### Navigation
`FluTabBar`, `FluTabView`, `FluTabWidget`, `FluPagination`, `FluPivot`, `FluSegmented`, `FluVNavigationView`, `FluHNavigationView`, `FluMSNavigationView`, `FluCommandBar`

### Display
`FluLabel`, `FluProgressBar`, `FluProgressRing`, `FluBusyProgressRing`, `FluInfoBadge`, `FluImageBox`, `FluDisplayBox`, `FluCodeBox`, `FluLoopView`, `FluHFlipView`, `FluVFlipView`, `FluTableView`, `FluListView`, `FluTreeView`

### Containers
`FluExpander`, `FluScrollArea`, `FluVScrollView`, `FluHScrollView`, `FluVCard`, `FluHCard`, `FluBorder`

### Dialogs & Popups
`FluDialog`, `FluMessageBox`, `FluMenu`, `FluMenuBar`, `FluRoundMenu`, `FluTeachingTip`, `FluVFlyout`, `FluConfirmFlyout`, `FluColorFlyout`

### Window
`FluWindowKitWidget`, `FluWindowKitTitleBar`, `FluWindowKitWindow`

## Troubleshooting

### ImportError: DLL load failed

On Windows, the .pyd needs Qt/PySide6 DLLs. Ensure PySide6 is installed:

```bash
pip install PySide6==6.8.3
```

The `__init__.py` auto-registers DLL directories. If it still fails, manually add:

```python
import os
os.add_dll_directory(r"C:\Qt\6.8.1\msvc2022_64\bin")
```

### Shiboken generation fails

Ensure the generator package is installed (separate from runtime):

```bash
pip install shiboken6-generator==6.8.3
```

### Version mismatch

The .pyd is ABI-locked to PySide6 6.8.3. Using a different PySide6 version will crash. Always pin:

```bash
pip install PySide6==6.8.3 shiboken6==6.8.3
```

## License

LGPL-2.1 — see [LICENSE](../../LICENSE.LGPL) for details.

## Links

- [FluentUI C++ Repository](https://github.com/mowangshuying/FluentUI)
- [PySide6 Documentation](https://doc.qt.io/qtforpython/)
- [Shiboken Documentation](https://doc.qt.io/qtforpython/shiboken/)
