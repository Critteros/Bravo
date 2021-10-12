cmake_minimum_required(VERSION 3.18)



find_package(Git REQUIRED)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "git not found!")
endif()

if(NOT EXISTS ${CMAKE_BINARY_DIR}/vcpkg)
    message(STATUS "Downloading vcpkg to ${CMAKE_BINARY_DIR}/vcpkg")
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone https://github.com/microsoft/vcpkg.git vcpkg
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE     git_result
        OUTPUT_VARIABLE     git_output
    )
endif()

message(STATUS "Initializing vcpkg")

# Platform detection settings for vcpkg
if(WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
    execute_process(
        COMMAND bootstrap-vcpkg.bat -disableMetrics
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg
    )
endif()

if(UNIX AND NOT APPLE)
    set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "")
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "-O3")
    execute_process(
        COMMAND ./bootstrap-vcpkg.sh -disableMetrics
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg
    )
endif()

include(${CMAKE_BINARY_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Project initial-setup
project("Bravo" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(project_warnings INTERFACE)
include("cmake/add_compiler_options.cmake")
set_project_warnings(project_warnings)



# Finding all source files for this project
file(GLOB sources "src/*.cpp" "src/*.h" "src/*.hpp")
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE project_warnings)
target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.hpp")

#########################################

# sleepy-discord
find_package(sleepy-discord CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sleepy-discord)

# fmt
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

#spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

#########################################



if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY 
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

