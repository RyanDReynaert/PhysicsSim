cmake_minimum_required(VERSION 3.10)
project(Physics_Sim)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(sim_main ${SOURCES})

find_package(SDL2 REQUIRED)

target_include_directories(sim_main PRIVATE
    ${SDL2_INCLUDE_DIRS}
    src/
)

target_link_libraries(sim_main PRIVATE
    ${SDL2_LIBRARIES}
)