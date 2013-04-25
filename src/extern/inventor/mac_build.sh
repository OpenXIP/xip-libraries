#! /bin/csh

@ NUM_LOCAL_JOBS = `hwprefs cpu_count` * 2

setenv MAKE "make -j ${NUM_LOCAL_JOBS}"

echo "Using: ${MAKE}"

rm -f  ${MEVIS_THIRDPARTY_LIB}/Inventor/inventor/libFL/libFL*
rm -f  ${MEVIS_THIRDPARTY_LIB}/Inventor/inventor/libimage/libimage*
rm -rf ${MEVIS_THIRDPARTY_LIB}/lib/Inventor.framework

qmake -o Makefile.ppp ppp.pro
${MAKE} -f Makefile.ppp distclean
qmake -o Makefile.ppp ppp.pro
${MAKE} -f Makefile.ppp

./gensources.sh

foreach build (release debug)
setenv CONFIG "CONFIG+=$build"

qmake ${CONFIG} -o Makefile.FL FL.pro
${MAKE} -f Makefile.FL distclean
qmake ${CONFIG} -o Makefile.FL FL.pro
${MAKE} -f Makefile.FL

qmake ${CONFIG} -o Makefile.image image.pro
${MAKE} -f Makefile.image distclean
qmake ${CONFIG} -o Makefile.image image.pro
${MAKE} -f Makefile.image

qmake ${CONFIG} -o Makefile.inventor inventor.pro
${MAKE} -f Makefile.inventor clean
# qmake ${CONFIG} -o Makefile.inventor "CONFIG+=build_oiv_installer" inventor.pro
qmake ${CONFIG} -o Makefile.inventor inventor.pro
${MAKE} -f Makefile.inventor

end
