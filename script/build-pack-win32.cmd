@ECHO OFF

IF EXIST release (DIR /S /Q release/*)
python cppnamelint.py bldgpack .. .\release

ECHO.
ECHO.

IF NOT "0"=="%ERRORLEVEL%"   (
ECHO  Failed to execute `bldgpack` command.
) ELSE (
ECHO  SUCCESS!
)

ECHO.
ECHO.

IF ""=="%AGENT_VERSION%" (PAUSE)
@ECHO ON
