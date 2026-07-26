cmake_minimum_required(VERSION 3.20)
project(FluentUI_Python VERSION 1.0.0 LANGUAGES CXX)

# Find Python
find_package(Python REQUIRED COMPONENTS Interpreter Development)

# Get PySide6 paths using Python
execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import PySide6; print(PySide6.__path__[0])"
    OUTPUT_VARIABLE PYSIDE6_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE PYSIDE6_RESULT
)

if(NOT PYSIDE6_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to find PySide6. Please install it with: pip install PySide6")
endif()

execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import shiboken6; print(shiboken6.__path__[0])"
    OUTPUT_VARIABLE SHIBOKEN6_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE SHIBOKEN6_RESULT
)

if(NOT SHIBOKEN6_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to find Shiboken6. Please install it with: pip install shiboken6")
endif()

# Find shiboken6-generator executable
execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import shiboken6_generator; import os; print(os.path.dirname(shiboken6_generator.__file__))"
    OUTPUT_VARIABLE SHIBOKEN6_GENERATOR_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_program(SHIBOKEN6_EXECUTABLE
    NAMES shiboken6 shiboken6-generator
    PATHS ${SHIBOKEN6_GENERATOR_DIR} ${SHIBOKEN6_PREFIX}
    NO_DEFAULT_PATH
)

if(NOT SHIBOKEN6_EXECUTABLE)
    find_program(SHIBOKEN6_EXECUTABLE
        NAMES shiboken6 shiboken6-generator
    )
endif()

if(NOT SHIBOKEN6_EXECUTABLE)
    message(FATAL_ERROR "Failed to find shiboken6 executable. Please install it with: pip install shiboken6-generator")
endif()

message(STATUS "Found PySide6: ${PYSIDE6_PREFIX}")
message(STATUS "Found Shiboken6: ${SHIBOKEN6_PREFIX}")
message(STATUS "Found shiboken6 executable: ${SHIBOKEN6_EXECUTABLE}")

# Get PySide6 and Shiboken6 include directories and libraries
execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import PySide6; import os; print(os.path.join(PySide6.__path__[0], 'include'))"
    OUTPUT_VARIABLE PYSIDE6_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import shiboken6_generator; import os; print(os.path.join(shiboken6_generator.__path__[0], 'include'))"
    OUTPUT_VARIABLE SHIBOKEN6_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import PySide6; import os; print(os.path.join(PySide6.__path__[0], 'pyside6.abi3.lib'))"
    OUTPUT_VARIABLE PYSIDE6_LIBRARY
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import shiboken6; import os; print(os.path.join(shiboken6.__path__[0], 'shiboken6.abi3.lib'))"
    OUTPUT_VARIABLE SHIBOKEN6_LIBRARY
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get PySide6 typesystems path
execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import PySide6; import os; print(os.path.join(PySide6.__path__[0], 'typesystems'))"
    OUTPUT_VARIABLE PYSIDE6_TYPESYSTEMS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get Qt6 include directory
get_target_property(QT6_INCLUDE_DIRS Qt6::Core INTERFACE_INCLUDE_DIRECTORIES)
# Use the parent directory (e.g., C:/Qt/6.5.1/msvc2019_64/include)
list(GET QT6_INCLUDE_DIRS 0 QT6_CORE_INCLUDE_DIR)
cmake_path(GET QT6_CORE_INCLUDE_DIR PARENT_PATH QT6_INCLUDE_DIR)
# Shiboken's Clang parser needs module subdirectories for forwarding headers
set(QT6_INCLUDE_PATHS "${QT6_INCLUDE_DIR};${QT6_INCLUDE_DIR}/QtCore;${QT6_INCLUDE_DIR}/QtGui;${QT6_INCLUDE_DIR}/QtWidgets")

message(STATUS "PySide6 include: ${PYSIDE6_INCLUDE_DIR}")
message(STATUS "PySide6 library: ${PYSIDE6_LIBRARY}")
message(STATUS "Shiboken6 include: ${SHIBOKEN6_INCLUDE_DIR}")
message(STATUS "Shiboken6 library: ${SHIBOKEN6_LIBRARY}")

# Set output directory for generated bindings
set(BINDINGS_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/bindings")
file(MAKE_DIRECTORY ${BINDINGS_OUTPUT_DIR})

# Header files to process
set(FLUENTUI_HEADERS
    # Utils
    "${CMAKE_SOURCE_DIR}/Utils/FluThemeUtils.h"
    "${CMAKE_SOURCE_DIR}/Utils/FluConfigUtils.h"
    "${CMAKE_SOURCE_DIR}/Utils/FluStyleSheetUtils.h"
    "${CMAKE_SOURCE_DIR}/Utils/FluIconUtils.h"
    "${CMAKE_SOURCE_DIR}/Utils/FluLogUtils.h"
    "${CMAKE_SOURCE_DIR}/Utils/FluTranslatorUtils.h"
    "${CMAKE_SOURCE_DIR}/Utils/FluEmoijUtils.h"
    "${CMAKE_SOURCE_DIR}/Utils/FluObjectPtrUtils.h"
    # Controls - Base
    "${CMAKE_SOURCE_DIR}/Controls/FluWidget.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluPushButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluIconButton.h"
    # Controls - Buttons
    "${CMAKE_SOURCE_DIR}/Controls/FluCheckBox.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluRadioButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluToggleButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluDropDownButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluSplitButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluRepeatButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluHyperLinkButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluAppBarButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluAppBarToggleButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluStyleButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluScaleButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluRotationButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluGraphicalButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluThemeButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluPPushButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluWindowkitButton.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluCommandBarItem.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluCommandBarIconItem.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluCommandBarIconTextItem.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluCommandBarSplitItem.h"
    # Controls - Input
    "${CMAKE_SOURCE_DIR}/Controls/FluLineEdit.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluTextEdit.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluTextEditWrap.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluSpinBox.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluDoubleSpinBox.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluPasswordBox.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluSearchLineEdit.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluAutoSuggestBox.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluComboBox.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluComboBoxEx.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluComboBoxTextItem.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluIntValidator.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluSlider.h"
    "${CMAKE_SOURCE_DIR}/Controls/FluRatingControl.h"
)

# Expected generated wrapper files (Shiboken6 generates lowercase names)
set(GENERATED_WRAPPER_FILES
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluentui_module_wrapper.cpp
    # Utils wrappers
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluthemeutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluconfigutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flustylesheetutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluiconutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flulogutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flutranslatorutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluemoijutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluobjectptrutils_wrapper.cpp
    # Controls wrappers - Base
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluwidget_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flupushbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluiconbutton_wrapper.cpp
    # Controls wrappers - Buttons
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucheckbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluradiobutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flutogglebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fludropdownbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flusplitbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flurepeatbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluhyperlinkbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluappbarbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluappbartogglebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flustylebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluscalebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flurotationbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flugraphicalbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluthemebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluppushbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluwindowkitbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucommandbaritem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucommandbariconitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucommandbaricontextitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucommandbarsplititem_wrapper.cpp
    # Controls wrappers - Input
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flulineedit_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flutextedit_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluspinbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fludoublespinbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flupasswordbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flusearchlineedit_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluautosuggestbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucombobox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucomboboxex_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/flucomboboxtextitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluintvalidator_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluslider_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/FluentUI/fluratingcontrol_wrapper.cpp
)

# Generate bindings using Shiboken6
add_custom_command(
    OUTPUT ${GENERATED_WRAPPER_FILES}
    COMMAND ${SHIBOKEN6_EXECUTABLE}
        --no-suppress-warnings
        --avoid-protected-hack
        --enable-pyside-extensions
        "--include-paths=${CMAKE_SOURCE_DIR}/Utils;${CMAKE_SOURCE_DIR}/Controls;${PYSIDE6_INCLUDE_DIR};${SHIBOKEN6_INCLUDE_DIR};${QT6_INCLUDE_PATHS}"
        "--typesystem-paths=${CMAKE_CURRENT_SOURCE_DIR}/typesystems;${PYSIDE6_TYPESYSTEMS_DIR}"
        "--output-directory=${BINDINGS_OUTPUT_DIR}"
        ${FLUENTUI_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/typesystems/fluentui_typesystem.xml
    DEPENDS
        ${FLUENTUI_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/typesystems/fluentui_typesystem.xml
    COMMENT "Generating Python bindings with Shiboken6"
)

# Create Python module
add_library(FluentUI_Python MODULE
    ${GENERATED_WRAPPER_FILES}
)

target_include_directories(FluentUI_Python PRIVATE
    ${CMAKE_SOURCE_DIR}/Utils
    ${CMAKE_SOURCE_DIR}/Controls
    ${Python_INCLUDE_DIRS}
    ${PYSIDE6_INCLUDE_DIR}
    ${PYSIDE6_INCLUDE_DIR}/QtCore
    ${PYSIDE6_INCLUDE_DIR}/QtGui
    ${PYSIDE6_INCLUDE_DIR}/QtWidgets
    ${SHIBOKEN6_INCLUDE_DIR}
    ${QT6_INCLUDE_DIR}
    ${QT6_INCLUDE_DIR}/QtCore
    ${QT6_INCLUDE_DIR}/QtGui
    ${QT6_INCLUDE_DIR}/QtWidgets
)

# Get Python library directory
execute_process(
    COMMAND ${Python_EXECUTABLE} -c "import sysconfig; print(sysconfig.get_config_var('LIBDIR'))"
    OUTPUT_VARIABLE PYTHON_LIBDIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_link_directories(FluentUI_Python PRIVATE
    ${PYTHON_LIBDIR}
)

target_link_libraries(FluentUI_Python PRIVATE
    FluentUI::Utils
    FluentUI::Controls
    ${PYSIDE6_LIBRARY}
    ${SHIBOKEN6_LIBRARY}
    Qt6::Core
    Qt6::Widgets
)

set_target_properties(FluentUI_Python PROPERTIES
    PREFIX ""
    OUTPUT_NAME "FluentUI"
    SUFFIX ".pyd"
)

# Install Python module
install(TARGETS FluentUI_Python
    LIBRARY DESTINATION ${Python_SITEARCH}
    RUNTIME DESTINATION ${Python_SITEARCH}
)
