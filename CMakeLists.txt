cmake_minimum_required(VERSION 3.10)


#Project initial-setup
project("Bravo" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(deps-source-dir "${PROJECT_SOURCE_DIR}/deps")

# Finding all source files for this project
file(GLOB sources "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${sources})

#########################################
#Deps
set(project-deps-list)

# seleepy-discord

set(OPENSSL_ROOT_DIR "C:\\Program Files\\Git\\usr\\bin")
add_subdirectory("${deps-source-dir}/sleepy-discord")
#########################################

#VS fix
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})