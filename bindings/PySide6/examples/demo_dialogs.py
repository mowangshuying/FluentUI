#!/usr/bin/env python
"""FluentUI Python Bindings - Dialog and Popup Example

Demonstrates FluDialog, FluMessageBox, FluRoundMenu, FluTeachingTip.
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

from FluentUI import (
    FluPushButton, FluLabel, FluDialog, FluMessageBox,
    FluRoundMenu, FluAction, FluMenu,
)


class DialogWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("FluentUI - Dialog & Popup Example")
        self.setGeometry(200, 200, 500, 400)

        central = QWidget()
        self.setCentralWidget(central)
        layout = QVBoxLayout(central)

        # Dialog button
        self.dialog_btn = FluPushButton()
        self.dialog_btn.setText("Show Dialog")
        self.dialog_btn.clicked.connect(self.show_dialog)
        layout.addWidget(self.dialog_btn)

        # MessageBox button
        self.msgbox_btn = FluPushButton()
        self.msgbox_btn.setText("Show MessageBox")
        self.msgbox_btn.clicked.connect(self.show_messagebox)
        layout.addWidget(self.msgbox_btn)

        # RoundMenu button
        self.menu_btn = FluPushButton()
        self.menu_btn.setText("Show RoundMenu")
        self.menu_btn.clicked.connect(self.show_round_menu)
        layout.addWidget(self.menu_btn)

        # Standard Menu button
        self.std_menu_btn = FluPushButton()
        self.std_menu_btn.setText("Show Standard Menu")
        self.std_menu_btn.clicked.connect(self.show_standard_menu)
        layout.addWidget(self.std_menu_btn)

        layout.addStretch()

    def show_dialog(self):
        dlg = FluDialog(self)
        dlg.show()
        print("Dialog shown")

    def show_messagebox(self):
        msgbox = FluMessageBox("Title", "This is a message box content.", self)
        msgbox.show()
        print("MessageBox shown")

    def show_round_menu(self):
        menu = FluRoundMenu()
        menu.setTitle("Options")

        action1 = FluAction("Copy")
        action2 = FluAction("Paste")
        action3 = FluAction("Delete")

        menu.addAction(action1)
        menu.addAction(action2)
        menu.addAction(action3)

        # Show at button position
        pos = self.menu_btn.mapToGlobal(self.menu_btn.rect().bottomLeft())
        menu.exec(pos)
        print("RoundMenu shown")

    def show_standard_menu(self):
        menu = FluMenu()
        action1 = FluAction("File")
        action2 = FluAction("Edit")
        action3 = FluAction("View")
        menu.addAction(action1)
        menu.addAction(action2)
        menu.addAction(action3)

        pos = self.std_menu_btn.mapToGlobal(self.std_menu_btn.rect().bottomLeft())
        menu.exec(pos)
        print("Standard Menu shown")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DialogWindow()
    window.show()
    print("FluentUI Dialog & Popup Example")
    print("Click buttons to show different popup types.")
    sys.exit(app.exec())
