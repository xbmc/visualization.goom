@ECHO OFF

SETLOCAL

SET SCRIPT_PATH=%~dp0

IF "%~1" == "" (
  ECHO BUILD_TYPE must be specified.
  Exit /b 1
)
SET BUILD_TYPE=%1
SET BUILD_DIR=build-%BUILD_TYPE%

PUSHD %SCRIPT_PATH%
IF ErrorLevel 1 Exit /b 1

cmake --build %BUILD_DIR% --config %BUILD_TYPE%

cmake --install %BUILD_DIR%

POPD
