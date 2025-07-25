cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME ModName)
string(REPLACE " " "_" ModName ${ModName})

set(TGT ${ModName})
message("ModName: ${ModName}")

FILE(GLOB DIR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
)

message("add_library(\${TGT} SHARED")
    foreach(f ${DIR_SRCS})
    message("    \"${f}\"")
    endforeach()
message(")")

# qt_add_executable(${TGT}
#     ${DIR_SRCS}
# )
if (${QT_VERSION_MAJOR} LESS 6)
    add_executable(${TGT}
        ${DIR_SRCS}
    )
else()
    qt_add_executable(${TGT}
        ${DIR_SRCS}
    )
endif()

if(USE_QRC)
set(RES_FILES
    "../res/badgelogo.scale-100.png"
    "../res/badgelogo.scale-140.png"
    "../res/badgelogo.scale-180.png"
    "../res/blank.png"
    "../res/ChevronDown.png"
    "../res/ChevronRight.png"
    "../res/ChromeClose.png"
    "../res/CoffeeCup.png"
    "../res/Contacts.txt"
    "../res/CopyLinkTeachingTip.png"
    "../res/folder.png"
    "../res/GalleryHeaderImage.png"
    "../res/LottieLogo1.png"
    "../res/ninegrid.gif"
    "../res/ScrollBottom.png"
    "../res/ScrollTop.png"
    "../res/Slices.png"
    "../res/Slices2.png"
    "../res/SunBlack.png"
    "../res/SunWhite.png"
    "../res/Typography.dark.png"
    "../res/Typography.light.png"
    "../res/widelogo.scale-100.png"
    "../res/widelogo.scale-140.png"
    "../res/widelogo.scale-180.png"
    "../res/WideLogo.scale-80.png"
    "../res/ControlImages/Acrylic.png"
    "../res/ControlImages/AnimatedIcon.png"
    "../res/ControlImages/AnimatedVisualPlayer.png"
    "../res/ControlImages/AnimationInterop.png"
    "../res/ControlImages/AnnotatedScrollBar.png"
    "../res/ControlImages/AppBarButton.png"
    "../res/ControlImages/AppBarSeparator.png"
    "../res/ControlImages/AppBarToggleButton.png"
    "../res/ControlImages/AutomationProperties.png"
    "../res/ControlImages/AutoSuggestBox.png"
    "../res/ControlImages/Border.png"
    "../res/ControlImages/BreadcrumbBar.png"
    "../res/ControlImages/Button.png"
    "../res/ControlImages/CalendarDatePicker.png"
    "../res/ControlImages/CalendarView.png"
    "../res/ControlImages/Canvas.png"
    "../res/ControlImages/Checkbox.png"
    "../res/ControlImages/Clipboard.png"
    "../res/ControlImages/ColorPaletteResources.png"
    "../res/ControlImages/ColorPicker.png"
    "../res/ControlImages/ComboBox.png"
    "../res/ControlImages/CommandBar.png"
    "../res/ControlImages/CommandBarFlyout.png"
    "../res/ControlImages/CompactSizing.png"
    "../res/ControlImages/ConnectedAnimation.png"
    "../res/ControlImages/ContentDialog.png"
    "../res/ControlImages/CreateMultipleWindows.png"
    "../res/ControlImages/DataGrid.png"
    "../res/ControlImages/DatePicker.png"
    "../res/ControlImages/DropDownButton.png"
    "../res/ControlImages/EasingFunction.png"
    "../res/ControlImages/Expander.png"
    "../res/ControlImages/FilePicker.png"
    "../res/ControlImages/FlipView.png"
    "../res/ControlImages/Flyout.png"
    "../res/ControlImages/Grid.png"
    "../res/ControlImages/GridView.png"
    "../res/ControlImages/HyperlinkButton.png"
    "../res/ControlImages/IconElement.png"
    "../res/ControlImages/Image.png"
    "../res/ControlImages/ImplicitTransition.png"
    "../res/ControlImages/InfoBadge.png"
    "../res/ControlImages/InfoBar.png"
    "../res/ControlImages/InkCanvas.png"
    "../res/ControlImages/InkToolbar.png"
    "../res/ControlImages/InputValidation.png"
    "../res/ControlImages/ItemsRepeater.png"
    "../res/ControlImages/ItemsView.png"
    "../res/ControlImages/Line.png"
    "../res/ControlImages/ListBox.png"
    "../res/ControlImages/ListView.png"
    "../res/ControlImages/MediaPlayerElement.png"
    "../res/ControlImages/MenuBar.png"
    "../res/ControlImages/MenuFlyout.png"
    "../res/ControlImages/NavigationView.png"
    "../res/ControlImages/NumberBox.png"
    "../res/ControlImages/PageTransition.png"
    "../res/ControlImages/ParallaxView.png"
    "../res/ControlImages/PasswordBox.png"
    "../res/ControlImages/PersonPicture.png"
    "../res/ControlImages/PipsPager.png"
    "../res/ControlImages/Pivot.png"
    "../res/ControlImages/Placeholder.png"
    "../res/ControlImages/ProgressBar.png"
    "../res/ControlImages/ProgressRing.png"
    "../res/ControlImages/PullToRefresh.png"
    "../res/ControlImages/RadialGradientBrush.png"
    "../res/ControlImages/RadioButton.png"
    "../res/ControlImages/RadioButtons.png"
    "../res/ControlImages/RatingControl.png"
    "../res/ControlImages/RelativePanel.png"
    "../res/ControlImages/RepeatButton.png"
    "../res/ControlImages/RevealFocus.png"
    "../res/ControlImages/RichEditBox.png"
    "../res/ControlImages/RichTextBlock.png"
    "../res/ControlImages/ScrollView.png"
    "../res/ControlImages/ScrollViewer.png"
    "../res/ControlImages/SemanticZoom.png"
    "../res/ControlImages/Shape.png"
    "../res/ControlImages/Slider.png"
    "../res/ControlImages/Sound.png"
    "../res/ControlImages/SplitButton.png"
    "../res/ControlImages/SplitView.png"
    "../res/ControlImages/StackPanel.png"
    "../res/ControlImages/StandardUICommand.png"
    "../res/ControlImages/SwipeControl.png"
    "../res/ControlImages/TabView.png"
    "../res/ControlImages/TeachingTip.png"
    "../res/ControlImages/TextBlock.png"
    "../res/ControlImages/TextBox.png"
    "../res/ControlImages/ThemeTransition.png"
    "../res/ControlImages/TimePicker.png"
    "../res/ControlImages/TitleBar.png"
    "../res/ControlImages/ToggleButton.png"
    "../res/ControlImages/ToggleSplitButton.png"
    "../res/ControlImages/ToggleSwitch.png"
    "../res/ControlImages/ToolTip.png"
    "../res/ControlImages/TreeView.png"
    "../res/ControlImages/VariableSizedWrapGrid.png"
    "../res/ControlImages/Viewbox.png"
    "../res/ControlImages/WebView.png"
    "../res/ControlImages/XamlUICommand.png"
    "../res/ControlResImages/CheckBox-Black.png"
    "../res/ControlResImages/CheckBox-White.png"
    "../res/ControlResImages/CheckBoxPressed-Black.png"
    "../res/ControlResImages/CheckBoxPressed-White.png"
    "../res/ControlResImages/ChevronDown-Dark.png"
    "../res/ControlResImages/ChevronDown-Light.png"
    "../res/ControlResImages/ChevronRight-Light.png"
    "../res/ControlResImages/ChevronRight-Dark.png"
    "../res/ControlResImages/RadioButton-Black.png"
    "../res/ControlResImages/RadioButton-White.png"
    "../res/ControlResImages/RadioButtonHover-Black.png"
    "../res/ControlResImages/RadioButtonHover-White.png"
    "../res/ControlResImages/RadioButtonPressed-Black.png"
    "../res/ControlResImages/RadioButtonPressed-White.png"
    "../res/ControlResImages/SpinBoxDown-Dark.png"
    "../res/ControlResImages/SpinBoxDown-Light.png"
    "../res/ControlResImages/SpinBoxDownDisabled-Dark.png"
    "../res/ControlResImages/SpinBoxDownDisabled-Light.png"
    "../res/ControlResImages/SpinBoxUp-Dark.png"
    "../res/ControlResImages/SpinBoxUp-Light.png"
    "../res/ControlResImages/SpinBoxUpDisabled-Dark.png"
    "../res/ControlResImages/SpinBoxUpDisabled-Light.png"
    "../res/ControlResImages/ToggleSwitchDisabled-Dark.png"
    "../res/ControlResImages/ToggleSwitchDisabled-light.png"
    "../res/ControlResImages/ToggleSwitchOff-Dark.png"
    "../res/ControlResImages/ToggleSwitchOff-light.png"
    "../res/ControlResImages/ToggleSwitchOffHover-Dark.png"
    "../res/ControlResImages/ToggleSwitchOffHover-light.png"
    "../res/ControlResImages/ToggleSwitchOffPressed-Dark.png"
    "../res/ControlResImages/ToggleSwitchOffPressed-light.png"
    "../res/ControlResImages/ToggleSwitchOn-Dark.png"
    "../res/ControlResImages/ToggleSwitchOn-light.png"
    "../res/ControlResImages/ToggleSwitchOnHover-Dark.png"
    "../res/ControlResImages/ToggleSwitchOnHover-light.png"
    "../res/ControlResImages/ToggleSwitchOnPressed-Dark.png"
    "../res/ControlResImages/ToggleSwitchOnPressed-light.png"
    "../res/HomeHeaderTiles/github-mark-white.png"
    "../res/HomeHeaderTiles/github-mark-white.svg"
    "../res/HomeHeaderTiles/github-mark.png"
    "../res/HomeHeaderTiles/github-mark.svg"
    "../res/HomeHeaderTiles/Header-Store.dark.png"
    "../res/HomeHeaderTiles/Header-Store.light.png"
    "../res/HomeHeaderTiles/Header-Toolkit.png"
    "../res/HomeHeaderTiles/Header-WindowsDesign.png"
    "../res/HomeHeaderTiles/Header-WinUIGallery.png"
    "../res/SampleMedia/cliff.jpg"
    "../res/SampleMedia/fishes.wmv"
    "../res/SampleMedia/grapes.jpg"
    "../res/SampleMedia/ladybug.wmv"
    "../res/SampleMedia/LandscapeImage1.jpg"
    "../res/SampleMedia/LandscapeImage10.jpg"
    "../res/SampleMedia/LandscapeImage11.jpg"
    "../res/SampleMedia/LandscapeImage12.jpg"
    "../res/SampleMedia/LandscapeImage13.jpg"
    "../res/SampleMedia/LandscapeImage2.jpg"
    "../res/SampleMedia/LandscapeImage3.jpg"
    "../res/SampleMedia/LandscapeImage4.jpg"
    "../res/SampleMedia/LandscapeImage5.jpg"
    "../res/SampleMedia/LandscapeImage6.jpg"
    "../res/SampleMedia/LandscapeImage7.jpg"
    "../res/SampleMedia/LandscapeImage8.jpg"
    "../res/SampleMedia/LandscapeImage9.jpg"
    "../res/SampleMedia/MirrorPCConsent.svg"
    "../res/SampleMedia/rainier.jpg"
    "../res/SampleMedia/sunset.jpg"
    "../res/SampleMedia/treetops.jpg"
    "../res/SampleMedia/valley.jpg"
    "../res/TabViewIcons/cmd.png"
    "../res/TabViewIcons/linux.png"
    "../res/TabViewIcons/powershell.png"
    "../res/Tiles/BadgeLogo.scale-100.png"
    "../res/Tiles/BadgeLogo.scale-125.png"
    "../res/Tiles/BadgeLogo.scale-150.png"
    "../res/Tiles/BadgeLogo.scale-200.png"
    "../res/Tiles/BadgeLogo.scale-400.png"
    "../res/Tiles/GalleryIcon.ico"
    "../res/Tiles/LargeTile.scale-100.png"
    "../res/Tiles/LargeTile.scale-125.png"
    "../res/Tiles/LargeTile.scale-150.png"
    "../res/Tiles/LargeTile.scale-200.png"
    "../res/Tiles/LargeTile.scale-400.png"
    "../res/Tiles/SmallTile-sdk.altform-lightunplated_targetsize-16.png"
    "../res/Tiles/SmallTile-sdk.altform-lightunplated_targetsize-24.png"
    "../res/Tiles/SmallTile-sdk.altform-lightunplated_targetsize-256.png"
    "../res/Tiles/SmallTile-sdk.altform-lightunplated_targetsize-32.png"
    "../res/Tiles/SmallTile-sdk.altform-lightunplated_targetsize-48.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-16.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-20.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-24.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-256.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-30.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-32.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-36.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-40.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-48.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-60.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-64.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-72.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-80.png"
    "../res/Tiles/SmallTile-sdk.altform-unplated_targetsize-96.png"
    "../res/Tiles/SmallTile-sdk.scale-100.png"
    "../res/Tiles/SmallTile-sdk.scale-125.png"
    "../res/Tiles/SmallTile-sdk.scale-150.png"
    "../res/Tiles/SmallTile-sdk.scale-200.png"
    "../res/Tiles/SmallTile-sdk.scale-400.png"
    "../res/Tiles/SmallTile-sdk.targetsize-16.png"
    "../res/Tiles/SmallTile-sdk.targetsize-20.png"
    "../res/Tiles/SmallTile-sdk.targetsize-24.png"
    "../res/Tiles/SmallTile-sdk.targetsize-256.png"
    "../res/Tiles/SmallTile-sdk.targetsize-30.png"
    "../res/Tiles/SmallTile-sdk.targetsize-32.png"
    "../res/Tiles/SmallTile-sdk.targetsize-36.png"
    "../res/Tiles/SmallTile-sdk.targetsize-40.png"
    "../res/Tiles/SmallTile-sdk.targetsize-48.png"
    "../res/Tiles/SmallTile-sdk.targetsize-60.png"
    "../res/Tiles/SmallTile-sdk.targetsize-64.png"
    "../res/Tiles/SmallTile-sdk.targetsize-72.png"
    "../res/Tiles/SmallTile-sdk.targetsize-80.png"
    "../res/Tiles/SmallTile-sdk.targetsize-96.png"
    "../res/Tiles/SmallTile.scale-100.png"
    "../res/Tiles/SmallTile.scale-125.png"
    "../res/Tiles/SmallTile.scale-150.png"
    "../res/Tiles/SmallTile.scale-200.png"
    "../res/Tiles/SmallTile.scale-400.png"
    "../res/Tiles/splash-sdk.scale-100.png"
    "../res/Tiles/splash-sdk.scale-125.png"
    "../res/Tiles/splash-sdk.scale-150.png"
    "../res/Tiles/splash-sdk.scale-200.png"
    "../res/Tiles/splash-sdk.scale-400.png"
    "../res/Tiles/squaretile-sdk.scale-100.png"
    "../res/Tiles/squaretile-sdk.scale-125.png"
    "../res/Tiles/squaretile-sdk.scale-150.png"
    "../res/Tiles/squaretile-sdk.scale-200.png"
    "../res/Tiles/squaretile-sdk.scale-400.png"
    "../res/Tiles/StoreLogo-sdk.scale-100.png"
    "../res/Tiles/StoreLogo-sdk.scale-125.png"
    "../res/Tiles/StoreLogo-sdk.scale-150.png"
    "../res/Tiles/StoreLogo-sdk.scale-200.png"
    "../res/Tiles/StoreLogo-sdk.scale-400.png"
    "../res/Tiles/Tile_General.png"
    "../res/Tiles/TitlebarLogo.png"
    "../res/Tiles/widelogo.scale-100.png"
    "../res/Tiles/widelogo.scale-140.png"
    "../res/Tiles/widelogo.scale-180.png"
    "../res/Tiles/WideLogo.scale-80.png"
    "../res/Tiles/WideTile.scale-100.png"
    "../res/Tiles/WideTile.scale-125.png"
    "../res/Tiles/WideTile.scale-150.png"
    "../res/Tiles/WideTile.scale-200.png"
    "../res/Tiles/WideTile.scale-400.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.scale-400_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-16_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-16_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-20_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-20_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-24_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-24_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-256_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-256_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-30_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-30_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-32_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-32_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-36_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-36_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-40_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-40_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-48_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-48_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-60_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-60_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-64_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-64_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-72_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-72_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-80_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-80_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-96_altform-unplated_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryAppList.targetsize-96_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryBadgeLogo.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryBadgeLogo.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryBadgeLogo.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryBadgeLogo.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryBadgeLogo.scale-400_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryLargeTile.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryLargeTile.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryLargeTile.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryLargeTile.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryLargeTile.scale-400_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryMedTile.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryMedTile.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryMedTile.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryMedTile.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryMedTile.scale-400_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySmallTile.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySmallTile.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySmallTile.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySmallTile.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySmallTile.scale-400_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySplashScreen.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySplashScreen.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySplashScreen.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySplashScreen.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGallerySplashScreen.scale-400_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryStoreLogo.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryStoreLogo.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryStoreLogo.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryStoreLogo.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryStoreLogo.scale-400_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryWideTile.scale-100_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryWideTile.scale-125_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryWideTile.scale-150_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryWideTile.scale-200_contrast-black.png"
    "../res/Tiles/contrast-black/XAMLControlsGalleryWideTile.scale-400_contrast-black.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.scale-400_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-16_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-16_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-20_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-20_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-24_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-24_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-256_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-256_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-30_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-30_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-32_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-32_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-36_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-36_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-40_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-40_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-48_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-48_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-60_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-60_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-64_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-64_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-72_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-72_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-80_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-80_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-96_altform-unplated_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryAppList.targetsize-96_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryBadgeLogo.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryBadgeLogo.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryBadgeLogo.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryBadgeLogo.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryBadgeLogo.scale-400_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryLargeTile.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryLargeTile.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryLargeTile.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryLargeTile.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryLargeTile.scale-400_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryMedTile.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryMedTile.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryMedTile.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryMedTile.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryMedTile.scale-400_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySmallTile.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySmallTile.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySmallTile.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySmallTile.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySmallTile.scale-400_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySplashScreen.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySplashScreen.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySplashScreen.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySplashScreen.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGallerySplashScreen.scale-400_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryStoreLogo.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryStoreLogo.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryStoreLogo.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryStoreLogo.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryStoreLogo.scale-400_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryWideTile.scale-100_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryWideTile.scale-125_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryWideTile.scale-150_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryWideTile.scale-200_contrast-white.png"
    "../res/Tiles/contrast-white/XAMLControlsGalleryWideTile.scale-400_contrast-white.png"
    "../res/ControlImages/CaptureElement.png"
    "../res/ControlImages/MapControl.png"
    "../res/ControlImages/ScratchPad.png"
    "../res/ControlResImages/CheckboxIndeterminate-Black.png"
    "../res/ControlResImages/CheckboxIndeterminate-White.png"
    "../res/ControlResImages/ChevronRight-Black.png"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${RES_FILES})

qt_add_resources(${TGT} "FluWinGalleryRes"
    PREFIX "/"
    BASE ".."
    FILES
    ${RES_FILES}
)
set(CODE_FILES
    "../code/AppBarButtonPageCode1.md"
    "../code/AppBarButtonPageCode2.md"
    "../code/AppBarToggleButtonPageCode1.md"
    "../code/AutoSuggestBoxPageCode1.md"
    "../code/BorderPageCode1.md"
    "../code/ButtonPageCode1.md"
    "../code/ButtonPageCode2.md"
    "../code/ButtonPageCode3.md"
    "../code/CalendarDatePickerPageCode1.md"
    "../code/CalendarViewPageCode1.md"
    "../code/CheckBoxPageCode1.md"
    "../code/CheckBoxPageCode2.md"
    "../code/ComboBoxPageCode1.md"
    "../code/ContentDialogPageCode1.md"
    "../code/DatePickerPageCode1.md"
    "../code/DropDownButtonPageCode1.md"
    "../code/DropDownButtonPageCode2.md"
    "../code/ExpanderPageCode1.md"
    "../code/ExpanderPageCode2.md"
    "../code/ExpanderPageCode3.md"
    "../code/FlipViewPageCode1.md"
    "../code/FlipViewPageCode2.md"
    "../code/FlyoutPageCode1.md"
    "../code/HyperLinkButtonPageCode1.md"
    "../code/InfoBadgePageCode1.md"
    "../code/InfoBarPageCode1.md"
    "../code/InfoBarPageCode2.md"
    "../code/ListViewPageCode1.md"
    "../code/MenuBarPageCode1.md"
    "../code/MenuBarPageCode2.md"
    "../code/NumberBoxPageCode1.md"
    "../code/NumberBoxPageCode2.md"
    "../code/PasswordBoxPageCode1.md"
    "../code/PasswordBoxPageCode2.md"
    "../code/PivotPageCode1.md"
    "../code/ProgressBarPageCode1.md"
    "../code/ProgressRingPageCode1.md"
    "../code/ProgressRingPageCode2.md"
    "../code/ProgressRingPageCode3.md"
    "../code/RadioButtonPageCode1.md"
    "../code/RadioButtonsPageCode1.md"
    "../code/RatingControlPageCode1.md"
    "../code/RepeatButtonPageCode1.md"
    "../code/ScrollViewPageCode1.md"
    "../code/SliderPageCode1.md"
    "../code/SliderPageCode2.md"
    "../code/SplitButtonPageCode1.md"
    "../code/TableViewPageCode1.md"
    "../code/TextBoxPageCode1.md"
    "../code/TimePickerPageCode1.md"
    "../code/TimePickerPageCode2.md"
    "../code/ToggleButtonPageCode1.md"
    "../code/ToggleSwitchPageCode1.md"
    "../code/TreeViewPageCode1.md"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${CODE_FILES})

qt_add_resources(${TGT} "FluWinGalleryCode"
    PREFIX "/"
    BASE ".."
    FILES
    ${CODE_FILES}
)

set(QSS_FILES
    "../StyleSheet/dark/FluAEmptyPage.qss"
    "../StyleSheet/dark/FluAllSamplesPage.qss"
    "../StyleSheet/dark/FluAppBarButtonPage.qss"
    "../StyleSheet/dark/FluAppBarToggleButtonPage.qss"
    "../StyleSheet/dark/FluATitlePage.qss"
    "../StyleSheet/dark/FluAutoSuggestBoxPage.qss"
    "../StyleSheet/dark/FluBasicInputPage.qss"
    "../StyleSheet/dark/FluBorderPage.qss"
    "../StyleSheet/dark/FluButtonPage.qss"
    "../StyleSheet/dark/FluCalendarDatePickerPage.qss"
    "../StyleSheet/dark/FluCalendarViewPage.qss"
    "../StyleSheet/dark/FluCheckBoxPage.qss"
    "../StyleSheet/dark/FluCollectionsPage.qss"
    "../StyleSheet/dark/FluColorPickerPage.qss"
    "../StyleSheet/dark/FluComboBoxPage.qss"
    "../StyleSheet/dark/FluContentDialogPage.qss"
    "../StyleSheet/dark/FluDateAndTimePage.qss"
    "../StyleSheet/dark/FluDatePickerPage.qss"
    "../StyleSheet/dark/FluDialogsAndFlyoutsPage.qss"
    "../StyleSheet/dark/FluDropDownButtonPage.qss"
    "../StyleSheet/dark/FluEmoijsPage.qss"
    "../StyleSheet/dark/FluExpanderPage.qss"
    "../StyleSheet/dark/FluFlipViewPage.qss"
    "../StyleSheet/dark/FluFlyoutPage.qss"
    "../StyleSheet/dark/FluGalleryWindow.qss"
    "../StyleSheet/dark/FluHomePage.qss"
    "../StyleSheet/dark/FluHomePageTitle.qss"
    "../StyleSheet/dark/FluHyperLinkButtonPage.qss"
    "../StyleSheet/dark/FluIconsPage.qss"
    "../StyleSheet/dark/FluInfoBadgePage.qss"
    "../StyleSheet/dark/FluInfoBarPage.qss"
    "../StyleSheet/dark/FluLayoutPage.qss"
    "../StyleSheet/dark/FluListViewPage.qss"
    "../StyleSheet/dark/FluMediaPage.qss"
    "../StyleSheet/dark/FluMenuAndToolBarsPage.qss"
    "../StyleSheet/dark/FluMenuBarPage.qss"
    "../StyleSheet/dark/FluNavigationPage.qss"
    "../StyleSheet/dark/FluNumberBoxPage.qss"
    "../StyleSheet/dark/FluPasswordBoxPage.qss"
    "../StyleSheet/dark/FluPivotPage.qss"
    "../StyleSheet/dark/FluProgressBar.qss"
    "../StyleSheet/dark/FluProgressBarPage.qss"
    "../StyleSheet/dark/FluProgressRingPage.qss"
    "../StyleSheet/dark/FluRadioButtonPage.qss"
    "../StyleSheet/dark/FluRadioButtonsPage.qss"
    "../StyleSheet/dark/FluRatingControlPage.qss"
    "../StyleSheet/dark/FluRepeatButtonPage.qss"
    "../StyleSheet/dark/FluScrollingPage.qss"
    "../StyleSheet/dark/FluScrollViewPage.qss"
    "../StyleSheet/dark/FluSettingPage.qss"
    "../StyleSheet/dark/FluSliderPage.qss"
    "../StyleSheet/dark/FluSplitButtonPage.qss"
    "../StyleSheet/dark/FluStatusAndInfoPage.qss"
    "../StyleSheet/dark/FluTableViewPage.qss"
    "../StyleSheet/dark/FluTextBoxPage.qss"
    "../StyleSheet/dark/FluTextPage.qss"
    "../StyleSheet/dark/FluTimePickerPage.qss"
    "../StyleSheet/dark/FluToggleButtonPage.qss"
    "../StyleSheet/dark/FluToggleSwitchPage.qss"
    "../StyleSheet/dark/FluTreeViewPage.qss"
    "../StyleSheet/dark/FluTypeographyPage.qss"
    "../StyleSheet/light/FluAEmptyPage.qss"
    "../StyleSheet/light/FluAllSamplesPage.qss"
    "../StyleSheet/light/FluAppBarButtonPage.qss"
    "../StyleSheet/light/FluAppBarToggleButtonPage.qss"
    "../StyleSheet/light/FluATitlePage.qss"
    "../StyleSheet/light/FluAutoSuggestBoxPage.qss"
    "../StyleSheet/light/FluBasicInputPage.qss"
    "../StyleSheet/light/FluBorderPage.qss"
    "../StyleSheet/light/FluButtonPage.qss"
    "../StyleSheet/light/FluCalendarDatePickerPage.qss"
    "../StyleSheet/light/FluCalendarViewPage.qss"
    "../StyleSheet/light/FluCheckBoxPage.qss"
    "../StyleSheet/light/FluCollectionsPage.qss"
    "../StyleSheet/light/FluColorPickerPage.qss"
    "../StyleSheet/light/FluComboBoxPage.qss"
    "../StyleSheet/light/FluContentDialogPage.qss"
    "../StyleSheet/light/FluDateAndTimePage.qss"
    "../StyleSheet/light/FluDatePickerPage.qss"
    "../StyleSheet/light/FluDialogsAndFlyoutsPage.qss"
    "../StyleSheet/light/FluDropDownButtonPage.qss"
    "../StyleSheet/light/FluEmoijsPage.qss"
    "../StyleSheet/light/FluExpanderPage.qss"
    "../StyleSheet/light/FluFlipViewPage.qss"
    "../StyleSheet/light/FluFlyoutPage.qss"
    "../StyleSheet/light/FluGalleryWindow.qss"
    "../StyleSheet/light/FluHomePage.qss"
    "../StyleSheet/light/FluHomePageTitle.qss"
    "../StyleSheet/light/FluHyperLinkButtonPage.qss"
    "../StyleSheet/light/FluIconsPage.qss"
    "../StyleSheet/light/FluInfoBadgePage.qss"
    "../StyleSheet/light/FluInfoBarPage.qss"
    "../StyleSheet/light/FluLayoutPage.qss"
    "../StyleSheet/light/FluListViewPage.qss"
    "../StyleSheet/light/FluMediaPage.qss"
    "../StyleSheet/light/FluMenuAndToolBarsPage.qss"
    "../StyleSheet/light/FluMenuBarPage.qss"
    "../StyleSheet/light/FluNavigationPage.qss"
    "../StyleSheet/light/FluNumberBoxPage.qss"
    "../StyleSheet/light/FluPasswordBoxPage.qss"
    "../StyleSheet/light/FluPivotPage.qss"
    "../StyleSheet/light/FluProgressBarPage.qss"
    "../StyleSheet/light/FluProgressRingPage.qss"
    "../StyleSheet/light/FluRadioButtonPage.qss"
    "../StyleSheet/light/FluRadioButtonsPage.qss"
    "../StyleSheet/light/FluRatingControlPage.qss"
    "../StyleSheet/light/FluRepeatButtonPage.qss"
    "../StyleSheet/light/FluScrollingPage.qss"
    "../StyleSheet/light/FluScrollViewPage.qss"
    "../StyleSheet/light/FluSettingPage.qss"
    "../StyleSheet/light/FluSliderPage.qss"
    "../StyleSheet/light/FluSplitButtonPage.qss"
    "../StyleSheet/light/FluStatusAndInfoPage.qss"
    "../StyleSheet/light/FluTableViewPage.qss"
    "../StyleSheet/light/FluTextBoxPage.qss"
    "../StyleSheet/light/FluTextPage.qss"
    "../StyleSheet/light/FluTimePickerPage.qss"
    "../StyleSheet/light/FluToggleButtonPage.qss"
    "../StyleSheet/light/FluToggleSwitchPage.qss"
    "../StyleSheet/light/FluTreeViewPage.qss"
    "../StyleSheet/light/FluTypeographyPage.qss"
    "../StyleSheet/atomOneDark/FluAEmptyPage.qss"
    "../StyleSheet/atomOneDark/FluAllSamplesPage.qss"
    "../StyleSheet/atomOneDark/FluAppBarButtonPage.qss"
    "../StyleSheet/atomOneDark/FluAppBarToggleButtonPage.qss"
    "../StyleSheet/atomOneDark/FluATitlePage.qss"
    "../StyleSheet/atomOneDark/FluAutoSuggestBoxPage.qss"
    "../StyleSheet/atomOneDark/FluBasicInputPage.qss"
    "../StyleSheet/atomOneDark/FluBorderPage.qss"
    "../StyleSheet/atomOneDark/FluButtonPage.qss"
    "../StyleSheet/atomOneDark/FluCalendarDatePickerPage.qss"
    "../StyleSheet/atomOneDark/FluCalendarViewPage.qss"
    "../StyleSheet/atomOneDark/FluCheckBoxPage.qss"
    "../StyleSheet/atomOneDark/FluCollectionsPage.qss"
    "../StyleSheet/atomOneDark/FluColorPickerPage.qss"
    "../StyleSheet/atomOneDark/FluComboBoxPage.qss"
    "../StyleSheet/atomOneDark/FluContentDialogPage.qss"
    "../StyleSheet/atomOneDark/FluDateAndTimePage.qss"
    "../StyleSheet/atomOneDark/FluDatePickerPage.qss"
    "../StyleSheet/atomOneDark/FluDialogsAndFlyoutsPage.qss"
    "../StyleSheet/atomOneDark/FluDropDownButtonPage.qss"
    "../StyleSheet/atomOneDark/FluEmoijsPage.qss"
    "../StyleSheet/atomOneDark/FluExpanderPage.qss"
    "../StyleSheet/atomOneDark/FluFlipViewPage.qss"
    "../StyleSheet/atomOneDark/FluFlyoutPage.qss"
    "../StyleSheet/atomOneDark/FluGalleryWindow.qss"
    "../StyleSheet/atomOneDark/FluHomePage.qss"
    "../StyleSheet/atomOneDark/FluHomePageTitle.qss"
    "../StyleSheet/atomOneDark/FluHyperLinkButtonPage.qss"
    "../StyleSheet/atomOneDark/FluIconsPage.qss"
    "../StyleSheet/atomOneDark/FluInfoBadgePage.qss"
    "../StyleSheet/atomOneDark/FluInfoBarPage.qss"
    "../StyleSheet/atomOneDark/FluLayoutPage.qss"
    "../StyleSheet/atomOneDark/FluListViewPage.qss"
    "../StyleSheet/atomOneDark/FluMediaPage.qss"
    "../StyleSheet/atomOneDark/FluMenuAndToolBarsPage.qss"
    "../StyleSheet/atomOneDark/FluMenuBarPage.qss"
    "../StyleSheet/atomOneDark/FluNavigationPage.qss"
    "../StyleSheet/atomOneDark/FluNumberBoxPage.qss"
    "../StyleSheet/atomOneDark/FluPasswordBoxPage.qss"
    "../StyleSheet/atomOneDark/FluPivotPage.qss"
    "../StyleSheet/atomOneDark/FluProgressBarPage.qss"
    "../StyleSheet/atomOneDark/FluProgressRingPage.qss"
    "../StyleSheet/atomOneDark/FluRadioButtonPage.qss"
    "../StyleSheet/atomOneDark/FluRadioButtonsPage.qss"
    "../StyleSheet/atomOneDark/FluRatingControlPage.qss"
    "../StyleSheet/atomOneDark/FluRepeatButtonPage.qss"
    "../StyleSheet/atomOneDark/FluScrollingPage.qss"
    "../StyleSheet/atomOneDark/FluScrollViewPage.qss"
    "../StyleSheet/atomOneDark/FluSettingPage.qss"
    "../StyleSheet/atomOneDark/FluSliderPage.qss"
    "../StyleSheet/atomOneDark/FluSplitButtonPage.qss"
    "../StyleSheet/atomOneDark/FluStatusAndInfoPage.qss"
    "../StyleSheet/atomOneDark/FluTableViewPage.qss"
    "../StyleSheet/atomOneDark/FluTextBoxPage.qss"
    "../StyleSheet/atomOneDark/FluTextPage.qss"
    "../StyleSheet/atomOneDark/FluTimePickerPage.qss"
    "../StyleSheet/atomOneDark/FluToggleButtonPage.qss"
    "../StyleSheet/atomOneDark/FluToggleSwitchPage.qss"
    "../StyleSheet/atomOneDark/FluTreeViewPage.qss"
    "../StyleSheet/atomOneDark/FluTypeographyPage.qss"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${QSS_FILES})

qt_add_resources(${TGT} "FluWinGalleryQss"
    PREFIX "/"
    BASE ".."
    FILES
    ${QSS_FILES}
)

set(I18N_FILES
    "../i18n/zh-CN.qm"
    "../i18n/en-US.qm"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${I18N_FILES})

qt_add_resources(${TGT} "FluWinGalleryI18n"
    PREFIX "/"
    BASE ".."
    FILES
    ${I18N_FILES}
)

endif()

if (USE_QRC)
    add_definitions(-DUSE_QRC)
endif()

target_link_libraries(${TGT}
    PRIVATE
    FluControls
)

set_target_properties(${TGT} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

if (NOT USE_QRC)
add_dependencies(${TGT} resource_copy)
endif()

include(GNUInstallDirs)
install(TARGETS ${TGT}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(${QT_VERSION} VERSION_GREATER 6.3.0)
qt_generate_deploy_app_script(
     TARGET ${TGT}
     OUTPUT_SCRIPT deploy_script
     NO_UNSUPPORTED_PLATFORM_ERROR
 )
 install(SCRIPT ${deploy_script})
 endif()
