REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files.
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=engine
SET compilerFlags=-g -m64 -shared -Wvarargs -Wall -Werror
SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
SET linkerFlags=-L%VULKAN_SDK%/Lib -luser32 -lvulkan-1
SET defines=-D_DEBUG -DKEXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly% (64-bit DLL)..."
clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%

IF %ERRORLEVEL% NEQ 0 (
    ECHO "Build failed with error code %ERRORLEVEL%!"
    exit /b %ERRORLEVEL%
)

ECHO "%assembly% built successfully."