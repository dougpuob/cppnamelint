@ECHO OFF

::python cppnamelint.py check ..\Source\Test\Sample\Sample_05.cpp ..\Source\Test\Sample\Sample_05.toml
::PAUSE 
::EXIT


IF EXIST ..\Source (
    python cppnamelint.py test ..\Source ..\Source\cppnamelint.toml
)

IF EXIST ..\Source\Test\Sample (
    python cppnamelint.py test-sample "..\Source\Test\Sample"
)

IF EXIST Test\Sample (
    python cppnamelint.py test-sample "Test\Sample"
)

PAUSE
@ECHO ON
