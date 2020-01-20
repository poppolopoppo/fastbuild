@ECHO OFF
@REM This does not handle Visual Studio 2010 and Cuda

@REM Local settings : (you can edit these to match yours)
@SET VS110=%vs110comntools%..\..\
@SET VS134=%vs120comntools%..\..\
@SET VS150=%vs140comntools%..\..\
@SET WINDOWS_SDK=C:\Program Files (x86)\Windows Kits
@SET CLANG=C:\Program Files (x86)\LLVM

REM ***** %~dp0SDK
@SET EXTERNAL_SDK=%~dp0SDK

REM ***** Visual Studio
mklink /j "%EXTERNAL_SDK%\VisualStudio\2010" "%VS110%"
mklink /j "%EXTERNAL_SDK%\VisualStudio\2013" "%VS110%"
mklink /j "%EXTERNAL_SDK%\VisualStudio\2015" "%VS134%"
mklink /j "%EXTERNAL_SDK%\VisualStudio\2017" "C:\Program Files (x86)\Microsoft Visual Studio\2017"
mklink /j "%EXTERNAL_SDK%\VisualStudio\2019" "C:\Program Files (x86)\Microsoft Visual Studio\2019"

REM ***** Windows SDK
mklink /j "%EXTERNAL_SDK%\Windows\8.0" "%WINDOWS_SDK%\8.0"
mklink /j "%EXTERNAL_SDK%\Windows\8.1" "%WINDOWS_SDK%\8.1"
mklink /j "%EXTERNAL_SDK%\Windows\10"  "%WINDOWS_SDK%\10"

REM ***** CLANG/LLVM
mklink /j "%EXTERNAL_SDK%\ClangForWindows\3.4" "%CLANG%"
mklink /j "%EXTERNAL_SDK%\ClangForWindows\3.8" "%CLANG%"
