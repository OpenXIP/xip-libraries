@echo off
if not exist "..\bin\RunIvJava.class" goto missing

copy .\ivJava.ini ..\bin\ivJava.ini

cd ..\bin
set classpath=%classpath%;.
java RunIvJava
@goto end


:missing
@echo ERROR: The class files required for execution are not found. Please run the build script first
@goto end

:end
cd ..