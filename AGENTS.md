# FluentUI - Qt C++ Fluent Design 组件库

## 构建命令

```bash
# CMake 配置（使用 Visual Studio 17 2022 生成器）
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=C:/Qt/6.5.1/msvc2019_64 -G"Visual Studio 17 2022" -A x64 ..

# 编译（默认使用 Debug 配置）
cmake --build . --config Debug
```

> Qt 6.5.1 安装路径：`C:/Qt/6.5.1/msvc2019_64`
> 编译产物输出目录：`build/bin/`（包含 `Gallery.exe`、`Examples.exe` 等）

## 运行 Gallery

```powershell
# 需要先将 Qt 动态库目录加入 PATH
$env:PATH = "C:\Qt\6.5.1\msvc2019_64\bin;" + $env:PATH
& "build\bin\Gallery.exe"
```

## Python 绑定

```bash
# 构建 Python 绑定（需要 PySide6 6.8.3 + Shiboken6）
cmake -DBUILD_PYTHON_BINDINGS=ON -DCMAKE_PREFIX_PATH=C:/Qt/6.8.1/msvc2022_64 -G"Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release --target FluentUI
```

> 产物：`build/bindings/PySide6/Release/FluentUI.pyd`
> 当前导出：`FluWidget`、`FluPushButton`、`FluIconButton`
> 测试：`python bindings/PySide6/test_bindings.py`

## CMake 选项

| 选项 | 默认值 | 说明 |
|------|--------|------|
| `USE_QRC` | `TRUE` | 使用 Qt 资源文件 |
| `BUILD_GALLERY` | `TRUE` | 构建 Gallery 演示应用 |
| `BUILD_ICONTOOL` | `FALSE` | 构建图标工具 |
| `BUILD_PYTHON_BINDINGS` | `FALSE` | 构建 PySide6 Python 绑定 |

## 项目结构

- `Controls/` - 187+ Fluent Design 控件（静态库 `FluentUI::Controls`）
- `Utils/` - 主题/图标/配置工具类（静态库 `FluentUI::Utils`）
- `Gallery/` - 主演示应用（可执行文件）
- `Examples/` - 单个控件演示（可执行文件）
- `bindings/PySide6/` - PySide6 Python 绑定（Shiboken6 生成）
- `3rdparty/` - 源码集成的第三方库
- `StyleSheet/` - 566 个 QSS 文件（Light/Dark/AtomOneDark 三套主题）
- `code/` - Gallery 页面的 Markdown 代码示例

## 依赖

- Qt 6.5.1（安装路径：`C:/Qt`）
- CMake >= 3.20，C++17
- Qt 模块：Core、Widgets、Svg、Charts、Core5Compat
- PySide6 6.8.3 + Shiboken6（仅 Python 绑定需要，pip 安装）

## 代码风格

- `.clang-format` 基于 Google 风格
- 缩进：4 空格，列宽限制：249
- 所有控件以 `Flu` 前缀命名（如 `FluPushButton`）
- 头文件/源文件配对：`FluWidget.h` / `FluWidget.cpp`

## 关键模式

- 主题切换：`FluThemeUtils::setTheme()` → 发射 `themeChanged` 信号
- 控件动态加载 QSS：`FluStyleSheetUtils::setQssByFileName()`
- 基类：`FluWidget` → `FluFrameLessWidget` / `FluWindowKitWidget`
- 图标：`FluAwesomeType` 枚举映射 Segoe Fluent Icons 字体（2300+ 图标）
