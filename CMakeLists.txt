cmake_minimum_required(VERSION 3.8)
project(raytracer LANGUAGES CXX)

add_executable(raytracer main.cpp)

target_compile_features(raytracer PUBLIC cxx_std_17)
