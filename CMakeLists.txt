cmake_minimum_required(VERSION 3.0.0)
project(dddcpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

include(CTest)
enable_testing()

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE third/catch2)

add_library(hhdate INTERFACE)
target_include_directories(hhdate INTERFACE third/hhdate)

add_library(tlexpected INTERFACE)
target_include_directories(tlexpected INTERFACE third/tlexpected)

add_library(tloptional INTERFACE)
target_include_directories(tloptional INTERFACE third/tloptional)

add_subdirectory(meetlib)
add_subdirectory(meetapp)
add_subdirectory(meettest)

add_test(NAME MeetTest COMMAND meettest)