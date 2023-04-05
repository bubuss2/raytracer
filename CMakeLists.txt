cmake_minimum_required(VERSION 3.8)
project(raytracer LANGUAGES CXX)

include_directories(source)
add_executable(raytracer source/main.cpp)

target_compile_features(raytracer PUBLIC cxx_std_17)
