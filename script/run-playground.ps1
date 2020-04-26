cls
clang -Xclang -ast-dump .\test\YouPlayGround.cpp
.\cppnamelint.exe check .\test\YouPlayGround.cpp --config .\test\YouPlayGround.toml --logfile logfile.log