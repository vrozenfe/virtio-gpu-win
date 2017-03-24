@echo on

set SYS_FILE_NAME=viogpudo

if "%1_%2" neq "_" goto %1_%2
for %%A in (Win8 Win10) do for %%B in (32 64) do call :%%A_%%B
set SYS_FILE_NAME=
goto :eof 


:BuildProject
setlocal

set _MAJORVERSION_=%_BUILD_MAJOR_VERSION_%
set _MINORVERSION_=%_BUILD_MINOR_VERSION_%
set _NT_TARGET_MIN=%_RHEL_RELEASE_VERSION_%

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
call ..\..\tools\callVisualStudio.bat 14 viogpudo.vcxproj /Rebuild "%~1" /Out %2
endlocal
goto :eof

:BuildSDV
setlocal
set _NT_TARGET_VERSION=%3
if "%_BUILD_MAJOR_VERSION_%"=="" set _BUILD_MAJOR_VERSION_=101
if "%_BUILD_MINOR_VERSION_%"=="" set _BUILD_MINOR_VERSION_=58000
if "%_RHEL_RELEASE_VERSION_%"=="" set _RHEL_RELEASE_VERSION_=61

set _MAJORVERSION_=%_BUILD_MAJOR_VERSION_%
set _MINORVERSION_=%_BUILD_MINOR_VERSION_%
set /a _NT_TARGET_MAJ="(%_NT_TARGET_VERSION% >> 8) * 10 + (%_NT_TARGET_VERSION% & 255)"
set _NT_TARGET_MIN=%_RHEL_RELEASE_VERSION_%

set STAMPINF_VERSION=%_NT_TARGET_MAJ%.%_RHEL_RELEASE_VERSION_%.%_BUILD_MAJOR_VERSION_%.%_BUILD_MINOR_VERSION_% 
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" %2
msbuild.exe viogpudo.vcxproj /t:clean /p:Configuration="%~1" /P:Platform=%2 
msbuild.exe viogpudo.vcxproj /t:sdv /p:inputs="/clean" /p:Configuration="%~1" /P:platform=%2
msbuild.exe viogpudo.vcxproj /p:Configuration="%~1" /P:Platform=%2 /P:RunCodeAnalysisOnce=True
msbuild.exe viogpudo.vcxproj /t:sdv /p:inputs="/devenv /check" /p:Configuration="%~1" /P:platform=%2
msbuild.exe viogpudo.vcxproj /t:dvl /p:Configuration="%~1" /P:platform=%2
endlocal
goto :eof

:buildpack
setlocal
set BUILD_OS=%1
set BUILD_ARC=%2

if exist Install\%BUILD_OS%\%BUILD_ARC% rmdir Install\%BUILD_OS%\%BUILD_ARC% /s /q
call :BuildProject %3 %4
call packOne.bat %BUILD_OS% %BUILD_ARC% %SYS_FILE_NAME%

endlocal
goto :eof

:WIN8_32
call :buildpack Win8 x86 "Win8 Release|x86" buildfre_win8_x86.log
goto :eof

:WIN8_64
call :buildpack Win8 x64 "Win8 Release|x64" buildfre_win8_amd64.log
if "%_BUILD_DISABLE_SDV%"=="" goto :DO_SDV
goto :eof
:DO_SDV
call :BuildSDV "Win8 Release" x64
call packOne.bat Win8 x64 %SYS_FILE_NAME%
rmdir /S /Q .\sdv
goto :eof

:WIN10_32
call :buildpack Win10 x86 "Win10 Release|x86" buildfre_win10_x86.log
goto :eof

:WIN10_64
call :buildpack Win10 x64 "Win10 Release|x64" buildfre_win10_amd64.log
if "%_BUILD_DISABLE_SDV%"=="" goto :DO_SDV
goto :eof
:DO_SDV
call :BuildSDV "Win10 Release" x64
rmdir /S /Q .\sdv
goto :eof

:eof
