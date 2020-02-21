@ECHO OFF

IF EXIST release (RD release)
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

IF ""=="%AGENT_VERSION%" (timeout /t 5)
@ECHO ON
