#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin:/usr/local/Cellar:/anaconda3/bin:

mkdir Release
python3 cppnamelint.py bldgpack .. ./Release