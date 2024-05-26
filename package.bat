@REM定义字符串变量
set curDir=%cd%
@REM 删除所有文件
rd /s /q %curDir%\FluGalleryWin64Msvc\
mkdir %curDir%\FluGalleryWin64Msvc\
@REM 拷贝所有文件
cp %curDir%\x64\Release\FluWinGallery.exe 											%curDir%\FluGalleryWin64Msvc\
cp %curDir%\3rdparty\framelesshelper\bin\release\FramelessHelperCore64.dll 			%curDir%\FluGalleryWin64Msvc\
cp %curDir%\3rdparty\framelesshelper\bin\release\FramelessHelperQuick64.dll 		%curDir%\FluGalleryWin64Msvc\
cp %curDir%\3rdparty\framelesshelper\bin\release\FramelessHelperWidgets64.dll 		%curDir%\FluGalleryWin64Msvc\
C:\Qt\6.5.1\msvc2019_64\bin\windeployqt.exe %curDir%\FluGalleryWin64Msvc\
pause