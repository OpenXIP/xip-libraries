PROJECT(ivCanvas)

SET(LIBRARY_OUTPUT_PATH ${ivCanvas_SOURCE_DIR}/bin/)

INCLUDE_DIRECTORIES(
	$ENV{SGIOIV}/include
	$ENV{SGIOIV}/include/inventor
	$ENV{JSDK_PATH}/include
	$ENV{JSDK_PATH}/include/win32
	$ENV{VCINSTALLDIR}/VC/Include)

LINK_DIRECTORIES(
	$ENV{SGIOIV}/lib
	$ENV{VCINSTALLDIR}/PlatformSDK/Lib
	$ENV{JSDK_PATH}/lib)

#	C:\Program Files\Java\jdk1.6.0_04\bin
#C:\Program Files\Java\jre1.6.0_04\bin
#C:\Program Files\Java\jre1.6.0_04\bin\server
#C:\Program Files\Java\jre1.6.0_04\bin\client)

#C:\Program Files\Microsoft Visual Studio 8\Common7\IDE
#C:\Program Files\Microsoft Visual Studio 8\VC\BIN
#C:\Program Files\Microsoft Visual Studio 8\Common7\Tools
#C:\Program Files\Microsoft Visual Studio 8\Common7\Tools\bin
#C:\Program Files\Microsoft Visual Studio 8\VC\PlatformSDK\bin
#C:\Program Files\Microsoft Visual Studio 8\SDK\v2.0\bin
#C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727
#C:\Program Files\Microsoft Visual Studio 8\VC\VCPackages
#C:\Program Files\CMake 2.4\bin;
#C:\home\sylvain\xipext\vtk\bin
#C:\Perl\site\bin
#C:\Perl\bin
#C:\Program Files\CatPC\Bin
#C:\Program Files\CatPC\Windows\System32
#C:\WINDOWS\system32
#C:\WINDOWS
#C:\WINDOWS\System32\Wbem
#c:\Program Files\Microsoft SQL Server\90\Tools\binn\
#C:\atria\ClearCase\bin;C:\atria\common
#C:\Program Files\doxygen\bin
#"C:\Program Files\Graphviz2.16\Bin"
#C:\Program Files\CruiseControl
#C:\svn-win32-1.4.6\bin
#C:\CUDA\bin

#C:\home\sylvain\xip-release\out\release
#C:\Program Files\Microsoft Visual Studio 8\VC\redist\x86\Microsoft.VC80.CRT
#C:\home\sylvain\3dviewer_demo\bin
#C:\home\sylvain\xipext\inventor\bin
#C:\WINDOWS\system32\WindowsPowerShell\v1.0
#C:\Program Files\ParaView 3.2.1\bin


ADD_LIBRARY(ivCanvas SHARED src/cpp/ivCanvas.cpp)

TARGET_LINK_LIBRARIES(ivCanvas
	xipinv240.lib
	Opengl32.lib
	jawt.lib
	User32.Lib
	Gdi32.Lib)

#ADD_CUSTOM_TARGET(ivCanvas.java
#	$ENV{JSDK_PATH}/bin/javac -d ${LIBRARY_OUTPUT_PATH} ${ivCanvas_SOURCE_DIR}/src/java/ivCanvas.java)
#ADD_CUSTOM_TARGET(Mainapplet.java
#	$ENV{JSDK_PATH}/bin/javac -d ${LIBRARY_OUTPUT_PATH} ${ivCanvas_SOURCE_DIR}/src/java/Mainapplet.java)

#ADD_DEPENDENCIES(ivCanvas ivCanvas.java)
#ADD_DEPENDENCIES(ivCanvas Mainapplet.java)
