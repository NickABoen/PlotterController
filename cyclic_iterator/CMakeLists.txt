cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(cyclic_iterator VERSION 1.0 LANGUAGES CXX)

# Provide compilation database for YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define library
add_library(cyclic_iterator
#add_executable(cyclic_iterator
    cyclic_iterator.cpp
    )

# Add compile features
target_compile_features(cyclic_iterator
    PUBLIC cxx_std_17
    )
