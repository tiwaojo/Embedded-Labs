# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

project ("Lab#2: Embedded System behavior with introduction on Jetson TX2 and Stack Use")

include(FetchContent)
FetchContent_Declare(
  JetsonGPIO 
  GIT_REPOSITORY https://github.com/pjueon/JetsonGPIO.git 
  GIT_TAG master
)
FetchContent_MakeAvailable(JetsonGPIO)


# Add source to this project's executable.
add_executable (lab2 "gpio_button.c" "jetsonGPIO.c" "jetsonGPIO.h")# "CMakeProject1.h")
target_link_libraries(lab2 JetsonGPIO::JetsonGPIO)
