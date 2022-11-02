# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

project ("Lab#3")

set(SRC "src/JHLEDBackpack.cpp" "src/JHLEDBackpack.h")
# Add source to this project's executable.
add_executable(lab3_task1 ${SRC} "task1.cpp" )
add_executable(lab3_task2 ${SRC} "task2.cpp" )

target_include_directories(lab3_task1 PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})
target_link_directories(lab3_task1 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(lab3_task1 PUBLIC i2c)

target_include_directories(lab3_task2 PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_directories(lab3_task2 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(lab3_task2 PUBLIC i2c)