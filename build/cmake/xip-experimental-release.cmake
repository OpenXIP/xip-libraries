# these are the the name of the source and binary directory on disk. 
SET(CTEST_SOURCE_NAME xip-experimental)
SET(CTEST_BINARY_NAME xip-experimental-release)
SET(CTEST_DASHBOARD_ROOT "C:/home/sylvain/dashboard")
SET(CTEST_SOURCE_DIRECTORY "${CTEST_DASHBOARD_ROOT}/${CTEST_SOURCE_NAME}")
SET(CTEST_BINARY_DIRECTORY "${CTEST_DASHBOARD_ROOT}/${CTEST_BINARY_NAME}")

SET(CTEST_CVS_COMMAND "C:/svn-win32-1.4.6/bin/svn.exe")
SET(CTEST_CVS_CHECKOUT  "${CTEST_CVS_COMMAND} checkout https://collab01a.scr.siemens.com/svn/xip/trunk xip-experimental")

# which ctest command to use for running the dashboard
SET(CTEST_COMMAND 
 "\"C:/Program Files/CMake 2.4/bin/ctest.exe\" -D Experimental -A ${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}"
  )

# should ctest wipe the binary tree before running
SET (CTEST_START_WITH_EMPTY_BINARY_DIRECTORY TRUE)

# what cmake command to use for configuring this dashboard
SET (CTEST_CMAKE_COMMAND 
  "\"C:/Program Files/CMake 2.4/bin/cmake.exe\""
  )

# set any extra envionment variables here
SET (CTEST_ENVIRONMENT
 "PATH=C:/WINDOWS/system32\;C:/home/sylvain/xipbuilder-cmd/bin\;C:/home/sylvain/xipext/vtk/bin\;${EXECUTABLE_OUTPUT_PATH}"
)

SET( $ENV{LC_MESSAGES}    "en_EN" )

SET (CTEST_INITIAL_CACHE "
CMAKE_GENERATOR:INTERNAL=Visual Studio 8 2005
CMAKE_MAKE_PROGRAM:FILEPATH=C:/Program Files/Microsoft Visual Studio 8/Common7/IDE/devenv.com
MAKECOMMAND:STRING=\"C:/Program Files/Microsoft Visual Studio 8/Common7/IDE/devenv.com\" Xip.sln /build Release /project ALL_BUILD
CMAKE_BUILD_TYPE:STRING=Release
SITE:STRING=sylvain.desktop
BUILDNAME:STRING=Win32-VS08-Release
SVNCOMMAND:FILEPATH=C:/svn-win32-1.4.6/bin/svn.exe
XIPEXT:PATH=C:/home/sylvain/xipext
XIPBUILDER:PATH=C:/home/sylvain/xipbuilder-cmd/bin/release
")


