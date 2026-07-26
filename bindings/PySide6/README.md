# FluentUI Python Bindings

Python bindings for the FluentUI C++ library, built with PySide6 and Shiboken6.

## Installation

### Prerequisites

- Python 3.8 or higher
- PySide6 >= 6.5.0
- CMake >= 3.20
- Qt 6.5.1 or compatible version
- C++17 compatible compiler

### Build from Source

1. **Install dependencies:**

```bash
pip install PySide6
```

2. **Configure CMake with Python bindings enabled:**

```bash
mkdir build && cd build
cmake -DBUILD_PYTHON_BINDINGS=ON -DCMAKE_PREFIX_PATH=/path/to/qt ..
```

3. **Build the project:**

```bash
cmake --build . --config Release
```

4. **Install Python package:**

```bash
cd python
pip install -e .
```

## Quick Start

```python
import sys
from PySide6.QtWidgets import QApplication
from fluentui.controls import FluPushButton
from fluentui.utils import FluThemeUtils

app = QApplication(sys.argv)

# Set theme
FluThemeUtils.setTheme("light")

# Create a FluentUI button
button = FluPushButton()
button.setText("Hello FluentUI!")
button.clicked.connect(lambda: print("Clicked!"))
button.show()

sys.exit(app.exec())
```

## Examples

See the `fluentui/examples/` directory for more examples:

- `push_button_example.py` - Basic button usage
- More examples coming soon...

Run an example:

```bash
python -m fluentui.examples.push_button_example
```

## API Reference

### Controls

- `FluWidget` - Base widget class
- `FluPushButton` - Push button with Fluent Design
- `FluIconButton` - Button with icon support

### Utils

- `FluThemeUtils` - Theme management (light/dark)
- `FluIconUtils` - Icon utilities
- `FluStyleSheetUtils` - Style sheet management
- `FluConfigUtils` - Configuration utilities

## Development

### Building Bindings

The Python bindings are generated using Shiboken6 from the C++ headers.

```bash
cd build
cmake --build . --target FluentUI_Python
```

### Running Tests

```bash
cd python
pytest tests/
```

## Troubleshooting

### Import Error: "No module named 'FluentUI'"

Make sure the C++ bindings are built and installed:

```bash
cd build
cmake --build . --target install
```

### Binding Generation Fails

Ensure Shiboken6 is installed and CMake can find it:

```bash
pip install shiboken6-generator
```

## License

This project is licensed under the LGPL-2.1 License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please read the contributing guidelines before submitting PRs.

## Links

- [FluentUI C++ Repository](https://github.com/mowangshuying/FluentUI)
- [PySide6 Documentation](https://doc.qt.io/qtforpython/)
- [Shiboken Documentation](https://doc.qt.io/qtforpython/shiboken/)
