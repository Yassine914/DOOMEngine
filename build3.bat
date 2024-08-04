@echo off
SetLocal EnableDelayedExpansion

echo ----------------------------
echo build script for DOOM Engine
echo      by Yassin Shehab
echo ----------------------------
echo.

set cppFiles=

pushd src

pushd vendor

for /r %%f in (*.cpp) do (
    set filepath=%%~f

    set "cppFiles=!cppFiles! !filePath:~36!"
)

if defined cppFiles set cppFiles=!cppFiles:~1!
popd
popd

for %%i in (%cppFiles%) do (
    echo %%i
)

set compilerFlags=-g -Wvarargs -Wall -Werror
set includeFlags=-Iinclude -Ithirdparty/lib/
set linkerFlags=-Lthirdparty/lib/ -lglfw3 -lopengl32 -lgdi32 -municode


clang++ %cppFiles% -o bin/imgui.dll -shared %compilerFlags% %includeFlags% %linkerFlags%