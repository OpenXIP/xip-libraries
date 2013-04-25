#! /bin/sh

rm -f  ${MEVIS_THIRDPARTY_LIB}/Inventor/inventor/libFL/libFL*
rm -f  ${MEVIS_THIRDPARTY_LIB}/Inventor/inventor/libimage/libimage*
rm -rf ${MEVIS_THIRDPARTY_LIB}/lib/Inventor.framework

qmake -o Makefile.ppp ppp.pro
make -f Makefile.ppp distclean

qmake -o Makefile.FL FL.pro
make -f Makefile.FL distclean

qmake -o Makefile.image image.pro
make -f Makefile.image distclean

qmake -o Makefile.inventor inventor.pro
make -f Makefile.inventor distclean
