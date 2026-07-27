@echo off
REM PySide6FluentUI Wheel Build Script
REM Prerequisites:
REM   - Visual Studio 2022 (MSVC)
REM   - Qt 6.8.1 installed at C:\Qt\6.8.1\msvc2022_64
REM   - Python 3.13 with: pip install PySide6==6.8.3 shiboken6==6.8.3 shiboken6-generator==6.8.3 build
REM
REM Usage: build_wheel.bat [Qt_PATH]
REM   Qt_PATH defaults to C:/Qt/6.8.1/msvc2022_64

setlocal enabledelayedexpansion

set QT_PATH=%~1
if "%QT_PATH%"=="" set QT_PATH=C:/Qt/6.8.1/msvc2022_64

set PROJECT_ROOT=%~dp0..\..
set BUILD_DIR=%PROJECT_ROOT%\build_wheel_temp
set PKG_DIR=%~dp0PySide6FluentUI

echo === PySide6FluentUI Wheel Builder ===
echo Qt path: %QT_PATH%
echo Project root: %PROJECT_ROOT%
echo.

REM Step 1: CMake configure
echo [1/6] Configuring CMake...
cmake -DBUILD_PYTHON_BINDINGS=ON -DBUILD_GALLERY=OFF -DCMAKE_PREFIX_PATH=%QT_PATH% -G"Visual Studio 17 2022" -A x64 -B "%BUILD_DIR%" -S "%PROJECT_ROOT%"
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed!
    exit /b 1
)

REM Step 2: Build the Python module (and dependencies)
echo [2/6] Building PySide6FluentUI module...
cmake --build "%BUILD_DIR%" --config Release
if %ERRORLEVEL% neq 0 (
    echo ERROR: Build failed!
    exit /b 1
)

REM Step 3: Copy .pyd to package directory
echo [3/6] Copying PySide6FluentUI.pyd...
set PYD_PATH=%BUILD_DIR%\bindings\PySide6\Release\PySide6FluentUI.pyd
if not exist "%PYD_PATH%" (
    echo ERROR: PySide6FluentUI.pyd not found at %PYD_PATH%
    exit /b 1
)
copy /Y "%PYD_PATH%" "%PKG_DIR%\PySide6FluentUI.pyd"

REM Step 4: Copy runtime DLLs
echo [4/6] Copying runtime DLLs...
REM qtadvanceddocking-qt6.dll (3rdparty ADS library, not available via pip)
set ADS_DLL=%BUILD_DIR%\bin\qtadvanceddocking-qt6.dll
if exist "%ADS_DLL%" (
    copy /Y "%ADS_DLL%" "%PKG_DIR%\qtadvanceddocking-qt6.dll"
) else (
    echo WARNING: qtadvanceddocking-qt6.dll not found, skipping
)
REM Qt6Core5Compat.dll (not included in PySide6 pip package)
for /f "delims=" %%i in ('python -c "import os; p='%QT_PATH%'.replace('/','\\'); print(os.path.join(p, 'bin', 'Qt6Core5Compat.dll'))"') do set QT5COMPAT=%%i
if exist "%QT5COMPAT%" (
    copy /Y "%QT5COMPAT%" "%PKG_DIR%\Qt6Core5Compat.dll"
) else (
    echo WARNING: Qt6Core5Compat.dll not found at %QT5COMPAT%, skipping
)

REM Step 5: Generate .pyi type stubs
echo [5/6] Generating type stubs...
python "%~dp0generate_stubs.py" "%BUILD_DIR%" "%QT_PATH%" "%PKG_DIR%"
if %ERRORLEVEL% neq 0 (
    echo WARNING: Stub generation failed, wheel will lack IDE type hints
)

REM Step 6: Build wheel
echo [6/6] Building wheel...
pushd "%~dp0"
python -m build --wheel
popd
if %ERRORLEVEL% neq 0 (
    echo ERROR: Wheel build failed!
    exit /b 1
)

echo.
echo === SUCCESS ===
echo Wheel output: %~dp0dist\
dir "%~dp0dist\*.whl" 2>nul
echo.
echo Install with: pip install dist\pyside6fluentui-1.0.0-py3-none-any.whl

REM Cleanup
rmdir /S /Q "%BUILD_DIR%" 2>nul

endlocal
