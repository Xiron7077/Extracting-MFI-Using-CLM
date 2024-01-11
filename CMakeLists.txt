cmake_minimum_required(VERSION 3.27)
project(Research_Project)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64/lib/cmake")

add_executable(Research_Project main.cpp include/node.h include/edge.h include/combination.h)
add_executable(ui src/ui.cpp include/node.h include/edge.h include/combination.h)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries(Research_Project PRIVATE Qt6::Widgets)
target_link_libraries(ui PRIVATE Qt6::Widgets)
