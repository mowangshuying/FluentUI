@REM 删除所有文件
rd /s /q E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc\
mkdir E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc\package
@REM 拷贝所有文件
cp -r E:\CodeLibraries\CppQtFluentUi888\res							E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc
cp -r E:\CodeLibraries\CppQtFluentUi888\StyleSheet						E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc
cp -r E:\CodeLibraries\CppQtFluentUi888\code						E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc
cp E:\CodeLibraries\CppQtFluentUi888\x64\Release\FluWinGallery.exe 				E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc\package
cp E:\CodeLibraries\CppQtFluentUi888\3rdparty\framelesshelper\bin\release\FramelessHelperCore64.dll 		E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc\package
cp E:\CodeLibraries\CppQtFluentUi888\3rdparty\framelesshelper\bin\release\FramelessHelperQuick64.dll 		E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc\package
cp E:\CodeLibraries\CppQtFluentUi888\3rdparty\framelesshelper\bin\release\FramelessHelperWidgets64.dll 	E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc\package
C:\Qt\6.5.1\msvc2019_64\bin\windeployqt.exe E:\CodeLibraries\CppQtFluentUi888\FluGalleryWin64Msvc\package
pause