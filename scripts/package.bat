@REM Package built Gallery into a distributable folder with Qt runtimes.
cd /d "%~dp0.."
set curDir=%cd%

@REM Delete old package
if exist "%curDir%\FluGalleryWin64Msvc\" rd /s /q "%curDir%\FluGalleryWin64Msvc\"
mkdir "%curDir%\FluGalleryWin64Msvc\package"

@REM Copy assets
xcopy /s /e /q /y "%curDir%\res"         "%curDir%\FluGalleryWin64Msvc\res"         >nul
xcopy /s /e /q /y "%curDir%\StyleSheet"  "%curDir%\FluGalleryWin64Msvc\StyleSheet"  >nul
xcopy /s /e /q /y "%curDir%\code"        "%curDir%\FluGalleryWin64Msvc\code"        >nul
xcopy /s /e /q /y "%curDir%\i18n"        "%curDir%\FluGalleryWin64Msvc\i18n"        >nul
xcopy /s /e /q /y "%curDir%\config"      "%curDir%\FluGalleryWin64Msvc\config"      >nul

@REM Copy the built executable
set exeRel=%curDir%\build\%ExeRel%\bin\gallery.exe
if not exist "%exeRel%" set exeRel=%curDir%\build\debug\bin\gallery.exe
copy /y "%exeRel%" "%curDir%\FluGalleryWin64Msvc\package" >nul

@REM Deploy Qt runtime DLLs (use same Qt version the app was built with)
C:\Qt\6.9.0\msvc2022_64\bin\windeployqt.exe "%curDir%\FluGalleryWin64Msvc\package\gallery.exe"

pause