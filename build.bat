@echo off
rem build script for DOOM Engine

SetLocal EnableDelayedExpansion

set cppFiles=

pushd src
for /r %%x in (*.cpp) do (
    set filePath=%%~x
    set cppFiles=!cppFiles! !filePath:~2!
)

if defined cppFiles set cppFiles=!cppFiles:~1!
popd

rem dependencies needing compilation
set thirdparty=./thirdparty/glad.c ./thirdparty/stb_image.cpp

set assembly=doomEngine

set compiler flags=-g -Wvarargs -Wall -Werror
set includeFlags=-I./include/ -I./thirdparty/include/
set linkerFlags=-L./thirdparty/lib/ -lglfw3 -lopengl32 -lgdi32

set defines=-D_DEBUG

echo building %assembly%

if "%~1"=="-t" (
    if "%~2"=="-v" (
        clang++ -ftime-report %cppFiles%  %thirdparty% %compilerFlags% -o ./bin/%assembly% %defines% %includeFlags% %linkerFlags% 2>&1 | awk "/User Time/" RS="\n\n\n" ORS="\n\n\n"
    ) else (
        clang++ -ftime-report %cppFiles%  %thirdparty% %compilerFlags% -o ./bin/%assembly% %defines% %includeFlags% %linkerFlags% 2>&1 | awk "/Clang front-end time report/" RS="\n\n" ORS="\n\n"
    )
) else (
    clang++ %cppFiles%  %thirdparty% %compilerFlags% -o ./bin/%assembly% %defines% %includeFlags% %linkerFlags%
)

echo %assembly% building complete.