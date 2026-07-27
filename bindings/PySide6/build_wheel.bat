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

echo === PySide6FluentUI Wheel Builder ===
echo Qt path: %QT_PATH%
echo Project root: %PROJECT_ROOT%
echo.

REM Step 1: CMake configure
echo [1/4] Configuring CMake...
cmake -DBUILD_PYTHON_BINDINGS=ON -DBUILD_GALLERY=OFF -DCMAKE_PREFIX_PATH=%QT_PATH% -G"Visual Studio 17 2022" -A x64 -B "%BUILD_DIR%" -S "%PROJECT_ROOT%"
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed!
    exit /b 1
)

REM Step 2: Build the Python module
echo [2/4] Building PySide6FluentUI module...
cmake --build "%BUILD_DIR%" --config Release --target PySide6FluentUI
if %ERRORLEVEL% neq 0 (
    echo ERROR: Build failed!
    exit /b 1
)

REM Step 3: Copy .pyd to package directory
echo [3/4] Preparing package...
set PYD_PATH=%BUILD_DIR%\bindings\PySide6\Release\PySide6FluentUI.pyd
if not exist "%PYD_PATH%" (
    echo ERROR: PySide6FluentUI.pyd not found at %PYD_PATH%
    exit /b 1
)
copy /Y "%PYD_PATH%" "%~dp0PySide6FluentUI\PySide6FluentUI.pyd"

REM Step 4: Build wheel
echo [4/4] Building wheel...
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
echo Install with: pip install dist\PySide6FluentUI-1.0.0-cp313-cp313-win_amd64.whl

REM Cleanup
rmdir /S /Q "%BUILD_DIR%" 2>nul

endlocal
