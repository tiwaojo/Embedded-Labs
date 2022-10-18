# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

project ("Lab#1: Embedded System behavior with introduction on Jetson TX2 and Stack Use")

# Add source to this project's executable.
add_executable (lab1 "cmp.c")# "CMakeProject1.h")
set_target_properties(lab1 PROPERTIES COMPILE_FLAGS "-save-temps" )

if(MSVC) #win32
	target_compile_options(lab1 PUBLIC "/FAcs" "/GL" "/02" )
	# https://learn.microsoft.com/en-us/cpp/build/reference/ga-optimize-for-windows-application?view=msvc-170
else() #Linux
	target_compile_options(lab1 PUBLIC "-save-temps" "-g" )
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab1 PROPERTY CXX_STANDARD 20)
endif()
# https://stackoverflow.com/questions/137038/how-do-you-get-assembler-output-from-c-c-source-in-gcc
# TODO: Add tests and install targets if needed.
