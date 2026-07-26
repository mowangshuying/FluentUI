# FluentUI Python 绑定移植文档

## 概述

本文档记录了 FluentUI Qt C++ 组件库通过 Shiboken6/PySide6 移植为 Python 绑定的完整过程。

- **项目**: FluentUI - Qt C++ Fluent Design 组件库
- **绑定工具**: Shiboken6 6.8.3 + PySide6 6.8.3
- **Python 版本**: 3.13.1
- **Qt 版本**: 6.8.1 (msvc2022_64)
- **产物**: `build/python/Release/FluentUI.pyd` (35.7 MB)
- **绑定类数量**: 140+ 个类

---

## 移植架构

```
python/
├── CMakeLists.txt                    # 绑定构建配置
├── typesystems/
│   └── fluentui_typesystem.xml       # Shiboken 类型系统定义
├── test_bindings.py                  # 基础绑定测试
├── MIGRATION_DOC.md                  # 本文档
└── examples/
    ├── demo_all_controls.py          # 全控件综合演示
    ├── demo_navigation.py            # 导航视图演示
    ├── demo_theme.py                 # 主题切换演示
    ├── demo_dialogs.py               # 弹窗/菜单演示
    └── demo_input.py                 # 输入控件演示
```

---

## 移植过程

### 第一阶段：基础设施搭建

**提交**: `996c9e98` - Add PySide6 Python bindings support

- 创建 `python/CMakeLists.txt`，配置 Shiboken6 代码生成流程
- 创建 `python/typesystems/fluentui_typesystem.xml` 类型系统文件
- 初始绑定 3 个基础类：`FluWidget`、`FluPushButton`、`FluIconButton`
- 配置 Shiboken6 的 include-paths、typesystem-paths
- 设置 MSVC 编译选项和链接库

**关键技术点**:
- Shiboken6 可执行文件位于 `shiboken6_generator` 包中
- PySide6 库文件名为 `pyside6.abi3.lib`（非 `PySide6.lib`）
- Shiboken6 头文件位于 `shiboken6_generator/include`（非 `shiboken6/include`）
- 需要 `target_link_directories` 添加 Python libs 目录

### 第二阶段：Utils 工具类绑定

**提交**: `68d81365` - feat(python): add Utils bindings

绑定 8 个工具类：

| 类名 | 说明 | 特殊处理 |
|------|------|----------|
| FluThemeUtils | 主题管理 | - |
| FluConfigUtils | 配置管理 | 排除 m_configUtils、m_settings 字段 |
| FluStyleSheetUtils | QSS 加载 | 排除 std::map 重载函数 |
| FluIconUtils | 图标工具 | - |
| FluLogUtils | 日志工具 | - |
| FluTranslatorUtils | 翻译工具 | - |
| FluEmoijUtils | Emoji 工具 | - |
| FluObjectPtrUtils | 对象指针跟踪 | - |

**遇到的问题**:
- `FluConfigUtils` 的 `m_configUtils` 是 protected 静态成员，Shiboken 生成的代码无法访问
- **解决方案**: 使用 `<modify-field name="m_configUtils" remove="all"/>` 排除该字段
- `FluStyleSheetUtils` 有 `std::map<QString, QString>` 参数重载
- **解决方案**: 使用 `<modify-function signature="..." remove="all"/>` 排除 std::map 重载

### 第三阶段：按钮类控件绑定

**提交**: `7122769f` - feat(python): add button controls bindings

绑定 20 个按钮类控件：
- FluCheckBox, FluRadioButton, FluToggleButton
- FluDropDownButton, FluSplitButton, FluRepeatButton
- FluHyperLinkButton, FluAppBarButton, FluAppBarToggleButton
- FluStyleButton, FluScaleButton, FluRotationButton
- FluGraphicalButton, FluThemeButton, FluPPushButton
- FluWindowkitButton, FluCommandBarItem 及其子类

### 第四阶段：输入类控件绑定

**提交**: `ac4a5625` - feat(python): add input controls bindings

绑定 13 个输入类控件：
- FluLineEdit, FluTextEdit, FluSpinBox, FluDoubleSpinBox
- FluPasswordBox, FluSearchLineEdit
- FluComboBox, FluComboBoxEx, FluComboBoxTextItem
- FluIntValidator, FluSlider, FluRatingControl

### 第五阶段：导航类控件绑定

**提交**: `4c92272a` - feat(python): add navigation controls bindings

绑定 12 个导航类控件：
- FluTabBar, FluTabBarContent, FluTabBarItem
- FluTabView, FluTabWidget
- FluPagination, FluPaginationItem
- FluPivot, FluPivotTitleBar, FluPivotTitleBarItem
- FluSegmented, FluSegmentedItem

### 第六阶段：显示类控件绑定

**提交**: `385a81c3` - feat(python): add display controls bindings

绑定 15 个显示类控件：
- FluLabel, FluProgressBar, FluProgressRing, FluBusyProgressRing
- FluInfoBadge, FluCircleDot, FluImageBox
- FluDisplayBox, FluDisplayBoxEx, FluDisplayIconBox
- FluInstructions, FluTriangle, FluStar
- FluTimeLine, FluTimeLineIcon, FluTimeLineItem

### 第七阶段：容器类控件绑定

**提交**: `f427f83c` - feat(python): add container controls bindings

绑定 15 个容器类控件：
- FluExpander, FluScrollArea
- FluVScrollView, FluHScrollView
- FluTableView, FluListView, FluTreeView
- FluVCard, FluHCard, FluBorder
- FluCodeBox, FluCodeExpander
- FluLoopView, FluHFlipView, FluVFlipView

### 第八阶段：弹窗类控件绑定

**提交**: `f2935dca` - feat(python): add popup/dialog controls bindings

绑定 15 个弹窗类控件：
- FluDialog, FluMessageBox
- FluMenu, FluMenuBar, FluAction
- FluRoundMenu, FluRoundMenuView
- FluTeachingTip, FluTeachingTipContent
- FluVFlyout, FluConfirmFlyout
- FluPMenu, FluPMenuBar
- FluIndicatorRoundMenu, FluCompleterMenu

### 第九阶段：窗口类控件绑定

**提交**: `c6c01b40` - feat(python): add window controls bindings

绑定 3 个 WindowKit 窗口类控件：
- FluWindowKitWidget, FluWindowKitTitleBar, FluWindowKitWindow

### 第十阶段：其他控件绑定

**提交**: `a0834e3d` - feat(python): add remaining controls bindings

绑定 15 个其他控件：
- FluToggleSwitch, FluToggleSwitchEx, FluTextToggleSwitchEx
- FluColorPickerButton, FluColorButton
- FluVSplitLine, FluHSplitLine
- FluVRadioGroupBox, FluHRadioGroupBox
- FluCalendarView, FluCalendarDatePicker, FluDatePicker
- FluSettingsLabelBox, FluSettingsSelectBox, FluSettingsVersionBox

### 第十一阶段：修复排除控件

**提交**: `13895baf` - fix(python): resolve binding issues for previously excluded controls

修复并重新绑定：
- **FluGifBox**: 前向声明 QMovie，避免 Clang 解析 `qplugin.h` 的 constexpr 错误
- **FluShortInfoBar**: 修复 `#pragma` 拼写错误为 `#pragma once`
- **FluInfoBarMgr**: 排除 `std::map<QWidget*, std::list<FluShortInfoBar*>>` 成员

### 第十二阶段：导航视图完整绑定

**提交**: `9fe88de1` - feat(python): add navigation views, AutoSuggestBox, TextEditWrap bindings

修复循环依赖并绑定：
- **FluVNavigationView** 及全部 V 导航子项（8 个类）
- **FluHNavigationView** 及全部 H 导航子项（8 个类）
- **FluAutoSuggestBox**: 前向声明 FluCompleterMenu 打破循环
- **FluTextEditWrap**: 前向声明 FluTextEdit 打破循环

**循环依赖解决方案**:
```cpp
// FluVNavigationSearchItem.h - 修改前
#include "FluAutoSuggestBox.h"

// FluVNavigationSearchItem.h - 修改后
class FluAutoSuggestBox;  // 前向声明
#include <QPushButton>     // 补充缺失的 include
```

### 第十三阶段：示例脚本

**提交**: `69d20006` - feat(python): add comprehensive example scripts

创建 5 个 Python 示例脚本：
- `demo_all_controls.py`: 全控件分类综合演示
- `demo_navigation.py`: VNavigationView 导航演示
- `demo_theme.py`: 主题切换演示
- `demo_dialogs.py`: Dialog/MessageBox/RoundMenu/Menu 演示
- `demo_input.py`: 输入控件综合演示

---

## 排除的控件及原因

| 控件 | 原因 | 技术细节 |
|------|------|----------|
| FluFrameLessWidget | 外部基类不可解析 | 继承自 `wangwenx190::FramelessHelper::FramelessWidget`，Shiboken 无法解析第三方命名空间基类 |
| FluFrameLessWidgetEx | 同上 | 同上 |
| FluFrameLessTitleBar | 依赖 FramelessHelper 宏 | 使用 `FRAMELESSHELPER_PREPEND_NAMESPACE` 宏 |
| FluStackedLayout | Shiboken QLayout bug | 生成代码调用 `addLayoutOwnership` 函数，该函数在 Shiboken 6.8.3 中未正确导出 |
| FluFlowLayout | 同上 | 同上 |

---

## 关键技术问题及解决方案

### 1. QMovie Clang 解析错误

**问题**: `FluGifBox.h` 包含 `<QMovie>`，QMovie 内部包含 `qplugin.h`，其中有 `constexpr` 变量使用 `reinterpret_cast`，Clang 拒绝解析。

**解决**: 在头文件中前向声明 `class QMovie;`，将 `#include <QMovie>` 移至 `.cpp` 文件。

### 2. 循环依赖

**问题**: `FluAutoSuggestBox` ↔ `FluCompleterMenu` 互相包含；`FluTextEdit` ↔ `FluTextEditWrap` 互相包含。

**解决**: 将 `#include` 替换为前向声明 `class Xxx;`，在 `.cpp` 中保留完整 include。

### 3. std::map/std::vector 参数

**问题**: Shiboken 无法自动生成 `std::map<QWidget*, std::list<FluShortInfoBar*>>` 等复杂 STL 容器的绑定代码。

**解决**: 使用 `<modify-field name="..." remove="all"/>` 排除相关成员，或使用 `<modify-function signature="..." remove="all"/>` 排除相关函数。

### 4. QLayout 子类 addLayoutOwnership

**问题**: Shiboken 6.8.3 为 QLayout 子类生成的代码调用 `addLayoutOwnership()` 函数，但该函数未在链接时正确导出。

**解决**: 暂时排除 FluStackedLayout 和 FluFlowLayout。用户可直接使用 PySide6 内置的 QStackedLayout/QLayout。

### 5. 第三方库基类

**问题**: FramelessHelper 控件继承自 `wangwenx190::FramelessHelper::FramelessWidget`，Shiboken 无法解析该命名空间下的基类。

**解决**: 暂时排除。需要为 FramelessHelper 创建独立的 typesystem 文件才能解决。

### 6. #pragma 拼写错误

**问题**: `FluShortInfoBar.h` 第一行为 `#pragma`（缺少 `once`），导致重复包含时类型重定义。

**解决**: 修正为 `#pragma once`。

---

## 构建命令

```bash
# 配置（需要 PySide6 6.8.3 + Shiboken6）
cmake -DBUILD_PYTHON_BINDINGS=ON \
      -DCMAKE_PREFIX_PATH=C:/Qt/6.8.1/msvc2022_64 \
      -G"Visual Studio 17 2022" -A x64 ..

# 构建
cmake --build . --config Release --target FluentUI_Python
```

## 运行示例

```python
import os, sys

# Windows DLL 路径设置
os.add_dll_directory(r'E:\code\FluentUI-Master\build\bin')
os.add_dll_directory(r'C:\Qt\6.8.1\msvc2022_64\bin')
os.add_dll_directory(r'<PySide6 安装路径>')
os.add_dll_directory(r'<shiboken6 安装路径>')

sys.path.insert(0, r'E:\code\FluentUI-Master\build\python\Release')

from FluentUI import FluPushButton, FluThemeUtils
# ... 使用控件
```

---

## 绑定统计

| 分类 | 绑定数量 | 说明 |
|------|----------|------|
| Utils 工具类 | 8 | 主题、配置、样式表、图标等 |
| 按钮类 | 20 | PushButton、CheckBox、RadioButton 等 |
| 输入类 | 13 | LineEdit、ComboBox、SpinBox 等 |
| 导航类 | 28 | TabBar、Pagination、V/HNavigationView 及子项 |
| 显示类 | 15 | Label、ProgressBar、TimeLine 等 |
| 容器类 | 15 | Expander、ScrollArea、TableView 等 |
| 弹窗类 | 15 | Dialog、MessageBox、RoundMenu 等 |
| 窗口类 | 3 | WindowKit 系列 |
| 其他 | 15 | ToggleSwitch、Calendar、ColorPicker 等 |
| **总计** | **~140+** | |
| 排除 | 5 | FramelessHelper(3) + QLayout(2) |

---

## 提交历史

```
69d20006 feat(python): add comprehensive example scripts
9fe88de1 feat(python): add navigation views, AutoSuggestBox, TextEditWrap bindings
13895baf fix(python): resolve binding issues for previously excluded controls
a0834e3d feat(python): add remaining controls bindings
c6c01b40 feat(python): add window controls bindings
f2935dca feat(python): add popup/dialog controls bindings
f427f83c feat(python): add container controls bindings
385a81c3 feat(python): add display controls bindings
4c92272a feat(python): add navigation controls bindings
ac4a5625 feat(python): add input controls bindings
7122769f feat(python): add button controls bindings
68d81365 feat(python): add Utils bindings
f3a59973 docs(agents): add Python bindings documentation
996c9e98 Add PySide6 Python bindings support
```

---

## 后续可扩展方向

1. **FramelessHelper 绑定**: 为 FramelessHelper 创建独立 typesystem，解析 `wangwenx190` 命名空间
2. **QLayout 子类**: 等待 Shiboken 修复 `addLayoutOwnership` 导出问题，或手动注入该函数声明
3. **枚举绑定**: 为 FluTheme、FluAwesomeType 等枚举创建 Python 枚举映射
4. **信号/槽完善**: 部分控件的信号参数使用了自定义类型，需要注册元类型
5. **文档生成**: 使用 Shiboken 的文档生成工具自动生成 API 文档
