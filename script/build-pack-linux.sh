#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin:/usr/local/Cellar:/anaconda3/bin:

mkdir release

proj_dir="../"
build_dir="??"
output_dir="??"

if   [[ "$OSTYPE" == "linux-gnu" ]]; then
  build_dir=../build/linux
  output_dir=./release/linux
  echo "INFO : Linux is detected."
elif [[ "$OSTYPE" == "darwin"* ]]; then
  build_dir=../build/macos
  output_dir=./release/macos
  echo "INFO : macOS is detected."
else
  echo "ERROR: missed OS detection !!"
fi

python3 cppnamelint.py bldgpack $proj_dir $build_dir $output_dir
