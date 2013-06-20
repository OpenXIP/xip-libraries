To configure Xip with CMake, you first need to download CMake
from www.cmake.org. Then follow the instructions and adjust
C:/XIP to your local path.

Prerequisites
--------------------------- 
*Tested in Windows, 32-bit compiler

CMake 2.8.11 
	Download - http://www.cmake.org/files/v2.8/cmake-2.8.11.1-win32-x86.exe
	
Visual Studio 9 2008

InsightToolkit-3.8.0.zip
	Download - http://sourceforge.net/projects/itk/files/itk/3.8/
	Configure in CMake
		Exceptions to default CMake options
			uncheck ITK_USE_CONCEPT_CHECKING
				*see http://www.itk.org/pipermail/insight-developers/2007-September/009606.html for details
	Build in Visual Studio 9
	
vtk-5.2.1.zip
	Download - http://www.vtk.org/files/release/5.2/vtk-5.2.1.zip
	Configure in CMake
		Exceptions to default CMake options
			check VTK_USE_PARALLEL
	Build in Visual Studio 9
		
glew 1.9.0 bin
	Unzip
	Note location of "include" directory and "lib/glew32.lib"

Configuring Xip using CMake 
--------------------------- 
* Using CMake from the Start Menu:

Set source dir to C:/XIP/xip-libraries
Set binary dir to C:/XIP/xip-libraries-build
Click on Configure
Set GLEW_INCLUDE_DIR to C:/XIP/glew-1.9.0/include
Set GLEW_LIBRARIES to C:/XIP/glew-1.9.0/lib/glew32.lib
Uncheck  BUILD_TESTING
Click on Configure
(optional) Set the path to Xipext: C:/XIP/xipext
(optional) Set the path to Xipbuilder:  C:/XIP/xipbuilder/bin/release
!!! You need the new Xipbuilder (Jan 2008) that takes the parameter:
!!! /cmd=filename
Click on Configure and then OK
Click on Generate
Open C:/XIP/xip-libraries-build/Xip.sln
Build for Release
(optional) in cygwin, go to xip-libraries-build and type ctest -D ExperimentalSubmit -VV

* Using CMake on the command line

Assuming you have Xip in C:/XIP/xip
Go one level above Xip dir: C:/XIP
mkdir xip-libraries-build
cd xip-libraries-build
cmake ../xip-libraries -G "Visual Studio 9 2008" -DXIPEXT:PATH=C:/XIP/xipext -DXIPBUILDER:PATH=C:/XIP/xipbuilder/bin/release
(optional) in cygwin, go to xip-libraries-build and type ctest -D ExperimentalSubmit -VV

To compile on Mac and Linux, you need to build Open Inventor.
Inventor has dependencies on third party libraries.
You need to install the following tools in order to build Open Inventor:

    * libjpeg  -- http://www.ijg.org/
    * freetype -- http://www.freetype.org/
    * iconv    -- http://www.gnu.org/software/libiconv/ 


Submitting to the dashboard
---------------------------
Edit the dashboard scripts:
xip/build/cmake/xip-continuous-release.cmake
and run the batch file xip/build/cmake/xip-dashboard.bat
Finally set the batch file as a Scheduled Task to run every night:
http://www.cmake.org/Wiki/CMake_Scripting_Of_CTest


Adding a new .cpp file
----------------------
If you add a new file to Xip, edit the CMakeLists.txt in that directory
and add the name of the cpp file to the bottom of the list in
ADD_LIBRARY(... myNewFile.cpp)

Inventor in src/extern
----------------------
To compile Inventor in src/extern, you first need to install jpeg.
For Windows, you can download the jpeg library from this website:
 http://gnuwin32.sourceforge.net/packages/jpeg.htm
