#
# environment variables example
#
### Google Mock
#export GMOCK_HOME=$HOME/..../gmock-1.6.0
#
#
### Boost
#export BOOST_ROOT=$HOME/..../boost_1_53_0
#
#
### jsoncpp
#export JSONCPP_HOME=$HOME/..../jsoncpp-src-0.5.0
#
#
### libcurl
#export CURL_HOME=$HOME/..../curl-7.30.0
#
#

project(design)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include $ENV{JSONCPP_HOME}/include $ENV{CURL_HOME}/include $ENV{BOOST_ROOT})
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild $ENV{JSONCPP_HOME}/libs/linux-gcc-4.7 $ENV{CURL_HOME}/build/lib)
add_definitions(-std=c++0x)
add_definitions(-g)
add_definitions(-O0)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(sources
   main.cpp
   collection_data_test.cpp
   lib/mutex_posix.cpp
)
add_executable(test ${sources})
target_link_libraries(test pthread)
target_link_libraries(test gmock)
target_link_libraries(test gtest)
target_link_libraries(test json_linux-gcc-4.7)
target_link_libraries(test curl)

