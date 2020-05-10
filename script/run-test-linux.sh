#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin:/usr/local/Cellar:/anaconda3/bin:

python3 testcppnamelintlib-exec.py   -v
python3 testcppnamelintlib-cmake.py  -v
python3 testcppnamelintlib-file.py   -v

if [ -f ./cppnamelint ]; then
    python3 testcppnamelint-main.py  -v
    python3 cppnamelint.py bldgtest
    cppnamelint test -testlog=testlog.log
fi
