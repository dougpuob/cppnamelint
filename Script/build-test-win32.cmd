@ECHO OFF

python testcppnamelint.py           -v
python testcppnamelintlib-exec.py   -v
python testcppnamelintlib-cmake.py  -v
python testcppnamelintlib-file.py   -v

IF EXIST cppnamelint.exe (
python testcppnamelint-main.py      -v
cppnamelint.exe test --all
)

timeout /t 5
@ECHO ON
