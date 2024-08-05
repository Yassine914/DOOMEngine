cmake_minimum_required(VERSION "3.20.x")

set(CMAKE_CXX_STANDARD 17)

# ------------------- DOOM ENGINE ----------------------
project(DOOMEngine)

file(GLOB SRC CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(DOOMEngine "${SRC}")

# ----- FILES -----
# for debug builds
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/")

# for release builds (make filepaths relative to the exe)
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RES_PATH="./res/")
