#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin:/usr/local/Cellar:/anaconda3/bin:

python3 testcppnamelint.py           -v
python3 testcppnamelintlib-exec.py   -v
python3 testcppnamelintlib-cmake.py  -v
python3 testcppnamelintlib-file.py   -v

if [ -f ./cppnamelint ]; then
    python3 testcppnamelint-main.py      -v
    cppnamelint test --all
fi

