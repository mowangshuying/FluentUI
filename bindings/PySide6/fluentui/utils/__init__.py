"""
FluentUI Utils Module
Python bindings for FluentUI C++ utilities
"""

# Import generated bindings
try:
    from FluentUI import (
        FluThemeUtils,
        FluIconUtils,
        FluStyleSheetUtils,
        FluConfigUtils,
    )
except ImportError as e:
    print(f"Warning: Could not import generated bindings: {e}")
    print("Make sure the C++ bindings are built and installed.")
    
    # Provide fallback stubs for development
    class FluThemeUtils:
        """Stub for FluThemeUtils - requires C++ bindings"""
        @staticmethod
        def setTheme(theme: str):
            print(f"Stub: setTheme({theme})")
        
        @staticmethod
        def getTheme() -> str:
            return "light"
    
    class FluIconUtils:
        """Stub for FluIconUtils - requires C++ bindings"""
        pass
    
    class FluStyleSheetUtils:
        """Stub for FluStyleSheetUtils - requires C++ bindings"""
        pass
    
    class FluConfigUtils:
        """Stub for FluConfigUtils - requires C++ bindings"""
        pass

__all__ = [
    'FluThemeUtils',
    'FluIconUtils',
    'FluStyleSheetUtils',
    'FluConfigUtils',
]
