# Gallery-v1.0.9

> 发布时间 2026-10-10 ｜ 66 次提交（2026-08 → 2026-10）｜ 364 个文件变更，+8827 / -4596

---

## 🆕 新增控件

- **FluToolTip**：自绘圆角气泡，167ms 淡入淡出、悬停延迟、自动隐藏、屏幕边缘自动避让；支持 Top/Bottom/Left/Right 及四角共 8 种 Placement；三套主题 QSS + Gallery 页面与独立示例
- **FluInfoBar**：WinUI 3 风格持久横幅，支持 `Informational/Success/Warning/Error` 四种 severity、title/message/isOpen/isClosable；`FluInfoBarMgr` 用平滑位移动画取代 1ms 轮询定时器，右下角 toast 堆叠在新增时可自动重排

## 🎨 控件重写与视觉升级

- **FluProgressBar**：从 QSS 渲染改为 `paintEvent` 自绘；新增 indeterminate 滑动动画（40% 进度块 + 三次缓动、2.0s 循环、双错位进度块）、`State` 枚举（Normal/Paused/Error）与状态切换 167ms 淡入淡出；高度 3px、圆角 1.5px/0.5px 对齐 WinUI 3 规范
- **FluProgressRing**：determinate 用 `QPropertyAnimation`（200ms OutCubic）平滑过渡，indeterminate 改为 90° 弧线连续顺时针旋转不再跳角；线宽随尺寸自适应（25px 小环协调）；新增 `progressColor/trackColor/textColor` 属性与三套主题 QSS
- **FluRatingControl**：改为自绘实现，支持半星显示
- **FluSlider**：整体优化，新增刻度尺式 tick marks（可设间隔）与主题化数值气泡，并修正气泡定位
- **FluTabBar**：WinUI 3 风格标签视觉（绘制层 + 接缝圆弧），随后进一步以纯 QSS 替换自绘并提升深色模式对比度；垂直居中与布局逻辑优化
- **FluPushButton / FluHyperLinkButton**：按钮外观对齐 WinUI 3；超链接按钮样式重构并移除 focus outline

## 🍴 编辑控件接入 Fluent 右键菜单

- `FluLineEdit`、`FluTextEdit`、`FluSpinBox`、`FluDoubleSpinBox`、`FluSearchLineEdit`、`FluPasswordBox`、`FluAutoSuggestBox` 的右键菜单由原生 `QMenu` 统一切换为 **FluPMenu**
- 新增 `FluPMenu::fromStandardMenu()` / `execStandardContextMenu()`，迁移 Qt 标准编辑动作（剪切/复制/粘贴/撤销等），支持子菜单递归转换与安全的 action 所有权转移

## 🔧 控件收敛与重命名（含破坏性变更）

- `FluComboBoxEx` → **`FluComboBox`**（旧 `FluComboBox`、`FluComboBoxTextItem` 移除）
- `FluCircleDot` → **`FluDotInfoBadge`**
- `FluToggleSwitchEx` / `FluTextToggleSwitchEx` 合并为统一的 **`FluToggleSwitch`**，并补充尺寸变体
- `FluShortInfoBar` 合并进 **`FluInfoBar`**
- PySide6 绑定的 typesystem 与示例脚本同步更新

## ✨ 功能增强

- **FluColorPicker**：`FluColorPickerButton` 集成取色交互（预设色 + 自由取色 flyout，发出 `colorChanged`）；`findColor` 改为缓存图像 + 最近邻 RGB 匹配，避免 O(n²) 开销
- **FluTableView**：新增列排序（`setSortingEnabled`）与空数据 "No data" 提示，修复 `setItemDelegate` 与 `initStyleOption` 变量遮蔽，复选框随主题着色，按压/选中行反馈与编辑器几何优化
- **FluToggleButton**：修复 `setToggled` 不刷新问题，新增 `toggledChanged` 信号与示例
- **FluDisplayBox / FluDisplayBoxEx**：新增 `setCodeByPath()` 便捷方法
- **FluVScrollView / FluFWScrollView**：新增布局便捷方法，简化 Gallery 调用点
- **FluSettingsVersionBox**：`addWidget()` 去掉横向拉伸因子，超链接按钮保持 sizeHint 宽度并与标签左对齐

## 🐛 稳定性与布局修复

- Expander：内容高度通过 `sizeHint` + `updateGeometry` 正确传播，折叠态下内容变化后几何保持刷新，非法 opacity QSS 改为 disabled 态配色
- 垂直导航：flyout 菜单高度计算与紧凑模式箭头显示修复
- ListView：delegate 与 view widget 所有权修正，消除悬空指针
- FluMenu：禁用项与可用项视觉区分；`FluMenu` 主题刷新改用 `qobject_cast` 安全转换
- FluCalendarView：主题切换时标题按钮保持无边框，修正 AtomOneDark 配色
- FluHRadioGroupBox：补齐三套主题缺失的 QSS
- InfoBar：启动时先入父容器再弹出，避免脱离窗口的悬浮窗
- FluProgressRing：working 定时器以环为父对象，避免悬空指针

## 🖌️ 样式与主题

- 全量 QSS 颜色格式统一为 `rgb()`，覆盖 light / dark / atomOneDark 三套主题
- 新增 15 个 QSS（FluToolTip、FluToolTipPage、FluInfoBar、FluProgressRing、FluHRadioGroupBox × 3 主题），移除 9 个随控件合并废弃的 QSS
- Gallery 默认主题切换为 AtomOneDark

## 🛠️ 构建、脚本与仓库

- CMake Presets 的 `QTDIR` 更新为 Qt 6.9.0（msvc2022_64）
- 修复 `build&pack / clean / lrelease / lupdate / package / pushTag / format` 等脚本（统一切到仓库根目录执行）
- 生成的 `.pyi` / `.sip` 标记为 `linguist-generated`，GitHub 语言统计不再计入
- 全库 clang-format 一遍

## 📝 文档与示例

- 新增 14 个 Gallery 代码示例文件（ColorPicker、ComboBox、InfoBadge、MenuBar、ProgressBar、Slider、ToggleButton、ToggleSwitch、ToolTip 等），修复并补全控件示例代码引用，注册缺失的 `ProgressBarPageCode2` 资源
- README 更新并移除 star history 图表
- i18n 翻译更新并重新生成 `.qm`；版本号标签同步至 1.0.9
