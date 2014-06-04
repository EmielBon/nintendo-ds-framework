@echo off

IF (%1)==() GOTO error
dir /b /ad %1 >nul 2>nul && GOTO indentDir
IF NOT EXIST %1 GOTO error
goto indentFile

:indentDir
set searchdir=%1

IF (%2)==() GOTO assignDefaultSuffix
set filesuffix=%2

GOTO run

:assignDefaultSuffix
::echo !!!!DEFAULT SUFFIX!!!
set filesuffix=*

:run
FOR /F "tokens=*" %%G IN ('DIR /B /S %searchdir%\*.%filesuffix%') DO (
echo Indenting file "%%G"
"%ARPIGI%/tools/UniversalIndentGUI/indenters/astyle.exe" "%%G" --options="./call_Artistic_Style.astylerc"

)
GOTO ende

:indentFile
echo Indenting one file %1
"%ARPIGI%/tools/UniversalIndentGUI/indenters/astyle.exe" "%1" --options="./call_Artistic_Style.astylerc"


GOTO ende

:error
echo .
echo ERROR: As parameter given directory or file does not exist!
echo Syntax is: call_Artistic_Style.bat dirname filesuffix
echo Syntax is: call_Artistic_Style.bat filename
echo Example: call_Artistic_Style.bat temp cpp
echo .

:ende
