cmake_minimum_required(VERSION 3.1)





set(CMAKE_CXX_STANDARD 11)

project(mandelbrot)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)


set(SOURCE_CODE mandelbrot.cpp)

add_executable(mandelbrot ${SOURCE_CODE})
target_link_libraries(mandelbrot sfml-graphics)