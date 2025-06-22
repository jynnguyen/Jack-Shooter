@echo off
cd /d "%~dp0"
cls

REM ===== 1. Create or Reuse Build Folder =====
powershell -Command "Write-Host ' > Preparing build folder... ' -ForegroundColor Yellow"
if not exist build (
    mkdir build
)

cd build

REM ===== 2. CMake Configure =====
powershell -Command "Write-Host ' [CMAKE] Configuring project...' -ForegroundColor Blue"
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..

REM ===== 3. Build Project =====
powershell -Command "Write-Host ' [CMAKE] Building project...' -ForegroundColor Blue"
cmake --build .


powershell -Command "Write-Host ' >> Build completed.' -ForegroundColor Green"
echo.

cd ..
REM ===== 4. Copy .main.exe to .\dist =====
xcopy /E /I /Y "assets" "dist\assets"
copy /Y "build\.main.exe" "dist"


set /p answer=Do you want to run .main.exe? (y/n): 

if /i "%answer%"=="y" (
    powershell -Command "Write-Host ' > Running play.exe file' -ForegroundColor Yellow"
    start "" "dist\.main.exe"
) else (
    powershell -Command "Write-Host ' > Cancel running ' -ForegroundColor Red"
)

pause

