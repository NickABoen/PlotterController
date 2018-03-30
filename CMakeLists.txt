cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(plotter VERSION 1.0 LANGUAGES CXX)

# Provide compilation database for YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#add_subdirectory(../libs/libSDL2pp ./libs)
add_subdirectory(./steppers)

# Add targets
add_executable(plotter
    test_main.cpp
    i_wiringPi.cpp
    wiringPiContext.cpp
    stepper.cpp
    stepper_coil.cpp
    )

message( STATUS "Start...")
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

# Add target definitions
#target_compile_definitions(plotter
#    PUBLIC DATA_PATH="${PROJECT_SOURCE_DIR}/data"
#    )

# Setup target includes
#target_include_directories(plotter
#    PUBLIC ${SDL2PP_INCLUDE_DIRS}
#    )

# Link target libraries
#target_link_libraries(plotter
#    PUBLIC ${SDL2PP_LIBRARIES}
#    )

target_link_libraries(plotter
    PUBLIC steppers
    )

find_library(lib_wiringPi wiringPi)

if(lib_wiringPi)
    add_definitions(-DHAS_WIRING_PI)
    target_link_libraries(plotter
        PUBLIC wiringPi
        )
endif()

# Add compile features
target_compile_features(plotter
    PUBLIC cxx_std_17
    )
