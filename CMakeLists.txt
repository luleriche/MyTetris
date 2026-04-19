cmake_minimum_required(VERSION 3.18)
project(MyTetris)
include_directories(include)

# Vérifie que SFML est installé :
find_package(SFML 2 COMPONENTS graphics window system)

add_compile_options(-Wall)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})