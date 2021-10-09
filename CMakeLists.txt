cmake_minimum_required(VERSION 3.20)


# Project initial-setup
project("Bravo" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Finding all source files for this project
file(GLOB sources "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${sources})

#########################################
#Deps
set(project-deps-list)

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




