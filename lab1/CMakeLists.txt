cmake_minimum_required(VERSION 3.5)

project(EmployeeApp)

set(CMAKE_CXX_STANDARD 98)

add_executable(Creator creator.cpp)

add_executable(Reporter reporter.cpp)

add_executable(Main main.cpp)