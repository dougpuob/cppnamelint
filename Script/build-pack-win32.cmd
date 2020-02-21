@ECHO OFF

IF EXIST Release (RD Release)
python cppnamelint.py bldgpack .. .\Release

ECHO.
ECHO.

IF NOT "0"=="%ERRORLEVEL%"   (
ECHO  Failed to execute `bldgpack` command.
) ELSE (
ECHO  SUCCESS!
)

ECHO.
ECHO.

timeout /t 5
@ECHO ON
