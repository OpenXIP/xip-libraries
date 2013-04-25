@echo off
@if "%VSINSTALLDIR%"=="" goto error_no_VCINSTALLDIR
@if "%JSDK_PATH%"=="" goto error_no_JSDK_PATH
@if "%SGIOIV%"=="" goto error_no_SGIOIV


set classpath=%classpath%;.\bin\classes;.


javac -d .\bin\classes .\src\Java\ivCanvas.java
javac -d .\bin\classes .\src\Java\Mainapplet.java


cl  -I"%SGIOIV%\include" -I"%SGIOIV%\include\inventor" -I"%JSDK_PATH%\include" -I"%JSDK_PATH%\include\win32" -I"%VCINSTALLDIR%\VC\Include"  -LD  .\src\cpp\ivCanvas.cpp -Fe".\bin\classes\ivCanvas.dll"  -link"%SGIOIV%\lib\xipinv240.lib" "%VCINSTALLDIR%\PlatformSDK\Lib\Opengl32.lib" "%JSDK_PATH%\lib\jawt.lib" "%VCINSTALLDIR%\PlatformSDK\Lib\User32.Lib"  "%VCINSTALLDIR%\PlatformSDK\Lib\Gdi32.Lib"

cd .\bin\classes

jar -cvf ivCanvas.jar *.*
copy ivCanvas.jar ..\ivCanvas.jar

cd ..\..

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

:error_no_SGIOIV
@echo ERROR: SGIOIV not set.
@echo ERROR: It must point to directory where Inventor is installed.
@goto end

:end
