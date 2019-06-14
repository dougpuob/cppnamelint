@ECHO OFF

IF EXIST ..\Source (
    python cppnamelint.py test ..\Source ..\Source\Config.toml
)

IF EXIST ..\Source\Test\Sample (
    python cppnamelint.py test-sample "..\Source\Test\Sample"
)

IF EXIST Sample (
    python cppnamelint.py test-sample "Sample"
)

PAUSE
@ECHO ON
