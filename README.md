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

+ Fluent Design style controls for Qt C++
+ Supports Light and Dark themes
+ Internationalization (i18n): zh-CN, en-US
+ Cross-platform: Windows, Linux, macOS
+ 200+ ready-to-use controls
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

### CMake Options

| Option | Default | Description |
|--------|---------|-------------|
| `USE_QRC` | `TRUE` | Build with Qt resource files (qrc) |
| `BUILD_GALLERY` | `TRUE` | Build the Gallery demo application |
| `BUILD_ICONTOOL` | `FALSE` | Build the Icon Tool |

## Third-Party Libraries

+ [framelesshelper](https://github.com/nicehash/framelesshelper) - Frameless window helper
+ [Qt-Advanced-Docking-System](https://github.com/nicehash/Qt-Advanced-Docking-System) - Advanced docking system
+ [qscintilla](https://www.riverbankcomputing.com/software/qscintilla/) - Code editor component
+ [qrcode](https://github.com/nicehash/qrcode) - QR code generation
+ [cmark](https://github.com/commonmark/cmark) - CommonMark parser
+ [qwindowkit](https://github.com/nicehash/qwindowkit) - Window kit

> All third-party libraries are integrated as source code in the `3rdparty/` directory.

## Project Structure

```
FluentUI/
├── Controls/       # 200+ Fluent Design controls
├── Examples/       # Control demos and examples
├── Gallery/        # Full demo application
├── Utils/          # Utility classes
├── 3rdparty/       # Third-party libraries (source)
├── i18n/           # Internationalization files
├── docs/           # Documentation and screenshots
└── StyleSheet/     # QSS stylesheets
```

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
