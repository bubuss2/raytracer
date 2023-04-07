cmake_minimum_required(VERSION 3.8)
project(raytracer LANGUAGES CXX CUDA)

include_directories(source/CPU)
include_directories(source/GPU)
add_executable(raytracer source/GPU/main.cu)

target_compile_features(raytracer PUBLIC cxx_std_17)
