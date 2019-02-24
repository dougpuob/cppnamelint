@ECHO OFF

SET SAMPLEDIR=%~dp0..\Source\Test\Sample

SET NLAPP=
IF EXIST      %~dp0..\Build\win32\Output\Debug\cppnamelint.exe (
    SET NLAPP=%~dp0..\Build\win32\Output\Debug\cppnamelint.exe
)

IF EXIST      %~dp0..\Build\win32\Output\Release\cppnamelint.exe (
    SET NLAPP=%~dp0..\Build\win32\Output\Release\cppnamelint.exe
)

ECHO.
ECHO.
ECHO NLAPP=%NLAPP%               > cppnamelint.log
ECHO SAMPLEDIR=%SAMPLEDIR%      >> cppnamelint.log
ECHO.

ECHO.                           >> cppnamelint.log
%NLAPP% test -a
%NLAPP% test -a                 >> cppnamelint.log
ECHO ERRORLEVEL=%ERRORLEVEL%    >> cppnamelint.log
IF NOT "0"=="%ERRORLEVEL%" (GOTO :ERROR)

CALL :RUNTEST %SAMPLEDIR%\Sample_01.c   %SAMPLEDIR%\Sample_01.toml
CALL :RUNTEST %SAMPLEDIR%\Sample_02.c   %SAMPLEDIR%\Sample_02.toml
CALL :RUNTEST %SAMPLEDIR%\Sample_03.c   %SAMPLEDIR%\Sample_03.toml
CALL :RUNTEST ..\Source\Config.cpp      ..\Source\Config.toml
CALL :RUNTEST ..\Source\Common.cpp      ..\Source\Config.toml
CALL :RUNTEST ..\Source\Detection.cpp   ..\Source\Config.toml
CALL :RUNTEST ..\Source\ParseAST.cpp    ..\Source\Config.toml
CALL :RUNTEST ..\Source\Main.cpp        ..\Source\Config.toml

GOTO :EXIT

:RUNTEST
SET SRCFILE=%1
SET CFGFILE=%2
ECHO %SRCFILE%
ECHO.                                       >> cppnamelint.log
%NLAPP% check %SRCFILE% --config=%CFGFILE%  >> cppnamelint.log
ECHO ERRORLEVEL=%ERRORLEVEL%                >> cppnamelint.log
IF NOT "0"=="%ERRORLEVEL%" (GOTO :ERROR)
GOTO :EOF

:ERROR
ECHO ERRORLEVEL=%ERRORLEVEL%
PAUSE
GOTO :EOF

:EXIT
ECHO.
ECHO PASSED

ECHO.       >> cppnamelint.log
ECHO PASSED >> cppnamelint.log

:END

@ECHO ON
