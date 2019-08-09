@ECHO OFF

IF EXIST Release (RD /S/Q Release)
python cppnamelint.py pack .. ./Release

@ECHO ON
