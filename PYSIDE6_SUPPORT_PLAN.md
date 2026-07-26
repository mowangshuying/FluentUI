# PySide6 支持计划

## 概述

本计划旨在为 FluentUI C++ 库添加 PySide6 (Python) 支持，使 Python 开发者能够使用 Fluent Design 风格的 Qt 控件。

## 技术方案选择

### 方案对比

| 方案 | 优点 | 缺点 | 推荐度 |
|------|------|------|--------|
| **Shiboken6 绑定生成** | 自动化程度高，维护成本低，性能接近原生 | 需要编写类型系统文件，学习曲线陡峭 | ⭐⭐⭐⭐⭐ |
| **手动 PySide6 封装** | 完全控制 API 设计，可以 Python 化 | 工作量大，维护成本高，性能略低 | ⭐⭐⭐ |
| **纯 Python 重写** | 完全 Python 化，易于扩展 | 失去 C++ 性能优势，工作量巨大 | ⭐⭐ |

**推荐方案**: Shiboken6 绑定生成 + Python 友好层

## 实施阶段

### 阶段 1: 基础设施搭建 (2-3 周)

#### 1.1 环境准备
- [ ] 安装 PySide6 和 Shiboken6
- [ ] 配置 CMake 以支持 Python 绑定生成
- [ ] 创建 `python/` 目录结构

```
python/
├── bindings/           # 生成的绑定代码
├── fluentui/           # Python 包
│   ├── __init__.py
│   ├── controls/       # 控件模块
│   ├── utils/          # 工具模块
│   └── examples/       # Python 示例
├── typesystems/        # Shiboken 类型系统文件
├── CMakeLists.txt      # Python 绑定构建配置
└── setup.py            # Python 包安装配置
```

#### 1.2 CMake 集成
修改根 `CMakeLists.txt`，添加 Python 绑定选项：

```cmake
option(BUILD_PYTHON_BINDINGS "Build Python bindings" OFF)

if(BUILD_PYTHON_BINDINGS)
    find_package(PySide6 REQUIRED)
    find_package(Shiboken6 REQUIRED)
    add_subdirectory(python)
endif()
```

#### 1.3 依赖处理
评估第三方库的 Python 支持情况：
- **framelesshelper**: 需要单独绑定或寻找 Python 替代方案
- **qwindowkit**: 需要绑定或替代
- **qtadvanceddocking**: 已有 Python 绑定 (Qt-Advanced-Docking-System)
- **cmark**: Markdown 解析，可用 Python 库替代 (markdown, mistune)
- **qscintilla**: 已有 PySide6 支持

### 阶段 2: 核心工具库绑定 (1-2 周)

#### 2.1 Utils 库绑定
优先级：高（所有控件依赖）

需要绑定的类：
- `FluThemeUtils` - 主题管理
- `FluStyleSheetUtils` - 样式表管理
- `FluIconUtils` - 图标工具
- `FluConfigUtils` - 配置工具
- `FluTranslatorUtils` - 翻译工具

创建类型系统文件 `python/typesystems/fluentui_utils_typesystem.xml`：

```xml
<?xml version="1.0"?>
<typesystem package="FluentUI.Utils">
    <load-typesystem name="typesystem_core.xml" generate="no"/>
    <load-typesystem name="typesystem_widgets.xml" generate="no"/>
    
    <namespace-type name="FluThemeUtils">
        <modify-function signature="getUtils()" remove="all"/>
        <!-- 暴露为 Python 友好的静态方法 -->
    </namespace-type>
</typesystem>
```

#### 2.2 资源系统适配
- 将 `.qrc` 资源文件转换为 Python 可访问格式
- 提供 `FluResources` Python 模块加载资源

### 阶段 3: 基础控件绑定 (3-4 周)

#### 3.1 分批绑定策略
按复杂度和依赖关系分批：

**批次 1 - 基础控件** (1 周):
- FluWidget (基类)
- FluPushButton
- FluIconButton
- FluToggleButton
- FluCheckBox
- FluRadioButton
- FluLabel
- FluBorder

**批次 2 - 输入控件** (1 周):
- FluLineEdit
- FluComboBox
- FluSpinBox
- FluSlider
- FluProgressBar
- FluProgressRing

**批次 3 - 布局容器** (1 周):
- FluScrollArea
- FluStackedLayout
- FluPivot
- FluTabView
- FluExpander

**批次 4 - 高级控件** (1 周):
- FluTreeView
- FluTableView
- FluMenu
- FluDialog
- FluMessageBox

#### 3.2 类型系统文件示例

`python/typesystems/fluentui_controls_typesystem.xml`:

```xml
<?xml version="1.0"?>
<typesystem package="FluentUI.Controls">
    <load-typesystem name="typesystem_widgets.xml" generate="no"/>
    
    <!-- FluPushButton -->
    <object-type name="FluPushButton">
        <modify-function signature="FluPushButton(QWidget*)">
            <modify-argument index="1">
                <parent index="this" action="add"/>
            </modify-argument>
        </modify-function>
    </object-type>
    
    <!-- FluIconButton -->
    <object-type name="FluIconButton">
        <!-- 信号绑定 -->
    </object-type>
</typesystem>
```

### 阶段 4: Python 友好层 (2-3 周)

#### 4.1 创建 Python 包装类
在生成的绑定基础上，创建更易用的 Python API：

```python
# python/fluentui/controls/push_button.py
from FluentUI.Controls import FluPushButton as _FluPushButton

class PushButton(_FluPushButton):
    """Python 友好的 PushButton 封装"""
    
    def __init__(self, text="", icon=None, parent=None):
        super().__init__(parent)
        self.setText(text)
        if icon:
            self.setIcon(icon)
    
    # 添加 Python 特有的方法和属性
    @property
    def text(self):
        return self.text()
    
    @text.setter
    def text(self, value):
        self.setText(value)
```

#### 4.2 信号/槽 Python 化
提供装饰器简化信号连接：

```python
# python/fluentui/utils/signals.py
def connect_signal(signal, callback):
    """简化的信号连接"""
    signal.connect(callback)
    return callback
```

#### 4.3 上下文管理器
为需要清理的资源提供上下文管理器：

```python
class ThemeManager:
    def __init__(self, theme="light"):
        self.theme = theme
    
    def __enter__(self):
        FluThemeUtils.setTheme(self.theme)
        return self
    
    def __exit__(self, *args):
        pass  # 恢复默认主题
```

### 阶段 5: 示例和文档 (2 周)

#### 5.1 Python 示例
将 Gallery 和 Examples 移植到 Python：

```python
# python/fluentui/examples/push_button_example.py
import sys
from PySide6.QtWidgets import QApplication
from fluentui.controls import PushButton

app = QApplication(sys.argv)

button = PushButton("Click Me")
button.clicked.connect(lambda: print("Button clicked!"))
button.show()

sys.exit(app.exec())
```

#### 5.2 API 文档
使用 Sphinx 生成 Python API 文档：

```bash
cd python/docs
sphinx-apidoc -o source ../fluentui
make html
```

#### 5.3 快速入门指南
编写 `python/README.md`：
- 安装说明
- 快速开始
- 常见示例
- API 参考

### 阶段 6: 测试和打包 (1-2 周)

#### 6.1 测试框架
- 使用 pytest 编写单元测试
- 测试信号/槽连接
- 测试主题切换
- 测试资源加载

#### 6.2 打包分发
创建 `setup.py` 或 `pyproject.toml`：

```toml
[build-system]
requires = ["setuptools>=45", "wheel", "cmake>=3.20"]
build-backend = "setuptools.build_meta"

[project]
name = "fluentui-pyside6"
version = "1.0.0"
dependencies = ["PySide6>=6.5.0"]
```

#### 6.3 CI/CD 集成
- GitHub Actions 自动构建 wheels
- 支持 Windows/Linux/macOS
- 发布到 PyPI

## 技术挑战与解决方案

### 挑战 1: 第三方库绑定
**问题**: framelesshelper, qwindowkit 等库没有现成的 Python 绑定

**解决方案**:
1. 为这些库单独生成 Shiboken 绑定
2. 或寻找 Python 替代方案（如 qt-material, qdarkstyle）
3. 或暂时禁用相关功能，后续逐步添加

### 挑战 2: 资源系统
**问题**: Qt 的 `.qrc` 资源系统在 Python 中访问方式不同

**解决方案**:
```python
# 提供资源加载辅助函数
def load_resource(path):
    """从 Qt 资源系统加载文件"""
    from PySide6.QtCore import QFile
    file = QFile(f":/{path}")
    if file.open(QFile.ReadOnly):
        return file.readAll().data()
    return None
```

### 挑战 3: 信号/槽语法差异
**问题**: C++ 的信号/槽与 Python 的语法不完全兼容

**解决方案**:
- Shiboken 会自动处理大部分转换
- 提供 Python 装饰器简化常用模式
- 文档说明差异和最佳实践

### 挑战 4: 性能优化
**问题**: Python 调用 C++ 有开销

**解决方案**:
- 批量操作 API（减少调用次数）
- 缓存常用对象
- 文档标注性能敏感的操作

## 时间线估算

| 阶段 | 任务 | 预计时间 | 依赖 |
|------|------|----------|------|
| 1 | 基础设施搭建 | 2-3 周 | 无 |
| 2 | Utils 库绑定 | 1-2 周 | 阶段 1 |
| 3 | 基础控件绑定 | 3-4 周 | 阶段 2 |
| 4 | Python 友好层 | 2-3 周 | 阶段 3 |
| 5 | 示例和文档 | 2 周 | 阶段 4 |
| 6 | 测试和打包 | 1-2 周 | 阶段 5 |
| **总计** | | **11-16 周** | |

## 里程碑

### M1: 最小可行产品 (MVP) - 6 周
- [ ] 基础设施搭建完成
- [ ] Utils 库绑定完成
- [ ] 10 个基础控件可用
- [ ] 简单示例可运行

### M2: 核心功能完成 - 10 周
- [ ] 50+ 控件绑定完成
- [ ] Python 友好层完成
- [ ] 主题系统可用
- [ ] 完整示例

### M3: 发布版本 - 14 周
- [ ] 所有控件绑定完成
- [ ] 文档完善
- [ ] 测试覆盖 > 80%
- [ ] PyPI 发布

## 风险和缓解措施

| 风险 | 影响 | 概率 | 缓解措施 |
|------|------|------|----------|
| Shiboken 绑定生成失败 | 高 | 中 | 提前验证关键类的绑定可行性 |
| 第三方库不兼容 | 高 | 高 | 优先处理核心功能，第三方库延后 |
| 性能问题 | 中 | 中 | 早期性能测试，优化关键路径 |
| 维护成本高 | 中 | 高 | 自动化绑定生成，减少手动代码 |

## 下一步行动

1. **立即开始**: 安装 PySide6/Shiboken6，验证绑定生成可行性
2. **原型验证**: 选择 1-2 个简单控件（如 FluPushButton）生成绑定
3. **评审决策**: 基于原型结果调整方案
4. **详细规划**: 制定每个阶段的详细任务清单

## 参考资源

- [PySide6 官方文档](https://doc.qt.io/qtforpython/)
- [Shiboken 文档](https://doc.qt.io/qtforpython/shiboken/)
- [Qt Python 绑定示例](https://code.qt.io/cgit/pyside/pyside-setup.git/tree/)
- [PySide6 GitHub](https://github.com/qtproject/pyside)
