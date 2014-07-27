project(RRRBotCore)
cmake_minimum_required(VERSION 2.8)

${CMAKE_SOURCE_DIR}/RRRBotCommon/cpp/core_api.pb.cc

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/lib/jsoncpp/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/protorpc.cxx/src)

set(SOURCES
    src/DllMain.cpp
    src/RRRBot.cpp
    src/Core.cpp
    src/CoreConfigurator.cpp
    src/Misc.cpp
    ${CMAKE_SOURCE_DIR}/RRRBotCommon/cpp/core_api.pb.cc
    include/stdafx.h
    include/RRRBot.h
    include/Core.h
    include/CoreConfigurator.h
    include/Misc.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} jsoncpp PROTORPC)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
