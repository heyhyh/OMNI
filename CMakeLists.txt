cmake_minimum_required(VERSION 3.0)

project(demo VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(demo ${SOURCES}
        src/MOTOR.cpp
        inc/MOTOR.h
        inc/define.h
        src/ROOT_INIT.cpp
        inc/ROOT_INIT.h
        src/PID.cpp
        inc/PID.h
        src/debug.cpp
        inc/debug.h
        inc/MATH.h
        src/can.cpp
        inc/can.h
        inc/TOP.h
        src/define.cpp
        inc/CHASSIS.h
        inc/UART.h
        src/UART.cpp
        src/chassis.cpp
        src/VOFA.cpp
        inc/VOFA.h)

target_link_libraries(demo pthread)