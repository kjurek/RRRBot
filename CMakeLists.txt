project(RRRBot)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)
set(RELEASE_DIR Release)

include_directories(RRRBotCommon/include)

add_subdirectory(RRRBotCommon)
add_subdirectory(RRRBotCore)
add_subdirectory(RRRBotApplication)
