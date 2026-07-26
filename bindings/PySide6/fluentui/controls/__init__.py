"""
FluentUI Controls Module
Python bindings for FluentUI C++ controls
"""

# Import generated bindings
try:
    from FluentUI import (
        FluWidget,
        FluPushButton,
        FluIconButton,
    )
except ImportError as e:
    print(f"Warning: Could not import generated bindings: {e}")
    print("Make sure the C++ bindings are built and installed.")
    
    # Provide fallback stubs for development
    class FluWidget:
        """Stub for FluWidget - requires C++ bindings"""
        pass
    
    class FluPushButton:
        """Stub for FluPushButton - requires C++ bindings"""
        pass
    
    class FluIconButton:
        """Stub for FluIconButton - requires C++ bindings"""
        pass

__all__ = [
    'FluWidget',
    'FluPushButton',
    'FluIconButton',
]
