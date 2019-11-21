@ECHO OFF

::=============================================================================
::  cppnamelint.py check <srcdir> <config> [--includes=<dirs>] [--ignores=<paths>]
::  cppnamelint.py pack  <rootdir> <outputdir>
::  cppnamelint.py test  <srcdir> <config>
::  cppnamelint.py test-sample <sampledir>
::  cppnamelint.py (-h | --help)
::  cppnamelint.py (-v | --version)
::  cppnamelint.py --help     Show this screen.
::  cppnamelint.py --version  Show version.
::
::Options:
::    --log=<file>     [default: cppnamelint.log]
::=============================================================================


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
