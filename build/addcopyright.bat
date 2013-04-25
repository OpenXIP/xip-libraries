@echo off
if not exist "%0.txt" goto :missing
if "%1" == "" goto :end
if not exist "%1" goto :end
find " *  COPYRIGHT NOTICE." "%1" > nul
IF NOT ERRORLEVEL 1 goto :end

move "%1" "%TEMP%\addcopyright.tmp" > nul
copy /b "%0.txt" + "%TEMP%\addcopyright.tmp" "%1" > nul
del "%TEMP%\addcopyright.tmp" > nul
echo %1
goto :end

:missing
echo Missing copyright notice!


:end
