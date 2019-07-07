#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin:/usr/local/Cellar:/anaconda3/bin:


if [ -d ../Source ]; then
    python3 cppnamelint.py test  ../Source  ../Source/Config.toml
fi

if [ -d ../Source/Test/Sample ]; then
    python3 cppnamelint.py test-sample "../Source/Test/Sample"
fi

if [ -d ./Test/Sample ]; then
    python3 cppnamelint.py test-sample "./Test/Sample"
fi
