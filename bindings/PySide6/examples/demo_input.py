#!/usr/bin/env python
"""FluentUI Python Bindings - Input Controls Example

Demonstrates FluLineEdit, FluTextEdit, FluComboBoxEx, FluSpinBox,
FluSlider, FluRatingControl, FluAutoSuggestBox, FluPasswordBox.
"""

import os
import sys

if sys.platform == 'win32':
    os.add_dll_directory(r'E:\code\FluentUI-Master\build\bin')
    os.add_dll_directory(r'C:\Qt\6.8.1\msvc2022_64\bin')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\PySide6')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\shiboken6')

sys.path.insert(0, r'E:\code\FluentUI-Master\build\python\Release')

from PySide6.QtWidgets import (
    QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
    QWidget, QGroupBox, QGridLayout, QFormLayout
)
from PySide6.QtCore import Qt

from PySide6FluentUI import (
    FluLineEdit, FluTextEdit, FluSpinBox, FluDoubleSpinBox,
    FluPasswordBox, FluSearchLineEdit, FluComboBox, FluComboBoxEx,
    FluSlider, FluRatingControl, FluAutoSuggestBox,
    FluLabel, FluPushButton,
)


class InputWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("FluentUI - Input Controls")
        self.setGeometry(150, 150, 700, 600)

        central = QWidget()
        self.setCentralWidget(central)
        main_layout = QVBoxLayout(central)

        # Text inputs group
        text_group = QGroupBox("Text Input")
        text_layout = QFormLayout(text_group)

        self.line_edit = FluLineEdit()
        self.line_edit.setPlaceholderText("Enter text...")
        text_layout.addRow("LineEdit:", self.line_edit)

        self.password = FluPasswordBox()
        text_layout.addRow("Password:", self.password)

        self.search = FluSearchLineEdit()
        text_layout.addRow("Search:", self.search)

        self.text_edit = FluTextEdit()
        self.text_edit.setFixedHeight(80)
        self.text_edit.setPlaceholderText("Multi-line text...")
        text_layout.addRow("TextEdit:", self.text_edit)

        main_layout.addWidget(text_group)

        # Selection inputs group
        select_group = QGroupBox("Selection")
        select_layout = QFormLayout(select_group)

        self.combo = FluComboBoxEx()
        self.combo.addTextItem("Python")
        self.combo.addTextItem("C++")
        self.combo.addTextItem("Rust")
        self.combo.addTextItem("Go")
        select_layout.addRow("ComboBox:", self.combo)

        self.spinbox = FluSpinBox()
        self.spinbox.setRange(0, 999)
        self.spinbox.setValue(100)
        select_layout.addRow("SpinBox:", self.spinbox)

        self.double_spin = FluDoubleSpinBox()
        self.double_spin.setRange(0.0, 1.0)
        self.double_spin.setSingleStep(0.1)
        self.double_spin.setValue(0.5)
        select_layout.addRow("DoubleSpinBox:", self.double_spin)

        main_layout.addWidget(select_group)

        # Range inputs group
        range_group = QGroupBox("Range & Rating")
        range_layout = QVBoxLayout(range_group)

        self.slider = FluSlider(Qt.Orientation.Horizontal)
        self.slider.setRange(0, 100)
        self.slider.setValue(50)
        range_layout.addWidget(self.slider)

        self.rating = FluRatingControl()
        range_layout.addWidget(self.rating)

        main_layout.addWidget(range_group)

        # AutoSuggest
        suggest_group = QGroupBox("AutoSuggest")
        suggest_layout = QVBoxLayout(suggest_group)

        self.suggest = FluAutoSuggestBox()
        self.suggest.setPlaceholderText("Search frameworks...")
        suggest_layout.addWidget(self.suggest)

        main_layout.addWidget(suggest_group)

        # Submit button
        self.submit_btn = FluPushButton()
        self.submit_btn.setText("Print All Values")
        self.submit_btn.clicked.connect(self.print_values)
        main_layout.addWidget(self.submit_btn)

        main_layout.addStretch()

    def print_values(self):
        print("=" * 40)
        print("Current Input Values:")
        print(f"  LineEdit: {self.line_edit.text()}")
        print(f"  Search: {self.search.getText()}")
        print(f"  SpinBox: {self.spinbox.value()}")
        print(f"  DoubleSpinBox: {self.double_spin.value()}")
        print(f"  Slider: {self.slider.value()}")
        print("=" * 40)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = InputWindow()
    window.show()
    print("FluentUI Input Controls Example")
    print("Interact with the controls and click 'Print All Values'.")
    sys.exit(app.exec())
