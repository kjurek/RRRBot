project(jsoncpp)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

SET(PUBLIC_HEADERS
    include/json/config.h
    include/json/forwards.h
    include/json/features.h
    include/json/value.h
    include/json/reader.h
    include/json/writer.h
    include/json/assertions.h
    include/json/version.h
)

set(SOURCES
    ${PUBLIC_HEADERS}
    src/json_tool.h
    src/json_reader.cpp
    src/json_batchallocator.h
    src/json_valueiterator.inl
    src/json_value.cpp
    src/json_writer.cpp
    src/version.h.in
)

add_library(${PROJECT_NAME} ${SOURCES})
