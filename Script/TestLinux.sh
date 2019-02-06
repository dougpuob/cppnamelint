#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin


SAMPLEDIR=${PWD}/../Source/Test/Sample

NLAPP=
if [ -f ${PWD}/../Build/linux/Output/namelint ]; then
	NLAPP=${PWD}/../Build/linux/Output/namelint
fi

echo NLAPP=${NLAPP}

echo
echo
echo NLAPP=${NLAPP}               > namelint.log
echo SAMPLEDIR=${SAMPLEDIR}      >> namelint.log
echo

echo                                                                            >> namelint.log
${NLAPP} test -a
${NLAPP} test -a                                                                >> namelint.log
echo ERRORLEVEL=$?                                                              >> namelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

echo                                                                           	    >> namelint.log
${NLAPP} check ${SAMPLEDIR}/UpperCamel_1.c --config=${SAMPLEDIR}/UpperCamel_1.toml 	>> namelint.log
echo ERRORLEVEL=$?                                                              	>> namelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

echo                                                                           	>> namelint.log
${NLAPP} check ${SAMPLEDIR}/UpperCamel_2.c --config=${SAMPLEDIR}/UpperCamel_2.toml	>> namelint.log
echo ERRORLEVEL=$?                                                              	>> namelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

echo                                                                           	>> namelint.log
${NLAPP} check ${SAMPLEDIR}/UpperCamel_3.c --config=${SAMPLEDIR}/UpperCamel_3.toml 	>> namelint.log
echo ERRORLEVEL=$?                                                              	>> namelint.log
if [ "0" != "$?" ]; then
	echo *ERROR*
fi

