@ECHO OFF

python testcppnamelint.py           -v
python testcppnamelintlib-exec.py   -v
python testcppnamelintlib-cmake.py  -v
python testcppnamelintlib-file.py   -v

PAUSE
@ECHO ON
