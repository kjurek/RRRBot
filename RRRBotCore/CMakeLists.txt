project(RRRBotCore)
cmake_minimum_required(VERSION 2.8)

include_directories(include)
include_directories(lib/jsoncpp/include)

set(SOURCES
    src/DllMain.cpp
    src/RRRBot.cpp
    src/Core.cpp
    src/CoreConfigurator.cpp
    src/Misc.cpp
    include/stdafx.h
    include/RRRBot.h
    include/ICoreApi.h
    include/Core.h
    include/CoreConfigurator.h
    include/Misc.h
)

add_subdirectory(lib/jsoncpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} jsoncpp)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
