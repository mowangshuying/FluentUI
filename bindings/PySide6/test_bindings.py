#!/usr/bin/env python
"""FluentUI Python Bindings Test"""

import os
import sys

# Add DLL directories (Windows only)
if sys.platform == 'win32':
    os.add_dll_directory(r'E:\code\FluentUI-Master\build\bin')
    os.add_dll_directory(r'C:\Qt\6.8.1\msvc2022_64\bin')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\PySide6')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\shiboken6')

# Add FluentUI module to path
sys.path.insert(0, r'E:\code\FluentUI-Master\build\python\Release')

from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from FluentUI import FluPushButton, FluIconButton, FluWidget

class TestWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("FluentUI Python Test")
        self.setGeometry(100, 100, 400, 300)
        
        # Create central widget
        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)
        
        # Create FluPushButton
        self.btn1 = FluPushButton()
        self.btn1.setText("FluPushButton")
        self.btn1.clicked.connect(self.on_btn1_clicked)
        layout.addWidget(self.btn1)
        
        # Create FluIconButton
        self.btn2 = FluIconButton()
        self.btn2.setText("FluIconButton")
        layout.addWidget(self.btn2)
        
        # Create FluWidget
        self.widget = FluWidget()
        layout.addWidget(self.widget)
        
        self.click_count = 0
        
    def on_btn1_clicked(self):
        self.click_count += 1
        self.btn1.setText(f"Clicked {self.click_count} times")
        print(f"Button clicked! Count: {self.click_count}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = TestWindow()
    window.show()
    print("FluentUI Python bindings test started!")
    print("Close the window to exit.")
    sys.exit(app.exec())
