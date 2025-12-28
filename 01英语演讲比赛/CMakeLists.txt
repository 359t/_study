cmake_minimum_required(VERSION 3.5)

project(Enlish_speech)

set(CMAKE_BUILD_TYPE DEBUG)

include_directories(./include)

add_executable(Enlish_speech src/main.cpp src/speechManager.cpp src/speaker.cpp)