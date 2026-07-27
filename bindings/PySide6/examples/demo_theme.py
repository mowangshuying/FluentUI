#!/usr/bin/env python
"""FluentUI Python Bindings - Theme Switching Example

Demonstrates theme management with FluThemeUtils.
"""

import os
import sys

if sys.platform == 'win32':
    os.add_dll_directory(r'E:\code\FluentUI-Master\build\bin')
    os.add_dll_directory(r'C:\Qt\6.8.1\msvc2022_64\bin')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\PySide6')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\shiboken6')

sys.path.insert(0, r'E:\code\FluentUI-Master\build\python\Release')

from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PySide6.QtCore import Qt

from PySide6FluentUI import (
    FluPushButton, FluLabel, FluToggleSwitch,
    FluProgressBar, FluCheckBox, FluLineEdit,
    FluThemeUtils, FluTheme,
)


class ThemeWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("FluentUI - Theme Switching")
        self.setGeometry(200, 200, 500, 400)

        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)

        # Title
        title = FluLabel()
        title.setText("Theme Switching Demo")
        layout.addWidget(title)

        # Theme toggle button
        self.theme_btn = FluPushButton()
        self.theme_btn.setText("Switch to Dark Theme")
        self.theme_btn.clicked.connect(self.toggle_theme)
        layout.addWidget(self.theme_btn)

        # Sample controls to show theme effect
        self.checkbox = FluCheckBox("Sample CheckBox")
        layout.addWidget(self.checkbox)

        self.line_edit = FluLineEdit()
        self.line_edit.setPlaceholderText("Type something...")
        layout.addWidget(self.line_edit)

        self.progress = FluProgressBar()
        self.progress.setRange(0, 100)
        self.progress.setValue(60)
        layout.addWidget(self.progress)

        self.switch = FluToggleSwitch()
        layout.addWidget(self.switch)

        layout.addStretch()

        self.is_dark = False

    def toggle_theme(self):
        self.is_dark = not self.is_dark
        theme_utils = FluThemeUtils.getUtils()
        if self.is_dark:
            theme_utils.setTheme(FluTheme.Dark)
            self.theme_btn.setText("Switch to Light Theme")
        else:
            theme_utils.setTheme(FluTheme.Light)
            self.theme_btn.setText("Switch to Dark Theme")
        print(f"Theme switched to: {'Dark' if self.is_dark else 'Light'}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ThemeWindow()
    window.show()
    print("FluentUI Theme Switching Example")
    print("Click the button to toggle between Light/Dark themes.")
    sys.exit(app.exec())
