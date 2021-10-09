cmake_minimum_required(VERSION 3.20)


# Platform detection settings for vcpkg
if(WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
endif()

if(UNIX AND NOT APPLE)
    set(VCPKG_TARGET_TRIPLET "x64-linux-static" CACHE STRING "")
endif()


# Project initial-setup
project("Bravo" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_GENERATOR_PLATFORM x64)


# Finding all source files for this project
file(GLOB sources "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${sources})

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
