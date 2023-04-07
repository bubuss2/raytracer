cmake_minimum_required(VERSION 3.8)
project(raytracer LANGUAGES CXX CUDA)

include_directories(source/CPU)
add_executable(raytracer source/CPU/main.cpp)

target_compile_features(raytracer PUBLIC cxx_std_17)
