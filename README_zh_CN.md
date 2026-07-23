<h1 align="center">
  Cpp FluentUI 
</h1>

<p align="center">
  一个基于 Qt C++ 的 Fluent Design 风格组件库
</p>

<p align="center">
简体中文 | <a href="README.md">English</a>
</p>

<div align=center>
  <img src="docs/gallery-atomOneDark.png">
</div>

## 特性

+ **187+ Fluent Design 控件**，基于 Qt C++ (C++17)
+ **3 套内置主题**：Light、Dark、Atom One Dark
+ **2300+ 图标**，基于 Segoe Fluent Icons 字体
+ 实时主题切换（信号槽机制）
+ 国际化支持（i18n）：中文（zh-CN）、英文（en-US）
+ 跨平台：Windows、Linux、macOS
+ Gallery 示例应用，附带代码示例

## 环境要求

+ CMake >= 3.20
+ Qt 6.x（已测试 Qt 6.5.1、6.7.1、6.8.3、6.9.0）或 Qt 5.x
+ C++17 编译器
+ **Windows**：Visual Studio 2022
+ **Linux**：GCC
+ **macOS**：Clang

> 需要的 Qt 模块：Core、Widgets、Svg、Charts、Core5Compat、Multimedia、ShaderTools、ImageFormats、Speech、3D、SCXML

## 快速开始

### 使用 Visual Studio 2022 构建

1. 克隆仓库：

   ```shell
   git clone https://github.com/mowangshuying/FluentUI.git
   ```

2. 使用 Visual Studio 2022 打开 `FluentUI.sln`。

3. 编译解决方案。

4. 将 **Gallery** 设置为启动项目并运行。

### 使用 Qt Creator 构建

1. 克隆仓库：

   ```shell
   git clone https://github.com/mowangshuying/FluentUI.git
   ```

2. 使用 Qt Creator 打开 `CMakeLists.txt`。

3. 编译项目。

### 使用 CMake 命令行构建

1. 克隆仓库：

   ```shell
   git clone https://github.com/mowangshuying/FluentUI.git
   ```

2. 使用 Ninja 构建（推荐）：

   ```shell
   mkdir build && cd build
   cmake -DCMAKE_PREFIX_PATH=/path/to/Qt -GNinja ..
   cmake --build .
   ```

### 快速构建（Windows）

运行 `build&pack.bat` 一键完成配置、构建和打包（需要 Visual Studio 2022 和 Qt 6.5.1）。

   ```shell
   build&pack.bat
   ```

### CMake 选项

| 选项 | 默认值 | 说明 |
|------|--------|------|
| `USE_QRC` | `TRUE` | 使用 Qt 资源文件（qrc）构建 |
| `BUILD_GALLERY` | `TRUE` | 构建 Gallery 示例应用 |

## 第三方库

| 库 | 许可证 | 说明 |
|-----|--------|------|
| [framelesshelper](https://github.com/nicehash/framelesshelper) | MIT | 无边框窗口辅助库 |
| [Qt-Advanced-Docking-System](https://github.com/nicehash/Qt-Advanced-Docking-System) | LGPL v2.1 | 高级停靠系统 |
| [qscintilla](https://www.riverbankcomputing.com/software/qscintilla/) | GPL v3 | 代码编辑器组件 |
| [qrcode](https://github.com/nayuki/QR-Code-generator) | MIT | 二维码生成 |
| [cmark](https://github.com/commonmark/cmark) | BSD 2-Clause | CommonMark 解析器 |
| [qwindowkit](https://github.com/stdware/qwindowkit) | Apache 2.0 | 窗口工具包 |

> 所有第三方库以源代码形式集成在 `3rdparty/` 目录中。

## 项目结构

```
FluentUI/
├── Controls/       # 187+ Fluent Design 控件（静态库）
├── Examples/       # 75 个控件演示（可执行文件）
├── Gallery/        # 完整演示应用（58 个页面）
├── Utils/          # 主题/图标/配置工具类（静态库）
├── 3rdparty/       # 6 个第三方库（源码集成）
├── StyleSheet/     # 566 个 QSS 文件（3 套主题）
├── i18n/           # 国际化（zh-CN, en-US）
├── code/           # Markdown 代码示例（54 个文件）
├── res/            # 图片、字体、Emoji SVG
├── docs/           # 文档和截图
└── config/         # 运行时配置
```

## 架构

```
Gallery / Examples
  └── FluentUI::Controls（静态库）
        ├── FluWidget          # 基类，提供主题感知
        ├── FluFrameLessWidget # 无边框窗口（framelesshelper）
        ├── FluWindowKitWidget # 窗口工具包集成
        └── FluentUI::Utils    # 主题/图标/配置管理
```

### 控件分类

| 分类 | 控件 |
|------|------|
| **按钮** | FluPushButton、FluToggleButton、FluSplitButton、FluDropDownButton、FluAppBarButton... |
| **输入** | FluLineEdit、FluSearchLineEdit、FluPasswordBox、FluSpinBox、FluAutoSuggestBox... |
| **选择** | FluCheckBox、FluRadioButton、FluToggleSwitch、FluComboBox、FluSegmented... |
| **导航** | FluVNavigationView、FluHNavigationView、FluMSNavigationView... |
| **对话框** | FluDialog、FluMessageBox、FluConfirmFlyout、FluTeachingTip、FluInfoBar... |
| **日期/时间** | FluCalendarView、FluCalendarDatePicker、FluDatePicker、FluTimePicker... |
| **布局** | FluExpander、FluPivot、FluStackedLayout、FluFlowLayout... |
| **代码编辑** | FluCodeBox、FluScintilla、FluTerminalWidget... |

## 文档

详细文档和代码示例请参见 [docs](./docs) 目录。

## 参考

+ [microsoft/WinUI-Gallery](https://github.com/microsoft/WinUI-Gallery) - WinUI 和 Fluent Design System 示例
+ [zhiyiYo/PyQt-Fluent-Widgets](https://github.com/zhiyiYo/PyQt-Fluent-Widgets) - PyQt Fluent Design 控件库
+ [Sepera-okeq/QtFluentWin11](https://github.com/Sepera-okeq/QtFluentWin11) - Windows 11 风格的 Qt Fluent Design
+ [zhuzichu520/FluentUI](https://github.com/zhuzichu520/FluentUI) - QML 版 FluentUI

## 许可证

本项目基于 [GNU 宽松通用公共许可证 v2.1](LICENSE.LGPL)。

## 历史点赞

![Star History Chart](https://api.star-history.com/svg?repos=mowangshuying/FluentUI&type=Date)
