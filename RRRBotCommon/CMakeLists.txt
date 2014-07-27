project(RRRBotCommon)
cmake_minimum_required(VERSION 2.8)

set(CPP_OUT ${PROJECT_SOURCE_DIR}/cpp)
set(PYTHON_OUT ${PROJECT_SOURCE_DIR}/python)
set(PROTOC ${CMAKE_SOURCE_DIR}/lib/protorpc.cxx/bin/protoc.exe)
set(PROTO_DIR ${PROJECT_SOURCE_DIR})
set(PROTO_FILE_NAME core_api)
set(PROTO_FILE_PATH ${PROJECT_SOURCE_DIR}/${PROTO_FILE_NAME}.proto)
set(PROTOC_ARGS
    --proto_path=${PROTO_DIR}
    --cpp_out=${CPP_OUT}
    --python_out=${PYTHON_OUT}
    ${PROTO_FILE_PATH}
)

execute_process(
    COMMAND ${PROTOC} ${PROTOC_ARGS}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
)

if( ${result} )
    message(FATAL_ERROR "${result}: ${error}")
endif()
