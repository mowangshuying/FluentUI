:: MIT License
:: Copyright (c) 2023 SineStriker

:: Description: This script calls `qmcorecmd` to deploy dependencies on Windows.

@echo off
setlocal enabledelayedexpansion

:: Initialize arguments
set "INPUT_DIR="
set "PLUGIN_DIR="
set "LIB_DIR="
set "QML_DIR="
set "QMAKE_PATH="
set "CORECMD_PATH="
set "VERBOSE="
set "FILES="
set "EXTRA_PLUGIN_PATHS="
set "PLUGINS=" & set /a "PLUGIN_COUNT=0"
set "QML_REL_PATHS="
set "ARGS="

:: Parse command line
:parse_args
if "%~1"=="" goto :end_parse_args
if "%1"=="-i" set "INPUT_DIR=%~2" & shift & shift & goto :parse_args
if "%1"=="-m" set "CORECMD_PATH=%~2" & shift & shift & goto :parse_args
if "%1"=="--plugindir" set "PLUGIN_DIR=%~2" & shift & shift & goto :parse_args
if "%1"=="--libdir" set "LIB_DIR=%~2" & shift & shift & goto :parse_args
if "%1"=="--qmldir" set "QML_DIR=%~2" & shift & shift & goto :parse_args
if "%1"=="--qmake" set "QMAKE_PATH=%~2" & shift & shift & goto :parse_args
if "%1"=="--extra" set "EXTRA_PLUGIN_PATHS=!EXTRA_PLUGIN_PATHS! %~2" & shift & shift & goto :parse_args
if "%1"=="--plugin" set /a "PLUGIN_COUNT+=1" & set "PLUGINS[!PLUGIN_COUNT!]=%~2" & shift & shift & goto :parse_args
if "%1"=="--qml" set "QML_REL_PATHS=!QML_REL_PATHS! %~2" & shift & shift & goto :parse_args
if "%1"=="--copy" set "ARGS=!ARGS! -c %~2 %~3" & shift & shift & shift & goto :parse_args
if "%1"=="-f" set "ARGS=!ARGS! -f" & shift & goto :parse_args
if "%1"=="-s" set "ARGS=!ARGS! -s" & shift & goto :parse_args
if "%1"=="-V" set "VERBOSE=-V" & shift & goto :parse_args
if "%1"=="-h" call :usage & exit /b

if "%1"=="-@" set "ARGS=!ARGS! -@ %~2" & shift & shift & goto :parse_args
if "%1"=="-L" set "ARGS=!ARGS! -L %~2" & shift & shift & goto :parse_args

shift
goto :parse_args
:end_parse_args

:: Check required arguments
if not defined INPUT_DIR echo Error: Missing required argument 'INPUT_DIR' & call :usage & exit /b
if not defined PLUGIN_DIR echo Error: Missing required argument 'PLUGIN_DIR' & call :usage & exit /b
if not defined LIB_DIR echo Error: Missing required argument 'LIB_DIR' & call :usage & exit /b
if not defined QML_DIR echo Error: Missing required argument 'QML_DIR' & call :usage & exit /b
if not defined CORECMD_PATH echo Error: Missing required argument 'CORECMD_PATH' & call :usage & exit /b

:: Normalize
set "INPUT_DIR=!INPUT_DIR:/=\!"
set "PLUGIN_DIR=!PLUGIN_DIR:/=\!"
set "LIB_DIR=!LIB_DIR:/=\!"
set "QML_DIR=!QML_DIR:/=\!"
set "CORECMD_PATH=!CORECMD_PATH:/=\!"

:: Get Qt plugin and QML paths
set "PLUGIN_PATHS="
set "QML_PATH="
if defined QMAKE_PATH (
    for /f "tokens=*" %%a in ('!QMAKE_PATH! -query QT_INSTALL_PLUGINS') do set "QMAKE_PLUGIN_PATH=%%a"
    set "PLUGIN_PATHS=!QMAKE_PLUGIN_PATH!"
    for /f "tokens=*" %%a in ('!QMAKE_PATH! -query QT_INSTALL_QML') do set "QML_PATH=%%a"
    set "QML_PATH=!QML_PATH:/=\!"

    :: Add Qt bin directory
    for /f "tokens=*" %%a in ('!QMAKE_PATH! -query QT_INSTALL_BINS') do set "QT_BIN_PATH=%%a"
    set "ARGS=!ARGS! -L !QT_BIN_PATH!"
)

:: Add extra plugin searching paths
set "PLUGIN_PATHS=!PLUGIN_PATHS! !EXTRA_PLUGIN_PATHS!"

:: Ensure that the QML search path is not empty 
:: when the QML related path is specified (qmake needs to be specified)
if not "%QML_REL_PATHS%"=="" (
    if "%QML_PATH%"=="" (
        echo Error: qmake path must be specified when QML paths are provided
        exit /b
    )
)

:: The type of file to be searched depends on the operating system
:: On Windows, search for.exe and.dll files
for /r "%INPUT_DIR%" %%f in (*.exe *.dll) do (
    set "FILES=!FILES! %%f"
)

:: Find the full path to the Qt plugin
for /L %%i in (1,1,%PLUGIN_COUNT%) do (
    set "plugin_path=!PLUGINS[%%i]!"

    :: Check format
    echo !plugin_path! | findstr /R "[^/]*\/[^/]*" >nul
    if errorlevel 1 (
        echo Error: Invalid plugin format '!plugin_path!'. Expected format: ^<category^>/^<name^>
        exit /b
    )

    :: Extracts the category and name
    for /f "tokens=1,2 delims=/" %%a in ("!plugin_path!") do (
        set "category=%%a"
        set "name=%%b"

        :: Calculate destination directory
        set "DESTINATION_DIR=!PLUGIN_DIR!\!category!"
        set "DESTINATION_DIR=!DESTINATION_DIR:/=\!"

        :: Traverse the path and find the specific plug-in file
        set "FOUND_PLUGINS="
        call :search_plugin
        if not defined FOUND_PLUGINS (
            echo Error: Plugin '!plugin_path!' not found in any search paths.
            exit /b
        )
    )
)

:: Process QML directories
for %%q in (%QML_REL_PATHS%) do (
    call :search_qml_dir "%%q"
)

:: Build and execute the deploy command
set "DEPLOY_CMD=!CORECMD_PATH! deploy !FILES! !ARGS! -o !LIB_DIR! !VERBOSE!"
if "!VERBOSE!"=="-V" echo Executing: !DEPLOY_CMD!
call !DEPLOY_CMD!

:: Check the deployment result
if %errorlevel% neq 0 exit /b
exit /b




:: ----------------------------------------------------------------------------------
:: Search plugins
:search_plugin
for %%d in (!PLUGIN_PATHS!) do (
    for %%f in ("%%d\!category!\!name!.dll") do (
        if exist "%%f" (
            call :check_debug "%%f"
            if "!ok!"=="0" (
                call :add_plugin "%%f"
            )
        )
    )
)
exit /b
:: ----------------------------------------------------------------------------------





:: ----------------------------------------------------------------------------------
:: Add plugin if not already found
:add_plugin
set "plugin=%~1"
set "plugin_name=%~nx1"
for %%i in (!FOUND_PLUGINS!) do (
    if "%%i"=="!plugin_name!" (
        exit /b
    )
)
set "FOUND_PLUGINS=!FOUND_PLUGINS! !plugin_name!"
set "ARGS=!ARGS! -c !plugin! !DESTINATION_DIR!"
exit /b
:: ----------------------------------------------------------------------------------





:: ----------------------------------------------------------------------------------
:: Search QML directory
:search_qml_dir
set "full_path=%QML_PATH%\%~1"
if exist "%full_path%\" (
    :: Directory
    for /r "%full_path%" %%f in (*) do (
        call :handle_qml_file "%%f"
    )
) else if exist "%full_path%" (
    :: File
    call :handle_qml_file "%full_path%"
)
exit /b
:: ----------------------------------------------------------------------------------





:: ----------------------------------------------------------------------------------
:: Check debug version of a dll
:check_debug
set "ok=1"
set "file_path=%~1"
if "!file_path:~-4!"==".pdb" exit /b
if "!file_path:~-10!"==".dll.debug" exit /b
if "!file_path:~-5!" == "d.dll" (
    set "prefix=!file_path:~0,-5!"
    if exist "!prefix!.dll" (
        exit /b
    )
)
set "ok=0"
exit /b
:: ----------------------------------------------------------------------------------





:: ----------------------------------------------------------------------------------
:: Copy or add to a deployment command
:handle_qml_file
set "file=%~1"
set "file=!file:/=\!"

:: Ignore specific files (example)
call :check_debug "%file%"
if "!ok!"=="1" (
    exit /b
)

:: Computes target file and folder in a very stupid way
set "rel_path=!file:%QML_PATH%\=!"
set "target=%QML_DIR%\%rel_path%"
for %%I in ("!file!") do (
    set "file_dir=%%~dpI"
)
set "rel_dir_path=!file_dir:%QML_PATH%\=!"
set "target_dir=%QML_DIR%\%rel_dir_path%"

:: Determine whether it is an executable binary file and handle it accordingly
if "%file:~-4%"==".dll" (
    set "ARGS=!ARGS! -c !file! !target_dir!"
) else if "%file:~-4%"==".exe" (
    set "ARGS=!ARGS! -c !file! !target_dir!"
) else (
    if not exist "%target%" (
        mkdir "%target_dir%" >nul 2>&1
    )
    copy /Y "%file%" "%target%" >nul 2>&1
)

exit /b
:: ----------------------------------------------------------------------------------





:: ----------------------------------------------------------------------------------
:: Show usage
:usage
echo Usage: %~n0 -i ^<dir^> -m ^<path^>
echo                --plugindir ^<plugin_dir^> --libdir ^<lib_dir^> --qmldir ^<qml_dir^>
echo               [--qmake ^<qmake_path^>] [--extra ^<extra_path^>]...
echo               [--qml ^<qml_module^>]... [--plugin ^<plugin^>]... [--copy ^<src^> ^<dest^>]...
echo               [-@ ^<file^>]... [-L ^<path^>]...
echo               [-f] [-s] [-V] [-h]
exit /b
:: ----------------------------------------------------------------------------------