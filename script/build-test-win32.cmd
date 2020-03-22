@ECHO OFF

python testcppnamelintlib-exec.py   -v
python testcppnamelintlib-cmake.py  -v
python testcppnamelintlib-file.py   -v

IF EXIST cppnamelint.exe (
python testcppnamelint-main.py      -v
python cppnamelint.py bldgtest
cppnamelint.exe test -all
)

IF ""=="%AGENT_VERSION%" (PAUSE)
@ECHO ON
