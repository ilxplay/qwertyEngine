@ECHO OFF
REM Build Everything

ECHO "Building everything..."

PUSHD engine
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (
    echo Error:%ERRORLEVEL%
    goto end
)

PUSHD testbed
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (
    echo Error:%ERRORLEVEL%
    goto end
)

ECHO "All assemblies built successfully."

:end
pause