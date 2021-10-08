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

add_subdirectory("${deps-source-dir}/sleepy-discord")
include_directories("${deps-source-dir}/sleepy-discord/include")
#target_include_directories(${PROJECT_NAME} PUBLIC "${deps-source-dir}/sleepy-discord/include")


target_link_libraries(${PROJECT_NAME} sleepy-discord)
#########################################




