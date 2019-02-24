#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin


SAMPLEDIR=${PWD}/../Source/Test/Sample

NLAPP=
if [ -f ${PWD}/../Build/linux/Output/cppnamelint ]; then
	NLAPP=${PWD}/../Build/linux/Output/cppnamelint
fi

echo NLAPP=${NLAPP}

echo
echo
echo NLAPP=${NLAPP}               > cppnamelint.log
echo SAMPLEDIR=${SAMPLEDIR}      >> cppnamelint.log
echo

echo                                                                            >> cppnamelint.log
${NLAPP} test -a
${NLAPP} test -a                                                                >> cppnamelint.log
echo ERRORLEVEL=$?                                                              >> cppnamelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

echo                                                                           	>> cppnamelint.log
${NLAPP} check ${SAMPLEDIR}/Sample_01.c --config=${SAMPLEDIR}/Sample_01.toml 	>> cppnamelint.log
echo ERRORLEVEL=$?                                                              >> cppnamelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

echo                                                                           	>> cppnamelint.log
${NLAPP} check ${SAMPLEDIR}/Sample_02.c --config=${SAMPLEDIR}/Sample_02.toml	>> cppnamelint.log
echo ERRORLEVEL=$?                                                              >> cppnamelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

echo                                                                           	>> cppnamelint.log
${NLAPP} check ${SAMPLEDIR}/Sample_03.c --config=${SAMPLEDIR}/Sample_03.toml 	>> cppnamelint.log
echo ERRORLEVEL=$?                                                              >> cppnamelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

