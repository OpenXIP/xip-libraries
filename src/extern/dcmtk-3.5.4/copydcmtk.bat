@echo off
goto _PARCHECK

:_HELP
echo ---------------------------------------------------------------------------------------------
echo  This is a quick utility batch file to copy the dcmtk header files
echo  from the svn structure as the 1st argument, and the cmake libraries from
echo  the cmake output root location specified as the 2nd argument to the DCMTK_PATH
echo  environment location.  The environment variable DCMTK_PATH must be set a priori.
echo  e.g. CopyDcmTkLibs c:\xip\src\extern\dcmtk-3.5.4 C:\xip\xipext-build 
echo  -h  print out this help
echo ---------------------------------------------------------------------------------------------
goto _FINISH

:_PARCHECK
if "%1" EQU "-h" (goto _HELP)
goto _START

:_START
set DCM_SRC_PATH=%1
set DCM_BUILD_PATH=%2

mkdir %DCMTK_PATH%\include
mkdir %DCMTK_PATH%\lib
mkdir %DCMTK_PATH%\lib\debug
mkdir %DCMTK_PATH%\lib\release


rem ## include files ##
xcopy /S /F /I %DCM_SRC_PATH%\config\include\dcmtk\config\*.h %DCMTK_PATH%\include\dcmtk\config
xcopy /S /F /I %DCM_SRC_PATH%\dcmdata\include\dcmtk\dcmdata\*.h %DCMTK_PATH%\include\dcmtk\dcmdata
xcopy /S /F /I %DCM_SRC_PATH%\dcmimage\include\dcmtk\dcmimage\*.h %DCMTK_PATH%\include\dcmtk\dcmimage
xcopy /S /F /I %DCM_SRC_PATH%\dcmimgle\include\dcmtk\dcmimgle\*.h %DCMTK_PATH%\include\dcmtk\dcmimgle
xcopy /S /F /I %DCM_SRC_PATH%\dcmjpeg\include\dcmtk\dcmjpeg\*.h %DCMTK_PATH%\include\dcmtk\dcmjpeg
xcopy /S /F /I %DCM_SRC_PATH%\dcmpstat\include\dcmtk\dcmpstat\*.h %DCMTK_PATH%\include\dcmtk\dcmpstat
xcopy /S /F /I %DCM_SRC_PATH%\dcmsr\include\dcmtk\dcmsr\*.h %DCMTK_PATH%\include\dcmtk\dcmsr
xcopy /S /F /I %DCM_SRC_PATH%\ofstd\include\dcmtk\ofstd\*.h %DCMTK_PATH%\include\dcmtk\ofstd
xcopy /S /F /I %DCM_SRC_PATH%\dcmnet\include\dcmtk\dcmnet\*.h %DCMTK_PATH%\include\dcmtk\dcmnet

rem ## debug ##
copy %DCM_BUILD_PATH%\dcmdata\libsrc\debug\dcmdata.lib  %DCMTK_PATH%\lib\debug\dcmdata.lib
copy %DCM_BUILD_PATH%\dcmimage\libsrc\debug\dcmimage.lib  %DCMTK_PATH%\lib\debug\dcmimage.lib
copy %DCM_BUILD_PATH%\dcmimgle\libsrc\debug\dcmimgle.lib  %DCMTK_PATH%\lib\debug\dcmimgle.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libsrc\debug\dcmjpeg.lib  %DCMTK_PATH%\lib\debug\dcmjpeg.lib
copy %DCM_BUILD_PATH%\dcmpstat\libsrc\debug\dcmpstat.lib  %DCMTK_PATH%\lib\debug\dcmpstat.lib
copy %DCM_BUILD_PATH%\dcmsr\libsrc\debug\dcmsr.lib  %DCMTK_PATH%\lib\debug\dcmsr.lib
copy %DCM_BUILD_PATH%\ofstd\libsrc\debug\ofstd.lib  %DCMTK_PATH%\lib\debug\ofstd.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libijg8\debug\ijg8.lib  %DCMTK_PATH%\lib\debug\ijg8.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libijg12\debug\ijg12.lib  %DCMTK_PATH%\lib\debug\ijg12.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libijg16\debug\ijg16.lib  %DCMTK_PATH%\lib\debug\ijg16.lib
copy %DCM_BUILD_PATH%\dcmnet\libsrc\debug\dcmnet.lib  %DCMTK_PATH%\lib\debug\dcmnet.lib



rem ## release ##
copy %DCM_BUILD_PATH%\dcmdata\libsrc\release\dcmdata.lib  %DCMTK_PATH%\lib\release\dcmdata.lib
copy %DCM_BUILD_PATH%\dcmimage\libsrc\release\dcmimage.lib  %DCMTK_PATH%\lib\release\dcmimage.lib
copy %DCM_BUILD_PATH%\dcmimgle\libsrc\release\dcmimgle.lib  %DCMTK_PATH%\lib\release\dcmimgle.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libsrc\release\dcmjpeg.lib  %DCMTK_PATH%\lib\release\dcmjpeg.lib
copy %DCM_BUILD_PATH%\dcmpstat\libsrc\release\dcmpstat.lib  %DCMTK_PATH%\lib\release\dcmpstat.lib
copy %DCM_BUILD_PATH%\dcmsr\libsrc\release\dcmsr.lib  %DCMTK_PATH%\lib\release\dcmsr.lib
copy %DCM_BUILD_PATH%\ofstd\libsrc\release\ofstd.lib  %DCMTK_PATH%\lib\release\ofstd.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libijg8\release\ijg8.lib  %DCMTK_PATH%\lib\release\ijg8.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libijg12\release\ijg12.lib  %DCMTK_PATH%\lib\release\ijg12.lib
copy %DCM_BUILD_PATH%\dcmjpeg\libijg16\release\ijg16.lib  %DCMTK_PATH%\lib\release\ijg16.lib
copy %DCM_BUILD_PATH%\dcmnet\libsrc\release\dcmdata.lib  %DCMTK_PATH%\lib\release\dcmnet.lib


:_FINISH
@goto :EOF