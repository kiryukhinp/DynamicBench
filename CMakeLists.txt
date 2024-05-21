cmake_minimum_required (VERSION 3.0...3.13) 
project (udplib)

if(WIN32)
    add_compile_options("/std:c++latest")
else()
    add_compile_options("-std=c++17")
endif(WIN32)

set( SRC "IRTKinetics/")
set (CMAKE_BUILD_TYPE Debug)

add_executable(irtkin ${SRC}main.cpp ${SRC}Point2D.cpp ${SRC}ReactorState.cpp ${SRC}ReactorUtilits.cpp ${SRC}HeatHydraulic.cpp)
# add_executable(corts ${SRC}testmain.cpp ${SRC}ControlRod.hpp ${SRC}Point2D.cpp)