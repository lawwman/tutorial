cmake_minimum_required (VERSION 3.14.0)
project (NN)  # sets name of project and store in variable PROJECT_NAME

# adds a library to the project. However, it is not linked to executable yet.
# Use target_link_libraries to link it to the main project executable
add_library(
	perceptron
	Perceptron.hpp
	Perceptron.cpp
	)

add_executable(NN hello_world.cpp)

target_link_libraries(NN PRIVATE perceptron)