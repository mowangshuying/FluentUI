@REM switch to the repository root regardless of where the script is invoked
cd /d "%~dp0.."
C:\Qt\6.9.0\msvc2022_64\bin\lupdate.exe controls\  -ts i18n\Controls.en-US.ts i18n\Controls.zh-CN.ts
C:\Qt\6.9.0\msvc2022_64\bin\lupdate.exe gallery\  -ts i18n\Gallery.en-US.ts i18n\Gallery.zh-CN.ts