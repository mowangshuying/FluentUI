# FluentUI - Qt C++ Fluent Design 组件库

## 构建命令

```bash
# CMake 配置（使用 Visual Studio 17 2022 生成器）
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=C:/Qt/6.9.0/msvc2022_64 -G"Visual Studio 17 2022" -A x64 ..

# 编译（默认使用 Debug 配置）
cmake --build . --config Debug
```

> Qt 安装路径：`C:/Qt/6.9.0/msvc2022_64`（本机另有 5.15.2 / 6.5.1 / 6.8.1）
> 编译产物输出目录：`build/debug/bin/`（包含 `Gallery.exe`、`Examples.exe` 等）

## 运行 Gallery

```powershell
# 需要先将 Qt 动态库目录加入 PATH
$env:PATH = "C:\Qt\6.9.0\msvc2022_64\bin;" + $env:PATH
& "build\debug\bin\Gallery.exe"
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

> 另可在 `CMakeUserPresets.json` 使用 `6.8.1_msvc2022_64` 预设（QTDIR=C:/Qt/6.8.1/msvc2022_64，Ninja x64）。

## 项目结构

- `controls/` - 187 个 Fluent Design 控件（静态库 `FluentUI::Controls`）
- `utils/` - 主题/图标/配置工具类（静态库 `FluentUI::Utils`）
- `gallery/` - 主演示应用（可执行文件，59 个控件展示页）
- `examples/` - 单控件演示（可执行文件，76 个 Demo）
- `bindings/PySide6/` - PySide6 Python 绑定（Shiboken6 生成）
- `3rdparty/` - 源码集成的第三方库（framelesshelper、qwindowkit 静态链接，无独立 DLL）
- `stylesheet/` - QSS 文件：`light/dark/atomOneDark` 三套主题各 195 个（共 585）
- `code/` - Gallery 页面的 Markdown 代码示例（61 个）
- `i18n/` - 翻译文件（Controls/Gallery 的 en-US、zh-CN 的 .ts/.qm）
- `scripts/` - 构建/打包/清理脚本（build&pack/package/clean/format/lupdate/lrelease/pushTag/dellogs）
- `res/` - 资源与图片（ControlImages、Segoe_Fluent_Icons.ttf 等）
- `config/` - 配置（`config.ini`）
- `docs/` - 项目文档与截图

## 依赖

- Qt 6.9.0（安装路径：`C:/Qt`）
- CMake >= 3.20，C++17
- Qt 模块：Core、Widgets、Svg、Charts、Core5Compat
- PySide6 6.8.3 + Shiboken6（仅 Python 绑定需要，pip 安装）

## 代码风格

- `.clang-format` 基于 Google 风格
- 缩进：4 空格，列宽限制：249
- 所有控件以 `Flu` 前缀命名（如 `FluPushButton`）
- 头文件/源文件配对：`FluWidget.h` / `FluWidget.cpp`

## 提交规范

- Commit message 格式：`<type>(<scope>): <subject>`
- type 必须使用英文：feat/docs/fix/refactor/chore/perf/style/test
- scope、subject 及详细描述均使用英文，不允许中文
- 一次提交只做一件事，不混无关变更

## 关键模式

- 主题切换：`FluThemeUtils::setTheme()` → 发射 `themeChanged` 信号
- 控件动态加载 QSS：`FluStyleSheetUtils::setQssByFileName()`
- QSS 状态切换：`setProperty()` + `style()->polish()` 强制刷新属性选择器（如 FluToggleButton 的 `[toggled=true]`）
- 基类：`FluWidget` → `FluFrameLessWidget` / `FluWindowKitWidget`
- 图标：`FluAwesomeType` 枚举映射 Segoe Fluent Icons 字体（2300+ 图标）
- 自定义绘制控件：重写 `paintEvent` + `QPropertyAnimation`/`QTimer` 驱动动画（如 FluProgressBar、FluProgressRing）
- 顶层悬浮控件：`Qt::ToolTip` 窗口标志 + 事件过滤器 + 淡入淡出动画（如 FluToolTip）