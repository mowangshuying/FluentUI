@REM switch to the repository root regardless of where the script is invoked
cd /d "%~dp0.."
git push origin --tags
pause
