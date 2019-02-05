@ECHO OFF

SET SAMPLEDIR=%~dp0..\Source\Test\Sample

SET NLAPP=
IF EXIST      %~dp0..\Build\win32\Output\Release\namelint.exe (
    SET NLAPP=%~dp0..\Build\win32\Output\Release\namelint.exe
)

IF EXIST      %~dp0..\Build\win32\Output\Debug\namelint.exe (
    SET NLAPP=%~dp0..\Build\win32\Output\Debug\namelint.exe
)

ECHO.
ECHO.
ECHO NLAPP=%NLAPP%               > namelint.log
ECHO SAMPLEDIR=%SAMPLEDIR%      >> namelint.log
ECHO.

ECHO.                                                                           >> namelint.log
%NLAPP% test -a
%NLAPP% test -a                                                                 >> namelint.log
ECHO ERRORLEVEL=%ERRORLEVEL%                                                    >> namelint.log
IF NOT "0"=="%ERRORLEVEL%" (GOTO :ERROR)

ECHO.                                                                           >> namelint.log
%NLAPP% check %SAMPLEDIR%\UpperCamel_1.c --config=%SAMPLEDIR%\UpperCamel_1.toml >> namelint.log
ECHO ERRORLEVEL=%ERRORLEVEL%                                                    >> namelint.log
IF NOT "0"=="%ERRORLEVEL%" (GOTO :ERROR)

ECHO.                                                                           >> namelint.log
%NLAPP% check %SAMPLEDIR%\UpperCamel_2.c --config=%SAMPLEDIR%\UpperCamel_2.toml >> namelint.log
ECHO ERRORLEVEL=%ERRORLEVEL%                                                    >> namelint.log
IF NOT "0"=="%ERRORLEVEL%" (GOTO :ERROR)

ECHO.                                                                           >> namelint.log
%NLAPP% check %SAMPLEDIR%\UpperCamel_3.c --config=%SAMPLEDIR%\UpperCamel_3.toml >> namelint.log
ECHO ERRORLEVEL=%ERRORLEVEL%                                                    >> namelint.log
IF NOT "0"=="%ERRORLEVEL%" (GOTO :ERROR)


GOTO :EXIT

:ERROR
ECHO ERROR
PAUSE

:EXIT
ECHO.
ECHO PASSED

ECHO.       >> namelint.log
ECHO PASSED >> namelint.log

@ECHO ON
