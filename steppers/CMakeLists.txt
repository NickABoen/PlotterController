cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(steppers VERSION 1.0 LANGUAGES CXX)

# Provide compilation database for YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(steppers
    stepper.cpp
    )

# Add Warning Flags
if(MSVC)
    message(STATUS "Compiling with MSVC...")
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Compiling with GNU...")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Compiling with CLANG...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -Wpedantic")
else()
    message(STATUS "Compiler ID = " ${CMAKE_CXX_COMPILER_ID})
endif()
message( STATUS "...End")

# Add compile features
target_compile_features(steppers
    PUBLIC cxx_std_17
    )
