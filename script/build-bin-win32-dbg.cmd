@ECHO OFF

python --version > NUL
IF "9009"=="%ERRORLEVEL%"   (GOTO :NOPY)

python cppnamelint.py chkenv
IF NOT "0"=="%ERRORLEVEL%"   (GOTO :NOTOOL)


ECHO.
ECHO ==============================================================
ECHO Generate makefile via CMake
ECHO ==============================================================
SET ROOT_DIR=..
SET BUILD_DIR=..\build\windows
SET SOURCE_DIR=..\source
SET BUILD_TYPE=DEBUG
python cppnamelint.py format  %ROOT_DIR% %SOURCE_DIR%
MKDIR %BUILD_DIR%
python cppnamelint.py bldgcfg %ROOT_DIR% %BUILD_DIR% %BUILD_TYPE%
IF NOT "0"=="%ERRORLEVEL%"   (GOTO :PYERR)
GOTO :PASS

:NOPY
ECHO Please install python.
GOTO :EXIT 

:NOTOOL
ECHO.
GOTO :EXIT 

:PYERR
ECHO Command result is FAILED.
GOTO :EXIT 

:PASS
ECHO Command result is SUCCESSFUL.
GOTO :EXIT 

:EXIT
IF ""=="%AGENT_VERSION%" (PAUSE)
@ECHO ON

