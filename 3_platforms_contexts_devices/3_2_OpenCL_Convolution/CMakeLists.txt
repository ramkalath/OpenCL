cmake_minimum_required(VERSION 3.4)

set(project_name "3_2_OpenCL_Convolution")
# setting project name
project(${project_name})

# here add all the cpp files involved in the project
add_executable(${project_name} ./src/main.cpp) # (TODO: enter the cpp files after the project name one after the other with the path)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_BUILD_TYPE Debug) #required for ycm
set(CMAKE_VERBOSE_MAKEFILE ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# add all the include files
target_include_directories(${project_name} PUBLIC ./include PUBLIC /usr/include PUBLIC /usr/local/include) # you can keep adding more if you want

#here add all the libraries that you included
target_link_libraries(${project_name} OpenCL) # (TODO: add the required libraries here)

# Required for YCM
IF(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
 EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
	${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
	)
ENDIF()
