cmake_minimum_required(VERSION 3.20)

project(Shadow CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Git commit embed
include(scripts/git.cmake)

# Fetch modules
message("\nFetching modules")
include(scripts/async-logger.cmake)
include(scripts/json.cmake)
include(scripts/cpr.cmake)

message("\nFetching custom modules")
include(scripts/imgui.cmake)
# Shadow

message(STATUS "Shadow Loader")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)

add_executable(Shadow WIN32 "${SRC_MAIN}")

# Set windows subsystem
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET Shadow PROPERTY CXX_STANDARD 23) # 23 Because std::format is not avalible in std:c++20 for some reason. Maybe it's because i use v142 toolset.

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

# Add Directx directory to be found
target_link_directories(Shadow PRIVATE
    "$ENV{DXSDK_DIR}/Lib/x64"
)

target_include_directories(Shadow PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include" 
    "${imgui_SOURCE_DIR}" 
	"${DirectX11_INCLUDE_DIRS}"
    "$ENV{DXSDK_DIR}/Include"
)

target_precompile_headers(Shadow PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(Shadow PRIVATE AsyncLogger imgui d3dx11 d3d11)

# Warnings as errors
add_definitions("/wd4005")
set_property(TARGET Shadow PROPERTY COMPILE_WARNING_AS_ERROR ON)

add_compile_definitions(Shadow
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX" 
    "WIN32_LEAN_AND_MEAN" 
)