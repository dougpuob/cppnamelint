cls
clang -Xclang -ast-dump .\test\sample\YouPlayGround.cpp
.\cppnamelint.exe check .\test\sample\YouPlayGround.cpp --config .\test\sample\YouPlayGround.toml --logfile logfile.log