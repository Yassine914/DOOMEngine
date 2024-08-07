cmake_minimum_required(VERSION "3.20.x")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")
set(PROJ_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# ------------------- DOOM ENGINE ----------------------
project(DOOMEngine)

# ----- SOURCE -----
file(GLOB SRC CMAKE_CONFIGURE_DEPENDS "${SRC_DIR}/*/*.cpp")

add_executable(DOOMEngine "${SRC}" "src/entrypoint.cpp")

# ----- IN-CODE ASSET DIRS -----
# for debug builds
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RES_PATH="${PROJ_DIR}/res/")

# for release builds (make filepaths relative to the exe)
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RES_PATH="./res/")

# ----- LIBRARIES -----
add_subdirectory("${LIB_DIR}/GLFW")
include_directories("${LIB_DIR}/GLFW/include/")

include_directories("${LIB_DIR}/Eigen/")

add_library(glad STATIC "${LIB_DIR}/glad/src/glad.c" "src/entrypoint.cpp")
include_directories("${LIB_DIR}/glad/include/")

file(GLOB IMGUI_SRC CMAKE_CONFIGURE_DEPENDS "${LIB_DIR}/imgui/src/*.cpp")
add_library(imgui STATIC "${IMGUI_SRC}" "src/entrypoint.cpp")
include_directories("${LIB_DIR}/imgui/include/")

add_library(stb_image STATIC "${LIB_DIR}/stb_image/src/stb_image.cpp")
include_directories("${LIB_DIR}/stb_image/include/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glad  glfw imgui stb_image)

# ----- DEFINES -----

if(WIN32)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _WIN32)
endif()
