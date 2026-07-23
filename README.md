<h1 align="center">
  Cpp FluentUI 
</h1>

<p align="center">
  A fluent design component library for Qt C++.
</p>

<p align="center">
English | <a href="README_zh_CN.md">简体中文</a>
</p>

<div align=center>
  <img src="docs/gallery-atomOneDark.png">
</div>

## Features

+ **187+ Fluent Design controls** for Qt C++ (C++17)
+ **3 built-in themes**: Light, Dark, Atom One Dark
+ **2300+ icons** via Segoe Fluent Icons font
+ Real-time theme switching with signal-slot mechanism
+ Internationalization (i18n): zh-CN, en-US
+ Cross-platform: Windows, Linux, macOS
+ Gallery demo application with code examples

## Requirements

+ CMake >= 3.20
+ Qt 6.x (tested with Qt 6.5.1, 6.7.1, 6.8.3, 6.9.0) or Qt 5.x
+ C++17 compiler
+ **Windows**: Visual Studio 2022
+ **Linux**: GCC
+ **macOS**: Clang

> Qt modules required: Core, Widgets, Svg, Charts, Core5Compat, Multimedia, ShaderTools, ImageFormats, Speech, 3D, SCXML

## Get Started

### Build with Visual Studio 2022

1. Clone the repository:

   ```shell
   git clone https://github.com/mowangshuying/FluentUI.git
   ```

2. Open `FluentUI.sln` with Visual Studio 2022.

3. Build the solution.

4. Set **Gallery** as the startup project and run it.

### Build with Qt Creator

1. Clone the repository:

   ```shell
   git clone https://github.com/mowangshuying/FluentUI.git
   ```

2. Open `CMakeLists.txt` with Qt Creator.

3. Build the project.

### Build with CMake (Command Line)

1. Clone the repository:

   ```shell
   git clone https://github.com/mowangshuying/FluentUI.git
   ```

2. Build using Ninja (recommended):

   ```shell
   mkdir build && cd build
   cmake -DCMAKE_PREFIX_PATH=/path/to/Qt -GNinja ..
   cmake --build .
   ```

### Quick Build (Windows)

Run `build&pack.bat` to configure, build, and package with a single command (requires Visual Studio 2022 and Qt 6.5.1).

   ```shell
   build&pack.bat
   ```

### CMake Options

| Option | Default | Description |
|--------|---------|-------------|
| `USE_QRC` | `TRUE` | Build with Qt resource files (qrc) |
| `BUILD_GALLERY` | `TRUE` | Build the Gallery demo application |

## Third-Party Libraries

| Library | License | Description |
|---------|---------|-------------|
| [framelesshelper](https://github.com/nicehash/framelesshelper) | MIT | Frameless window helper |
| [Qt-Advanced-Docking-System](https://github.com/nicehash/Qt-Advanced-Docking-System) | LGPL v2.1 | Advanced docking system |
| [qscintilla](https://www.riverbankcomputing.com/software/qscintilla/) | GPL v3 | Code editor component |
| [qrcode](https://github.com/nayuki/QR-Code-generator) | MIT | QR code generation |
| [cmark](https://github.com/commonmark/cmark) | BSD 2-Clause | CommonMark parser |
| [qwindowkit](https://github.com/stdware/qwindowkit) | Apache 2.0 | Window kit |
| [cmark](https://github.com/commonmark/cmark) | BSD 2-Clause | CommonMark parser |
| [qwindowkit](https://github.com/nicehash/qwindowkit) | Apache 2.0 | Window kit |

> All third-party libraries are integrated as source code in the `3rdparty/` directory.

## Project Structure

```
FluentUI/
├── Controls/       # 187+ Fluent Design controls (static library)
├── Examples/       # 75 control demos (executable)
├── Gallery/        # Full demo application (58 pages)
├── Utils/          # Theme/Icon/Config utilities (static library)
├── 3rdparty/       # 6 third-party libraries (source)
├── StyleSheet/     # 566 QSS files (3 themes)
├── i18n/           # Internationalization (zh-CN, en-US)
├── code/           # Markdown code examples (54 files)
├── res/            # Images, fonts, emoji SVGs
├── docs/           # Documentation and screenshots
└── config/         # Runtime configuration
```

## Architecture

```
Gallery / Examples
  └── FluentUI::Controls (static library)
        ├── FluWidget          # Base widget with theme awareness
        ├── FluFrameLessWidget # Frameless window (framelesshelper)
        ├── FluWindowKitWidget # Window kit integration
        └── FluentUI::Utils    # Theme/Icon/Config management
```

### Control Categories

| Category | Controls |
|----------|----------|
| **Buttons** | FluPushButton, FluToggleButton, FluSplitButton, FluDropDownButton, FluAppBarButton... |
| **Input** | FluLineEdit, FluSearchLineEdit, FluPasswordBox, FluSpinBox, FluAutoSuggestBox... |
| **Selection** | FluCheckBox, FluRadioButton, FluToggleSwitch, FluComboBox, FluSegmented... |
| **Navigation** | FluVNavigationView, FluHNavigationView, FluMSNavigationView... |
| **Dialogs** | FluDialog, FluMessageBox, FluConfirmFlyout, FluTeachingTip, FluInfoBar... |
| **Date/Time** | FluCalendarView, FluCalendarDatePicker, FluDatePicker, FluTimePicker... |
| **Layout** | FluExpander, FluPivot, FluStackedLayout, FluFlowLayout... |
| **Code Editor** | FluCodeBox, FluScintilla, FluTerminalWidget... |

## Documentation

See the [docs](./docs) directory for detailed documentation and code examples.

## Reference

+ [microsoft/WinUI-Gallery](https://github.com/microsoft/WinUI-Gallery) - WinUI and Fluent Design System demo
+ [zhiyiYo/PyQt-Fluent-Widgets](https://github.com/zhiyiYo/PyQt-Fluent-Widgets) - Fluent design widgets for PyQt
+ [Sepera-okeq/QtFluentWin11](https://github.com/Sepera-okeq/QtFluentWin11) - Fluent design for Qt on Windows 11
+ [zhuzichu520/FluentUI](https://github.com/zhuzichu520/FluentUI) - FluentUI for QML

## License

This project is licensed under the [GNU Lesser General Public License v2.1](LICENSE.LGPL).

## Star History

![Star History Chart](https://api.star-history.com/svg?repos=mowangshuying/FluentUI&type=Date)
