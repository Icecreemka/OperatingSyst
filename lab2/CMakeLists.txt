cmake_minimum_required(VERSION 3.14)

project(LAB2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR "C:/Users/user/Documents/acm/OS/lab2")

if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

add_executable(LAB2 "${SOURCE_DIR}/lab2.cpp")

enable_testing()  

set(GTest_DIR "C:/Users/user/Documents/vcpkg/installed/x64-windows/share/gtest")
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests "${SOURCE_DIR}/test.cpp")

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_test(NAME LAB2_Tests COMMAND tests)
