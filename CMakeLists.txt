cmake_minimum_required(VERSION 3.20)
project(gipsy_paint)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(gpaint gpaint.cpp gpaint-functions.cpp)
target_link_libraries(gpaint PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)