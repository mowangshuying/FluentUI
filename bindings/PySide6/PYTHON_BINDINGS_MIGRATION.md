# FluentUI Python 绑定移植文档

## 概述

本文档记录了将 FluentUI Qt C++ 控件库通过 Shiboken6/PySide6 绑定到 Python 的完整移植过程。

- **绑定工具**: Shiboken6 6.8.3 + PySide6 6.8.3
- **Qt 版本**: Qt 6.8.1 (msvc2022_64)
- **Python 版本**: Python 3.13.1
- **产物**: `build/python/Release/FluentUI.pyd` (35.7 MB)
- **绑定类数量**: 140+ 个类

---

## 构建方法

```bash
# 配置（需要 PySide6 6.8.3 + Shiboken6 已通过 pip 安装）
cmake -DBUILD_PYTHON_BINDINGS=ON -DCMAKE_PREFIX_PATH=C:/Qt/6.8.1/msvc2022_64 -G"Visual Studio 17 2022" -A x64 ..

# 编译
cmake --build . --config Release --target FluentUI_Python
```

---

## 移植过程（按提交顺序）

### 第 1 阶段：基础框架搭建 (`996c9e98`)

- 创建 `python/CMakeLists.txt`，配置 Shiboken6 代码生成流程
- 创建 `python/typesystems/fluentui_typesystem.xml` 类型系统文件
- 初始绑定 3 个核心类：`FluWidget`、`FluPushButton`、`FluIconButton`
- 创建 `python/test_bindings.py` 验证脚本

### 第 2 阶段：Utils 工具类 (`68d81365`)

绑定 8 个工具类：
- `FluThemeUtils` - 主题管理
- `FluConfigUtils` - 配置管理（排除 `m_configUtils`、`m_settings`  protected 成员）
- `FluStyleSheetUtils` - QSS 样式表加载（排除 `std::map` 重载）
- `FluIconUtils` - 图标工具
- `FluLogUtils` - 日志工具
- `FluTranslatorUtils` - 翻译工具
- `FluEmoijUtils` - Emoji 工具
- `FluObjectPtrUtils` - 对象指针追踪

### 第 3 阶段：按钮类控件 (`7122769f`)

绑定 20 个按钮类：
- `FluCheckBox`、`FluRadioButton`、`FluToggleButton`
- `FluDropDownButton`、`FluSplitButton`、`FluRepeatButton`
- `FluHyperLinkButton`、`FluAppBarButton`、`FluAppBarToggleButton`
- `FluStyleButton`、`FluScaleButton`、`FluRotationButton`
- `FluGraphicalButton`、`FluThemeButton`、`FluPPushButton`
- `FluWindowkitButton`
- `FluCommandBarItem`、`FluCommandBarIconItem`、`FluCommandBarIconTextItem`、`FluCommandBarSplitItem`

### 第 4 阶段：输入类控件 (`ac4a5625`)

绑定 14 个输入类：
- `FluLineEdit`、`FluTextEdit`、`FluSpinBox`、`FluDoubleSpinBox`
- `FluPasswordBox`、`FluSearchLineEdit`
- `FluComboBox`、`FluComboBoxEx`、`FluComboBoxTextItem`
- `FluIntValidator`、`FluSlider`、`FluRatingControl`

### 第 5 阶段：导航类控件 (`4c92272a`)

绑定 12 个导航类：
- `FluTabBar`、`FluTabBarContent`、`FluTabBarItem`
- `FluTabView`、`FluTabWidget`
- `FluPagination`、`FluPaginationItem`
- `FluPivot`、`FluPivotTitleBar`、`FluPivotTitleBarItem`
- `FluSegmented`、`FluSegmentedItem`

### 第 6 阶段：显示类控件 (`385a81c3`)

绑定 19 个显示类：
- `FluLabel`、`FluProgressBar`、`FluProgressRing`、`FluBusyProgressRing`
- `FluInfoBadge`、`FluCircleDot`、`FluImageBox`
- `FluDisplayBox`、`FluDisplayBoxEx`、`FluDisplayIconBox`
- `FluInstructions`、`FluTriangle`、`FluStar`
- `FluTimeLine`、`FluTimeLineIcon`、`FluTimeLineItem`

### 第 7 阶段：容器类控件 (`f427f83c`)

绑定 19 个容器类：
- `FluExpander`、`FluScrollArea`
- `FluVScrollView`、`FluHScrollView`
- `FluTableView`、`FluListView`、`FluTreeView`
- `FluVCard`、`FluHCard`、`FluBorder`
- `FluCodeBox`、`FluCodeExpander`
- `FluLoopView`、`FluHFlipView`、`FluVFlipView`

### 第 8 阶段：弹窗类控件 (`f2935dca`)

绑定 20 个弹窗类：
- `FluDialog`、`FluMessageBox`
- `FluMenu`、`FluMenuBar`、`FluAction`
- `FluRoundMenu`、`FluRoundMenuView`
- `FluTeachingTip`、`FluTeachingTipContent`
- `FluVFlyout`、`FluConfirmFlyout`
- `FluPMenu`、`FluPMenuBar`
- `FluIndicatorRoundMenu`、`FluCompleterMenu`

### 第 9 阶段：窗口类控件 (`c6c01b40`)

绑定 3 个窗口类：
- `FluWindowKitWidget`、`FluWindowKitTitleBar`、`FluWindowKitWindow`

### 第 10 阶段：其他控件 (`a0834e3d`)

绑定 12 个其他类：
- `FluToggleSwitch`、`FluToggleSwitchEx`、`FluTextToggleSwitchEx`
- `FluColorPickerButton`、`FluColorButton`
- `FluVSplitLine`、`FluHSplitLine`
- `FluVRadioGroupBox`、`FluHRadioGroupBox`
- `FluCalendarView`、`FluCalendarDatePicker`、`FluDatePicker`
- `FluSettingsLabelBox`、`FluSettingsSelectBox`、`FluSettingsVersionBox`
- `FluGifBox`、`FluShortInfoBar`、`FluInfoBarMgr`

### 第 11 阶段：修复排除控件 (`13895baf`)

C++ 源码修改：
- `FluGifBox.h` - 前向声明 `QMovie`，避免 Clang 解析错误
- `FluShortInfoBar.h` - 修复 `#pragma` → `#pragma once`
- `FluAutoSuggestBox.h` - 前向声明 `FluCompleterMenu` 打破循环依赖
- `FluTextEditWrap.h` - 前向声明 `FluTextEdit` 打破循环依赖

### 第 12 阶段：导航视图完整绑定 (`9fe88de1`)

C++ 源码修改：
- `FluVNavigationSearchItem.h` - 前向声明 `FluAutoSuggestBox`，添加 `<QPushButton>` include

绑定 16 个导航视图类：
- V 系列：`FluVNavigationItem`、`FluVNavigationIconTextItem`、`FluVNavigationFlyIconTextItem`、`FluVNavigationIndicator`、`FluVNavigationMenuItem`、`FluVNavigationSearchItem`、`FluVNavigationSettingsItem`、`FluVNavigationView`
- H 系列：`FluHNavigationItem`、`FluHNavigationIconTextItem`、`FluHNavigationFlyIconTextItem`、`FluHNavigationIndicator`、`FluHNavigationMoreItem`、`FluHNavigationSearchItem`、`FluHNavigationSettingsItem`、`FluHNavigationView`

### 第 13 阶段：示例脚本 (`69d20006`)

创建 5 个示例脚本：
- `demo_all_controls.py` - 全控件分类总览
- `demo_navigation.py` - 导航视图示例
- `demo_theme.py` - 主题切换示例
- `demo_dialogs.py` - 弹窗/菜单示例
- `demo_input.py` - 输入控件示例

---

## 排除的控件及原因

| 控件 | 原因 | 技术细节 |
|------|------|----------|
| `FluFrameLessWidget` | 外部基类不可解析 | 继承自 `wangwenx190::FramelessHelper::FramelessWidget`，Shiboken 无法解析第三方命名空间基类 |
| `FluFrameLessWidgetEx` | 同上 | 同上 |
| `FluFrameLessTitleBar` | 依赖 FramelessHelper 宏 | 使用 `FRAMELESSHELPER_BEGIN_NAMESPACE` 等宏，Clang 解析失败 |
| `FluStackedLayout` | Shiboken QLayout bug | 生成的代码调用 `addLayoutOwnership` 函数，该函数在 Shiboken 6.8.3 中未正确导出 |
| `FluFlowLayout` | 同上 | 同上 |

---

## 关键技术问题及解决方案

### 1. 循环依赖 (Cyclic Dependency)

**问题**: Shiboken 检测到类之间的循环引用，无法生成代码。

**解决方案**: 在 C++ 头文件中将 `#include` 改为前向声明 (`class X;`)，将实际 include 移到 `.cpp` 文件。

**案例**:
- `FluAutoSuggestBox.h` ↔ `FluCompleterMenu.h`
- `FluTextEdit.h` ↔ `FluTextEditWrap.h`
- `FluVNavigationSearchItem.h` → `FluAutoSuggestBox.h`

### 2. QMovie Clang 解析错误

**问题**: `FluGifBox.h` 包含 `<QMovie>`，触发 `qplugin.h` 中的 `constexpr` 错误。

**解决方案**: 在头文件中前向声明 `class QMovie;`，将 `#include <QMovie>` 移到 `.cpp`。

### 3. std::map 成员绑定失败

**问题**: `FluInfoBarMgr` 的 `std::map<QWidget*, std::list<FluShortInfoBar*>>` 成员导致 Shiboken 生成错误的初始化代码。

**解决方案**: 使用 `<modify-field name="m_infoBarMap" remove="all"/>` 排除该成员。

### 4. QLayout 子类 addLayoutOwnership 错误

**问题**: Shiboken 6.8.3 为 QLayout 子类生成的代码调用 `addLayoutOwnership`，但该函数未正确导出。

**解决方案**: 暂时排除 `FluStackedLayout` 和 `FluFlowLayout`。用户可直接使用 PySide6 内置的 `QStackedLayout` 和 `QLayout`。

### 5. 外部库基类不可解析

**问题**: `FluFrameLessWidget` 继承自 FramelessHelper 库的 `FramelessWidget`，Shiboken 无法解析 `wangwenx190` 命名空间。

**解决方案**: 暂时排除 FramelessHelper 相关控件。这些是窗口级控件，Python 用户较少直接使用。

### 6. #pragma once 拼写错误

**问题**: `FluShortInfoBar.h` 第 1 行写的是 `#pragma` 而非 `#pragma once`，导致重复包含。

**解决方案**: 修正为 `#pragma once`。

---

## 类型系统修改技巧

### 排除 protected 成员
```xml
<object-type name="FluConfigUtils" generate="yes">
    <modify-field name="m_configUtils" remove="all"/>
    <modify-field name="m_settings" remove="all"/>
</object-type>
```

### 排除 std::map/std::vector 重载函数
```xml
<object-type name="FluStyleSheetUtils" generate="yes">
    <modify-function signature="getQssByFileName(const std::map&lt;QString, QString&gt; &amp;, const QString &amp;)" remove="all"/>
</object-type>
```

### 排除循环引用方法
```xml
<object-type name="FluVNavigationIconTextItem" generate="yes">
    <modify-field name="m_items" remove="all"/>
    <modify-field name="m_parentItem" remove="all"/>
    <modify-function signature="getItems()" remove="all"/>
    <modify-function signature="addItem(FluVNavigationIconTextItem *)" remove="all"/>
</object-type>
```

---

## 运行环境要求

```python
import os, sys

# Windows DLL 路径（必须）
os.add_dll_directory(r'E:\code\FluentUI-Master\build\bin')
os.add_dll_directory(r'C:\Qt\6.8.1\msvc2022_64\bin')
os.add_dll_directory(r'<python>\Lib\site-packages\PySide6')
os.add_dll_directory(r'<python>\Lib\site-packages\shiboken6')

# 模块路径
sys.path.insert(0, r'E:\code\FluentUI-Master\build\python\Release')

from FluentUI import FluPushButton, FluThemeUtils, ...
```

---

## 已绑定类完整列表 (140+)

### Utils (8)
FluThemeUtils, FluConfigUtils, FluStyleSheetUtils, FluIconUtils, FluLogUtils, FluTranslatorUtils, FluEmoijUtils, FluObjectPtrUtils

### Buttons (20)
FluPushButton, FluIconButton, FluCheckBox, FluRadioButton, FluToggleButton, FluDropDownButton, FluSplitButton, FluRepeatButton, FluHyperLinkButton, FluAppBarButton, FluAppBarToggleButton, FluStyleButton, FluScaleButton, FluRotationButton, FluGraphicalButton, FluThemeButton, FluPPushButton, FluWindowkitButton, FluCommandBarItem, FluCommandBarIconItem, FluCommandBarIconTextItem, FluCommandBarSplitItem

### Input (14)
FluLineEdit, FluTextEdit, FluTextEditWrap, FluSpinBox, FluDoubleSpinBox, FluPasswordBox, FluSearchLineEdit, FluComboBox, FluComboBoxEx, FluComboBoxTextItem, FluIntValidator, FluSlider, FluRatingControl, FluAutoSuggestBox

### Navigation (28)
FluTabBar, FluTabBarContent, FluTabBarItem, FluTabView, FluTabWidget, FluPagination, FluPaginationItem, FluPivot, FluPivotTitleBar, FluPivotTitleBarItem, FluSegmented, FluSegmentedItem, FluVNavigationView, FluVNavigationItem, FluVNavigationIconTextItem, FluVNavigationFlyIconTextItem, FluVNavigationIndicator, FluVNavigationMenuItem, FluVNavigationSearchItem, FluVNavigationSettingsItem, FluHNavigationView, FluHNavigationItem, FluHNavigationIconTextItem, FluHNavigationFlyIconTextItem, FluHNavigationIndicator, FluHNavigationMoreItem, FluHNavigationSearchItem, FluHNavigationSettingsItem

### Display (19)
FluLabel, FluProgressBar, FluProgressRing, FluBusyProgressRing, FluInfoBadge, FluCircleDot, FluImageBox, FluDisplayBox, FluDisplayBoxEx, FluDisplayIconBox, FluInstructions, FluTriangle, FluStar, FluTimeLine, FluTimeLineIcon, FluTimeLineItem, FluGifBox, FluShortInfoBar, FluInfoBarMgr

### Containers (15)
FluExpander, FluScrollArea, FluVScrollView, FluHScrollView, FluTableView, FluListView, FluTreeView, FluVCard, FluHCard, FluBorder, FluCodeBox, FluCodeExpander, FluLoopView, FluHFlipView, FluVFlipView

### Popup/Dialog (15)
FluDialog, FluMessageBox, FluMenu, FluMenuBar, FluAction, FluRoundMenu, FluRoundMenuView, FluTeachingTip, FluTeachingTipContent, FluVFlyout, FluConfirmFlyout, FluPMenu, FluPMenuBar, FluIndicatorRoundMenu, FluCompleterMenu

### Window (3)
FluWindowKitWidget, FluWindowKitTitleBar, FluWindowKitWindow

### Other (15)
FluToggleSwitch, FluToggleSwitchEx, FluTextToggleSwitchEx, FluColorPickerButton, FluColorButton, FluVSplitLine, FluHSplitLine, FluVRadioGroupBox, FluHRadioGroupBox, FluCalendarView, FluCalendarDatePicker, FluDatePicker, FluSettingsLabelBox, FluSettingsSelectBox, FluSettingsVersionBox

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

## 后续扩展建议

1. **FramelessHelper 控件**: 等待 Shiboken 支持第三方命名空间基类，或创建中间包装层
2. **FluStackedLayout/FluFlowLayout**: 等待 Shiboken 修复 QLayout `addLayoutOwnership` 问题
3. **枚举绑定**: 当前枚举（如 `FluTheme`、`FluAwesomeType`）未绑定为 Python 枚举，可后续添加 `<enum-type>` 声明
4. **信号/槽**: 大部分信号已自动绑定，部分复杂信号可能需要 `<modify-function>` 调整
