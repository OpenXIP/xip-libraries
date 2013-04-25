@echo off
@if "%VSINSTALLDIR%"=="" goto error_no_VCINSTALLDIR
@if "%JSDK_PATH%"=="" goto error_no_JSDK_PATH
@if "%OIV_PATH%"=="" goto error_no_OIV

if not exist "..\bin" mkdir ..\bin


set classpath=%classpath%;..\bin;.


javac -d ..\bin ..\ivCanvas.java
javac -d ..\bin ..\MainFrame.java
javac -d ..\bin ..\RunIvJava.java

cl  -I"%OIV_PATH%\include" -I"%OIV_PATH%\include\inventor" -I"%JSDK_PATH%\include" -I"%JSDK_PATH%\include\win32" -I"%VCINSTALLDIR%\VC\Include"  -LD  ..\canvas\ivCanvas.cpp -Fe"..\bin\ivCanvas.dll" -Fo"..\bin\ivCanvas.obj"  -link"%OIV_PATH%\lib\xipinv240.lib" "%VCINSTALLDIR%\PlatformSDK\Lib\Opengl32.lib" "%JSDK_PATH%\lib\jawt.lib" "%VCINSTALLDIR%\PlatformSDK\Lib\User32.Lib"  "%VCINSTALLDIR%\PlatformSDK\Lib\Gdi32.Lib"
@goto end


:error_no_VCINSTALLDIR
@echo ERROR: VCINSTALLDIR variable is not set.
@echo It must point to Visual Studio Installation\VC.
@echo Either set it manually or run the batch script from a Visual Studio Command Prompt or execute vsvars32.bat prior to running this script.
@goto end 

:error_no_JSDK_PATH
@echo ERROR: JSDK_PATH not set.
@echo ERROR: It must point to java\jdk\
@goto end 

:error_no_OIV
@echo ERROR: OIV_PATH not set.
@echo ERROR: It must point to directory where Inventor is installed.
@goto end

:end