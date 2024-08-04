@echo off
SetLocal EnableDelayedExpansion

echo ----------------------------
echo build script for DOOM Engine
echo      by Yassin Shehab
echo ----------------------------
echo.

mkdir bin/ > nul
mkdir obj/ > nul

set assembly=DoomEngine

set defines=-D_DEBUG

set cppFiles=

pushd src

for /r %%f in (*.cpp) do (
    set filepath=%%~f

    set "cppFiles=!cppFiles! !filePath:~36!"
)

if defined cppFiles set cppFiles=!cppFiles:~1!

echo C++ files to compile =^>

for %%i in (%cppFiles%) do (
    rem trick to sleep for milliseconds
    ping 127.0.0.1 -n 1 -w 100 > nul
    echo %%i
)
echo ----------------------------
echo.

popd

set staticLibs=-lglad -lglfw3
set dynamicLibs=-limgui

echo compiling source code...

set compilerFlags=-g -Wvarargs -Wall -Werror
set includeFlags=-I./thirdparty/include/

clang++ -c %cppFiles%  %compilerFlags% %includeFlags% %defines%

@REM echo ----------------------------
echo.

echo linking...

set objFiles=

for /r %%f in (*.o) do (
    set filepath=%%~f
    
    set "filepath=!filepath!"
    set objFiles=!objFiles! !filepath:~36!
)

set linkerFlags=-Lbin/ 
set linkingLibs=-lopengl32 -luser32 -lgdi32

clang++ %objFiles% -o ./bin/%assembly%.exe %linkerFlags% %staticLibs% %dynamicLibs%


exit
@REM for /r %%f in (*.o) do (
    @REM set filepath=%%~f
    @REM set filename=!filepath:~36!
    @REM echo !filepath! !filename!
    @REM move !filepath! %cwd%/obj/!filename!
@REM )

@REM echo building %assembly% complete...

@REM exit