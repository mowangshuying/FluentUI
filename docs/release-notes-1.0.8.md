# Gallery-v1.0.8

> 发布时间 2026-08-02 ｜ 289 次提交（2025-10 → 2026-08）

---

## 🐍 PySide6 Python 绑定（全新支持）

- 基于 Shiboken6 新增完整 PySide6 绑定，支持构建 wheel 包（`PySide6FluentUI`）并在 PyPI 发布
- 覆盖全部主要控件类别：按钮、输入、导航、容器、显示、弹窗/对话框、窗口控件及工具类；新增 `FluStackedLayoutWrap` 绕过 Shiboken 的 QLayout 限制
- 提供详细迁移文档与示例脚本，支持 PySide6 6.9.0 + LLVM 18 + 静态链接

## 🧭 横向导航栏 FluHNavigation 重构

- Gallery 集成横向导航栏并带切换动画；支持分组子项 flyout（下拉动画、居中对齐、主题适配）
- 自绘 `FluHNavigationIndicator` 选中指示器（平滑伸缩动画）
- 页面边框随导航模式切换（水平/垂直），全部三套主题适配
- 导航状态跨会话持久化；修复点击穿透、选中重置、hover 残留等 10+ 项问题

## 📐 垂直导航栏 WinUI3 风格

- WinUI3 风格条目布局与图标渲染，指示器高度动画与圆角优化，主题/配色修复

## ⚡ 主题切换性能优化

- `themeChanged` 延迟到 `QTimer::singleShot`，批量 QSS 更新 + 缓存 + 跳过隐藏控件
- 点击响应从 ~13s 降至 <1ms

## 🏗️ 工程结构重构

- 顶层目录统一为小写（`Stylesheet→stylesheet` 等），脚本集中到 `scripts/`，`python/` 迁移为 `bindings/PySide6`
- 全部 3rdparty 库改为静态构建（FramelessHelper、Qt-Advanced-Docking-System 等）
- 移除 IconTool；API 别名统一为 `FluentUI::Controls` / `FluentUI::Utils`

## 🔧 构建与 CI

- 打包瘦身：安装阶段剔除 `include/lib/share`，Gallery.zip 仅含运行时文件
- qrc 资源低优化编译，降低 CI 内存占用；修复 GitHub Actions（Qt 6.9.0、路径大小写、过时 actions）

## 🎨 控件修复与样式统一

- `FluComboBoxEx` 选中指示器同步、`FluIndicatorMenuItemDelegate` 位置计算、`FluTreeView`、`FluCalendarViewTitle`、滚动条、`FluPMenu/FluPMenuBar`、`FluMessageBox` 等多项修复
- CheckBox/RadioButton 缩小 0.8x，菜单/下拉/按钮圆角统一 8px，AtomOneDark 主题修正

## 📝 文档与其他

- README 重构（构建信息、第三方许可、项目结构）；Gallery zh-CN 翻译补全；全库命名规范化与死代码清理`
