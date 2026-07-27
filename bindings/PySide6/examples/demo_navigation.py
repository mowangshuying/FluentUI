#!/usr/bin/env python
"""FluentUI Python Bindings - Navigation View Example

Demonstrates FluVNavigationView with navigation items.
"""

import os
import sys

if sys.platform == 'win32':
    os.add_dll_directory(r'E:\code\FluentUI-Master\build\bin')
    os.add_dll_directory(r'C:\Qt\6.8.1\msvc2022_64\bin')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\PySide6')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\shiboken6')

sys.path.insert(0, r'E:\code\FluentUI-Master\build\python\Release')

from PySide6.QtWidgets import QApplication, QMainWindow, QHBoxLayout, QWidget, QLabel
from PySide6.QtCore import Qt

from PySide6FluentUI import (
    FluVNavigationView, FluVNavigationIconTextItem,
    FluVNavigationMenuItem, FluVNavigationSettingsItem,
    FluLabel, FluThemeUtils,
)


class NavigationWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("FluentUI - Navigation View Example")
        self.setGeometry(100, 100, 1000, 600)

        central = QWidget()
        self.setCentralWidget(central)
        layout = QHBoxLayout(central)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)

        # Create vertical navigation view
        self.nav_view = FluVNavigationView()
        self.nav_view.setFixedWidth(200)
        layout.addWidget(self.nav_view)

        # Content area
        self.content = QLabel("Select a navigation item")
        self.content.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.content.setStyleSheet("font-size: 18px;")
        layout.addWidget(self.content, 1)

        # Add navigation items
        self._setup_nav_items()

    def _setup_nav_items(self):
        # Add menu items to the navigation view
        items_data = [
            ("Home", "Home"),
            ("Settings", "Settings"),
            ("Profile", "Profile"),
            ("About", "About"),
        ]

        for text, key in items_data:
            item = FluVNavigationIconTextItem()
            self.nav_view.addItemToMidLayout(item)

        # Connect signal
        self.nav_view.keyChanged.connect(self._on_nav_changed)

    def _on_nav_changed(self, key):
        self.content.setText(f"Current page: {key}")
        print(f"Navigation changed to: {key}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = NavigationWindow()
    window.show()
    print("FluentUI Navigation View Example")
    print("Close the window to exit.")
    sys.exit(app.exec())
