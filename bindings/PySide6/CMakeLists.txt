cmake_minimum_required(VERSION 3.20)
project(PySide6FluentUI VERSION 1.0.0 LANGUAGES CXX)

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
    "${CMAKE_SOURCE_DIR}/utils/FluThemeUtils.h"
    "${CMAKE_SOURCE_DIR}/utils/FluConfigUtils.h"
    "${CMAKE_SOURCE_DIR}/utils/FluStyleSheetUtils.h"
    "${CMAKE_SOURCE_DIR}/utils/FluIconUtils.h"
    "${CMAKE_SOURCE_DIR}/utils/FluLogUtils.h"
    "${CMAKE_SOURCE_DIR}/utils/FluTranslatorUtils.h"
    "${CMAKE_SOURCE_DIR}/utils/FluEmoijUtils.h"
    "${CMAKE_SOURCE_DIR}/utils/FluObjectPtrUtils.h"
    # Controls - Base
    "${CMAKE_SOURCE_DIR}/controls/FluWidget.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPushButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluIconButton.h"
    # Controls - Buttons
    "${CMAKE_SOURCE_DIR}/controls/FluCheckBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluRadioButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluToggleButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDropDownButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSplitButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluRepeatButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHyperLinkButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluAppBarButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluAppBarToggleButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluStyleButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluScaleButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluRotationButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluGraphicalButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluThemeButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPPushButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluWindowkitButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCommandBarItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCommandBarIconItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCommandBarIconTextItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCommandBarSplitItem.h"
    # Controls - Input
    "${CMAKE_SOURCE_DIR}/controls/FluLineEdit.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTextEdit.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTextEditWrap.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSpinBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDoubleSpinBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPasswordBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSearchLineEdit.h"
    "${CMAKE_SOURCE_DIR}/controls/FluComboBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluIntValidator.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSlider.h"
    "${CMAKE_SOURCE_DIR}/controls/FluRatingControl.h"
    # Controls - Navigation (simplified)
    "${CMAKE_SOURCE_DIR}/controls/FluTabBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTabBarContent.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTabBarItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTabView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTabWidget.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPagination.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPaginationItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPivot.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPivotTitleBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPivotTitleBarItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSegmented.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSegmentedItem.h"
    # Controls - Display
    "${CMAKE_SOURCE_DIR}/controls/FluLabel.h"
    "${CMAKE_SOURCE_DIR}/controls/FluProgressBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluProgressRing.h"
    "${CMAKE_SOURCE_DIR}/controls/FluBusyProgressRing.h"
    "${CMAKE_SOURCE_DIR}/controls/FluInfoBadge.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDotInfoBadge.h"
    "${CMAKE_SOURCE_DIR}/controls/FluImageBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDisplayBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDisplayBoxEx.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDisplayIconBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluInstructions.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTriangle.h"
    "${CMAKE_SOURCE_DIR}/controls/FluStar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimeLine.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimeLineIcon.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimeLineItem.h"
    # Controls - Container
    "${CMAKE_SOURCE_DIR}/controls/FluExpander.h"
    "${CMAKE_SOURCE_DIR}/controls/FluScrollArea.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVScrollView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHScrollView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTableView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluListView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTreeView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVCard.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHCard.h"
    "${CMAKE_SOURCE_DIR}/controls/FluBorder.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCodeBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCodeExpander.h"
    "${CMAKE_SOURCE_DIR}/controls/FluLoopView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHFlipView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVFlipView.h"
    # Controls - Popup/Dialog
    "${CMAKE_SOURCE_DIR}/controls/FluDialog.h"
    "${CMAKE_SOURCE_DIR}/controls/FluMessageBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluMenu.h"
    "${CMAKE_SOURCE_DIR}/controls/FluMenuBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluAction.h"
    "${CMAKE_SOURCE_DIR}/controls/FluRoundMenu.h"
    "${CMAKE_SOURCE_DIR}/controls/FluRoundMenuView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTeachingTip.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTeachingTipContent.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVFlyout.h"
    "${CMAKE_SOURCE_DIR}/controls/FluConfirmFlyout.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPMenu.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPMenuBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluIndicatorRoundMenu.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCompleterMenu.h"
    # Controls - Window (WindowKit-based only)
    "${CMAKE_SOURCE_DIR}/controls/FluWindowKitWidget.h"
    "${CMAKE_SOURCE_DIR}/controls/FluWindowKitTitleBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluWindowKitWindow.h"
    # Controls - Other
    "${CMAKE_SOURCE_DIR}/controls/FluToggleSwitch.h"
    "${CMAKE_SOURCE_DIR}/controls/FluColorPickerButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluColorButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVSplitLine.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHSplitLine.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVRadioGroupBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHRadioGroupBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCalendarView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCalendarDatePicker.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDatePicker.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSettingsLabelBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSettingsSelectBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSettingsVersionBox.h"
    # Controls - Previously excluded (now fixed)
    "${CMAKE_SOURCE_DIR}/controls/FluGifBox.h"
    "${CMAKE_SOURCE_DIR}/controls/FluInfoBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluInfoBarMgr.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTextEditWrap.h"
    "${CMAKE_SOURCE_DIR}/controls/FluAutoSuggestBox.h"
    # Controls - Navigation Views (V)
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationIndicator.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationIconTextItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationFlyIconTextItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationMenuItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationSearchItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationSettingsItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluVNavigationView.h"
    # Controls - Navigation Views (H)
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationIndicator.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationIconTextItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationFlyIconTextItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationMoreItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationSearchItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationSettingsItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluHNavigationView.h"
    # Controls - CommandBar
    "${CMAKE_SOURCE_DIR}/controls/FluCommandBar.h"
    # Controls - Color
    "${CMAKE_SOURCE_DIR}/controls/FluColorFlyout.h"
    "${CMAKE_SOURCE_DIR}/controls/FluColorLabel.h"
    # Controls - MS Navigation
    "${CMAKE_SOURCE_DIR}/controls/FluMSNavigationItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluMSNavigationView.h"
    # Controls - ScrollView
    "${CMAKE_SOURCE_DIR}/controls/FluFWScrollView.h"
    # Controls - Shortcut
    "${CMAKE_SOURCE_DIR}/controls/FluShortcutPicker.h"
    "${CMAKE_SOURCE_DIR}/controls/FluShortcutPickerDlg.h"
    # Controls - System Tray
    "${CMAKE_SOURCE_DIR}/controls/FluSystemTrayIcon.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSystemTrayMenu.h"
    # Controls - ListView Item
    "${CMAKE_SOURCE_DIR}/controls/FluListViewItem.h"
    # Controls - StackedLayout (wrapper)
    "${CMAKE_SOURCE_DIR}/controls/FluStackedLayoutWrap.h"
    # Controls - Frameless Window
    "${CMAKE_SOURCE_DIR}/controls/FluFrameLessTitleBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluFrameLessWidget.h"
    "${CMAKE_SOURCE_DIR}/controls/FluFrameLessWidgetEx.h"
    # Controls - Remaining classes
    "${CMAKE_SOURCE_DIR}/controls/FluAmPmView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCalendarItem.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCalendarSelectDayView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCalendarSelectMonthView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCalendarSelectYearView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCalendarViewTitle.h"
    "${CMAKE_SOURCE_DIR}/controls/FluCodeSyntaxHighlighter.h"
    "${CMAKE_SOURCE_DIR}/controls/FluColorView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluColorViewGradient.h"
    "${CMAKE_SOURCE_DIR}/controls/FluColorViewHHandle.h"
    "${CMAKE_SOURCE_DIR}/controls/FluColorViewVHandle.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDatePickerView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluDatePickerViewMask.h"
    "${CMAKE_SOURCE_DIR}/controls/FluFlowLayout.h"
    "${CMAKE_SOURCE_DIR}/controls/FluIndicatorMenuItemDeleage.h"
    "${CMAKE_SOURCE_DIR}/controls/FluListViewItemDelegate.h"
    "${CMAKE_SOURCE_DIR}/controls/FluMenuAniMgr.h"
    "${CMAKE_SOURCE_DIR}/controls/FluMenuItemDelegate.h"
    "${CMAKE_SOURCE_DIR}/controls/FluMSWindow.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPMenuBarStyle.h"
    "${CMAKE_SOURCE_DIR}/controls/FluPMenuStyle.h"
    "${CMAKE_SOURCE_DIR}/controls/FluScrollBar.h"
    "${CMAKE_SOURCE_DIR}/controls/FluScrollBarArrowButton.h"
    "${CMAKE_SOURCE_DIR}/controls/FluScrollBarHandle.h"
    "${CMAKE_SOURCE_DIR}/controls/FluScrollBarTrunk.h"
    "${CMAKE_SOURCE_DIR}/controls/FluScrollDelegate.h"
    "${CMAKE_SOURCE_DIR}/controls/FluShortcutMenuItemDelegate.h"
    "${CMAKE_SOURCE_DIR}/controls/FluStackedLayout.h"
    "${CMAKE_SOURCE_DIR}/controls/FluSubMenuItemWidget.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTableItemDelegate.h"
    "${CMAKE_SOURCE_DIR}/controls/FluThread.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimePicker24H.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimePicker24HView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimePickerAP.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimePickerAPView.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTimePickerViewMask.h"
    "${CMAKE_SOURCE_DIR}/controls/FluTreeViewItemDelegate.h"
    "${CMAKE_SOURCE_DIR}/controls/FluValueObject.h"
)

# Expected generated wrapper files (Shiboken6 generates lowercase names)
set(GENERATED_WRAPPER_FILES
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/pyside6fluentui_module_wrapper.cpp
    # Utils wrappers
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluthemeutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluconfigutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flustylesheetutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluiconutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flulogutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutranslatorutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluemoijutils_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluobjectptrutils_wrapper.cpp
    # Controls wrappers - Base
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluwidget_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupushbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluiconbutton_wrapper.cpp
    # Controls wrappers - Buttons
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucheckbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluradiobutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutogglebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludropdownbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusplitbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flurepeatbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhyperlinkbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluappbarbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluappbartogglebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flustylebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluscalebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flurotationbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flugraphicalbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluthemebutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluppushbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluwindowkitbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucommandbaritem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucommandbariconitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucommandbaricontextitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucommandbarsplititem_wrapper.cpp
    # Controls wrappers - Input
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flulineedit_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutextedit_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluspinbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludoublespinbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupasswordbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusearchlineedit_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucombobox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluintvalidator_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluslider_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluratingcontrol_wrapper.cpp
    # Controls wrappers - Navigation (simplified)
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutabbar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutabbarcontent_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutabbaritem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutabview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutabwidget_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupagination_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupaginationitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupivot_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupivottitlebar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupivottitlebaritem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusegmented_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusegmenteditem_wrapper.cpp
    # Controls wrappers - Display
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flulabel_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluprogressbar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluprogressring_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flubusyprogressring_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluinfobadge_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucircledot_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluimagebox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludisplaybox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludisplayboxex_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludisplayiconbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluinstructions_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutriangle_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flustar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimeline_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimelineicon_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimelineitem_wrapper.cpp
    # Controls wrappers - Container
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluexpander_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluscrollarea_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvscrollview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhscrollview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutableview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flulistview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutreeview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvcard_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhcard_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluborder_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucodebox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucodeexpander_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluloopview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhflipview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvflipview_wrapper.cpp
    # Controls wrappers - Popup/Dialog
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludialog_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumessagebox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumenu_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumenubar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluaction_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluroundmenu_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluroundmenuview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluteachingtip_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluteachingtipcontent_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvflyout_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluconfirmflyout_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupmenu_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupmenubar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluindicatorroundmenu_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucompletermenu_wrapper.cpp
    # Controls wrappers - Window (WindowKit-based only)
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluwindowkitwidget_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluwindowkittitlebar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluwindowkitwindow_wrapper.cpp
    # Controls wrappers - Other
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutoggleswitch_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutoggleswitchex_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutexttoggleswitchex_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorpickerbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvsplitline_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhsplitline_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvradiogroupbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhradiogroupbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucalendarview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucalendardatepicker_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludatepicker_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusettingslabelbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusettingsselectbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusettingsversionbox_wrapper.cpp
    # Controls wrappers - Previously excluded (now fixed)
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flugifbox_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flushortinfobar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluinfobarmgr_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutexteditwrap_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluautosuggestbox_wrapper.cpp
    # Controls wrappers - Navigation Views (V)
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationindicator_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationicontextitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationflyicontextitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationmenuitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationsearchitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationsettingsitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvnavigationview_wrapper.cpp
    # Controls wrappers - Navigation Views (H)
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationindicator_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationicontextitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationflyicontextitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationmoreitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationsearchitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationsettingsitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluhnavigationview_wrapper.cpp
    # Controls wrappers - CommandBar
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucommandbar_wrapper.cpp
    # Controls wrappers - Color
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorflyout_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorlabel_wrapper.cpp
    # Controls wrappers - MS Navigation
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumsnavigationitem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumsnavigationview_wrapper.cpp
    # Controls wrappers - ScrollView
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flufwscrollview_wrapper.cpp
    # Controls wrappers - Shortcut
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flushortcutpicker_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flushortcutpickerdlg_wrapper.cpp
    # Controls wrappers - System Tray
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusystemtrayicon_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusystemtraymenu_wrapper.cpp
    # Controls wrappers - ListView Item
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flulistviewitem_wrapper.cpp
    # Controls wrappers - StackedLayout (wrapper)
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flustackedlayoutwrap_wrapper.cpp
    # Controls wrappers - Frameless Window
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluframelesstitlebar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluframelesswidget_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluframelesswidgetex_wrapper.cpp
    # Controls wrappers - Remaining classes
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluampmview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucalendaritem_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucalendarselectdayview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucalendarselectmonthview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucalendarselectyearview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucalendarviewtitle_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucodesyntaxhighlighter_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorviewgradient_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorviewhhandle_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flucolorviewvhandle_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludatepickerview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fludatepickerviewmask_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluflowlayout_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluindicatormenuitemdeleage_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flulistviewitemdelegate_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumenuanimgr_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumenuitemdelegate_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flumswindow_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupmenubarstyle_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flupmenustyle_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluscrollbar_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluscrollbararrowbutton_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluscrollbarhandle_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluscrollbartrunk_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluscrolldelegate_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flushortcutmenuitemdelegate_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flustackedlayout_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flusubmenuitemwidget_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutableitemdelegate_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluthread_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimepicker24h_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimepicker24hview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimepickerap_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimepickerapview_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutimepickerviewmask_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/flutreeviewitemdelegate_wrapper.cpp
    ${BINDINGS_OUTPUT_DIR}/PySide6FluentUI/fluvalueobject_wrapper.cpp
)

# Generate bindings using Shiboken6
add_custom_command(
    OUTPUT ${GENERATED_WRAPPER_FILES}
    COMMAND ${SHIBOKEN6_EXECUTABLE}
        --no-suppress-warnings
        --avoid-protected-hack
        --enable-pyside-extensions
        "--include-paths=${CMAKE_SOURCE_DIR}/utils;${CMAKE_SOURCE_DIR}/controls;${CMAKE_SOURCE_DIR}/3rdparty/framelesshelper/include;${CMAKE_BINARY_DIR}/3rdparty/framelesshelper;${PYSIDE6_INCLUDE_DIR};${SHIBOKEN6_INCLUDE_DIR};${QT6_INCLUDE_PATHS}"
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
add_library(PySide6FluentUI MODULE
    ${GENERATED_WRAPPER_FILES}
)

target_include_directories(PySide6FluentUI PRIVATE
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/controls
    ${CMAKE_SOURCE_DIR}/3rdparty/framelesshelper/include
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

target_link_directories(PySide6FluentUI PRIVATE
    ${PYTHON_LIBDIR}
)

target_link_libraries(PySide6FluentUI PRIVATE
    FluentUI::Utils
    FluentUI::Controls
    ${PYSIDE6_LIBRARY}
    ${SHIBOKEN6_LIBRARY}
    Qt6::Core
    Qt6::Widgets
)

set_target_properties(PySide6FluentUI PROPERTIES
    PREFIX ""
    OUTPUT_NAME "PySide6FluentUI"
    SUFFIX ".pyd"
)

# Install Python module
install(TARGETS PySide6FluentUI
    LIBRARY DESTINATION ${Python_SITEARCH}
    RUNTIME DESTINATION ${Python_SITEARCH}
)
