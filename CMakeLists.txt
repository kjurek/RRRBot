project(RRRBot)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)

if (WIN32)
    	add_definitions(/D "WIN32_LEAN_AND_MEAN")
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/jsoncpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/protorpc.cxx)

include_directories(RRRBotCommon/cpp)
add_subdirectory(RRRBotCommon)

add_subdirectory(RRRBotCore)
