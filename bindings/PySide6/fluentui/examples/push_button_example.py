"""
FluentUI PushButton Example
Demonstrates basic usage of FluentUI controls in Python
"""

import sys
from PySide6.QtWidgets import QApplication, QVBoxLayout, QWidget
from fluentui.controls import FluPushButton
from fluentui.utils import FluThemeUtils


class ExampleWindow(QWidget):
    def __init__(self):
        super().__init__()
        
        self.setWindowTitle("FluentUI PySide6 Example")
        self.setMinimumSize(400, 300)
        
        # Create layout
        layout = QVBoxLayout(self)
        
        # Create a FluentUI push button
        self.button = FluPushButton(self)
        self.button.setText("Click Me!")
        self.button.setFixedSize(200, 40)
        
        # Connect signal
        self.button.clicked.connect(self.on_button_clicked)
        
        # Add to layout
        layout.addWidget(self.button)
        layout.addStretch()
        
        # Set theme
        FluThemeUtils.setTheme("light")
        
    def on_button_clicked(self):
        print("Button clicked!")
        self.button.setText("Clicked!")


def main():
    app = QApplication(sys.argv)
    
    window = ExampleWindow()
    window.show()
    
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
