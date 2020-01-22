cmake_minimum_required(VERSION 3.10)
project(aeda1617_ci1)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(aeda1617_ci1 main.cpp Tests/Test.cpp Tests/Mail.cpp Tests/Postman.cpp Tests/PostOffice.cpp)

target_link_libraries(aeda1617_ci1 gtest gtest_main)
