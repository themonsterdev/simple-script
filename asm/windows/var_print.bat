@echo off

REM Define the path to vcvarsall.bat (adjust this path to match your installation)
SET "VS_VCVARS_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"

REM Check if vcvarsall.bat exists
IF NOT EXIST "%VS_VCVARS_PATH%" (
    echo vcvarsall.bat not found at %VS_VCVARS_PATH%. Please check the path.
    cmd /k
    exit /b 1
)

REM Run vcvarsall.bat to set up the environment variables for Visual Studio tools
call "%VS_VCVARS_PATH%" x64

REM Check if the environment variables were set correctly
IF NOT DEFINED VCToolsInstallDir (
    echo Visual Studio environment variables not set correctly.
    cmd /k
    exit /b 1
)

REM Assemble the ASM file
nasm -f win64 var_print.asm -o var_print.obj
IF %ERRORLEVEL% NEQ 0 (
    echo NASM assembly failed.
    exit /b 1
)

REM Link the object file to create the executable
link /entry:start /subsystem:console var_print.obj kernel32.lib
IF %ERRORLEVEL% NEQ 0 (
    echo Linking failed.
    exit /b 1
)

echo Build successful! The executable is var_print.exe

REM Keep the command window open
exit /b 0
