To configure Xip with CMake, you first need to download CMake
from www.cmake.org. Then follow the instructions and adjust
C:/home/sylvain to your path.

Configuring Xip using CMake 
--------------------------- 
* Using CMake from the Start Menu:

Set source dir to C:/home/sylvain/xip
Set binary dir to C:/home/sylvain/xip-build
Click on Configure
Set the path to Xipext: C:/home/sylvain/xipext
Set the path to Xipbuilder:  C:/home/sylvain/xipbuilder/bin/release
!!! You need the new Xipbuilder (Jan 2008) that takes the parameter:
!!! /cmd=filename
Click on Configure and then OK
Open C:/home/sylvain/xip-build/Xip.sln
Build for Release
(optional) in cygwin, go to xip-build and type ctest -D ExperimentalSubmit -VV

* Using CMake on the command line

Assuming you have Xip in C:/home/sylvain/xip
Go one level above Xip dir: C:/home/sylvain
mkdir xip-build
cd xip-build
cmake ../xip -G "Visual Studio 8 2005" -DXIPEXT:PATH=C:/home/sylvain/xipext -DXIPBUILDER:PATH=C:/home/sylvain/xipbuilder/bin/release
!!! You need the new Xipbuilder (Jan 2007) that takes the parameter:
!!! /cmd=filename
(optional) in cygwin, go to xip-build and type ctest -D ExperimentalSubmit -VV


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
