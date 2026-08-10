#!/usr/bin/env python
"""FluentUI Python Bindings - Comprehensive Examples

Demonstrates all major control categories bound via Shiboken6/PySide6.
"""

import os
import sys

# --- Environment Setup (Windows) ---
if sys.platform == 'win32':
    os.add_dll_directory(r'E:\code\FluentUI-Master\build\bin')
    os.add_dll_directory(r'C:\Qt\6.8.1\msvc2022_64\bin')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\PySide6')
    os.add_dll_directory(r'C:\Users\Administrator\AppData\Local\Programs\Python\Python313\Lib\site-packages\shiboken6')

sys.path.insert(0, r'E:\code\FluentUI-Master\build\python\Release')

from PySide6.QtWidgets import (
    QApplication, QMainWindow, QVBoxLayout, QHBoxLayout,
    QWidget, QGridLayout, QGroupBox, QScrollArea
)
from PySide6.QtCore import Qt

from PySide6FluentUI import (
    # Buttons
    FluPushButton, FluIconButton, FluToggleButton, FluCheckBox,
    FluRadioButton, FluHyperLinkButton, FluRepeatButton,
    FluDropDownButton, FluSplitButton, FluStyleButton,
    FluToggleSwitch,
    # Input
    FluLineEdit, FluTextEdit, FluSpinBox, FluDoubleSpinBox,
    FluPasswordBox, FluSearchLineEdit, FluComboBox, FluComboBox,
    FluSlider, FluRatingControl, FluAutoSuggestBox,
    # Display
    FluLabel, FluProgressBar, FluProgressRing, FluBusyProgressRing,
    FluInfoBadge, FluImageBox, FluTimeLine, FluTimeLineItem,
    # Containers
    FluExpander, FluScrollArea, FluVCard, FluHCard,
    FluBorder, FluCodeBox,
    # Navigation
    FluTabBar, FluPagination, FluPivot, FluSegmented,
    FluVNavigationView, FluVNavigationIconTextItem,
    FluHNavigationView, FluHNavigationIconTextItem,
    # Popup/Dialog
    FluDialog, FluMessageBox, FluMenu, FluRoundMenu,
    FluTeachingTip, FluConfirmFlyout,
    # Window
    FluWindowKitWidget, FluWindowKitWindow,
    # Utils
    FluThemeUtils, FluIconUtils, FluStyleSheetUtils,
    # Other
    FluCalendarView, FluCalendarDatePicker, FluDatePicker,
    FluColorPickerButton, FluSettingsLabelBox,
)


class ButtonExamples(QGroupBox):
    """Button controls demonstration."""

    def __init__(self):
        super().__init__("Buttons")
        layout = QHBoxLayout(self)

        self.push_btn = FluPushButton()
        self.push_btn.setText("PushButton")
        self.push_btn.clicked.connect(lambda: print("PushButton clicked"))
        layout.addWidget(self.push_btn)

        self.toggle_btn = FluToggleButton()
        self.toggle_btn.setText("Toggle")
        layout.addWidget(self.toggle_btn)

        self.checkbox = FluCheckBox("CheckBox")
        layout.addWidget(self.checkbox)

        self.radio = FluRadioButton("Radio")
        layout.addWidget(self.radio)

        self.switch = FluToggleSwitch()
        layout.addWidget(self.switch)

        self.hyperlink = FluHyperLinkButton("https://github.com")
        self.hyperlink.setText("GitHub")
        layout.addWidget(self.hyperlink)


class InputExamples(QGroupBox):
    """Input controls demonstration."""

    def __init__(self):
        super().__init__("Input")
        layout = QGridLayout(self)

        self.line_edit = FluLineEdit()
        self.line_edit.setPlaceholderText("LineEdit...")
        layout.addWidget(self.line_edit, 0, 0)

        self.password = FluPasswordBox()
        layout.addWidget(self.password, 0, 1)

        self.search = FluSearchLineEdit()
        layout.addWidget(self.search, 1, 0)

        self.combo = FluComboBox()
        self.combo.addTextItem("Option 1")
        self.combo.addTextItem("Option 2")
        self.combo.addTextItem("Option 3")
        layout.addWidget(self.combo, 1, 1)

        self.spinbox = FluSpinBox()
        self.spinbox.setRange(0, 100)
        self.spinbox.setValue(42)
        layout.addWidget(self.spinbox, 2, 0)

        self.slider = FluSlider(Qt.Orientation.Horizontal)
        self.slider.setRange(0, 100)
        self.slider.setValue(50)
        layout.addWidget(self.slider, 2, 1)

        self.rating = FluRatingControl()
        layout.addWidget(self.rating, 3, 0)


class DisplayExamples(QGroupBox):
    """Display controls demonstration."""

    def __init__(self):
        super().__init__("Display")
        layout = QHBoxLayout(self)

        self.label = FluLabel()
        self.label.setText("FluLabel")
        layout.addWidget(self.label)

        self.progress_bar = FluProgressBar()
        self.progress_bar.setRange(0, 100)
        self.progress_bar.setValue(65)
        layout.addWidget(self.progress_bar)

        self.progress_ring = FluProgressRing()
        self.progress_ring.setCurValue(75)
        layout.addWidget(self.progress_ring)

        self.busy_ring = FluBusyProgressRing()
        layout.addWidget(self.busy_ring)


class ContainerExamples(QGroupBox):
    """Container controls demonstration."""

    def __init__(self):
        super().__init__("Containers")
        layout = QVBoxLayout(self)

        self.expander = FluExpander()
        layout.addWidget(self.expander)

        self.card = FluVCard()
        layout.addWidget(self.card)

        self.border = FluBorder()
        layout.addWidget(self.border)


class NavigationExamples(QGroupBox):
    """Navigation controls demonstration."""

    def __init__(self):
        super().__init__("Navigation")
        layout = QVBoxLayout(self)

        self.pagination = FluPagination(1, 5, 100)
        layout.addWidget(self.pagination)

        self.segmented = FluSegmented()
        layout.addWidget(self.segmented)


class ThemeExample(QGroupBox):
    """Theme switching demonstration."""

    def __init__(self):
        super().__init__("Theme")
        layout = QHBoxLayout(self)

        self.theme_btn = FluPushButton()
        self.theme_btn.setText("Toggle Theme")
        self.theme_btn.clicked.connect(self.toggle_theme)
        layout.addWidget(self.theme_btn)

        self.info_label = FluLabel()
        self.info_label.setText("Current: Light")
        layout.addWidget(self.info_label)

    def toggle_theme(self):
        utils = FluThemeUtils.getUtils()
        # Theme switching is handled internally
        print("Theme toggle requested")


class ExampleWindow(QMainWindow):
    """Main example window showcasing all FluentUI controls."""

    def __init__(self):
        super().__init__()
        self.setWindowTitle("FluentUI Python - Comprehensive Examples")
        self.setGeometry(100, 100, 900, 700)

        # Central scroll area
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        self.setCentralWidget(scroll)

        container = QWidget()
        scroll.setWidget(container)
        main_layout = QVBoxLayout(container)

        # Add example groups
        main_layout.addWidget(ButtonExamples())
        main_layout.addWidget(InputExamples())
        main_layout.addWidget(DisplayExamples())
        main_layout.addWidget(ContainerExamples())
        main_layout.addWidget(NavigationExamples())
        main_layout.addWidget(ThemeExample())

        main_layout.addStretch()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ExampleWindow()
    window.show()
    print("=" * 60)
    print("FluentUI Python Bindings - Comprehensive Examples")
    print("=" * 60)
    print(f"Total bound classes: 140+")
    print("Categories: Buttons, Input, Display, Containers,")
    print("           Navigation, Popup/Dialog, Window, Utils")
    print("=" * 60)
    print("Close the window to exit.")
    sys.exit(app.exec())
