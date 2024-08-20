cmake_minimum_required(VERSION 3.17)
project(e2cwt)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/code")

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

foreach(SOURCE_PATH ${SOURCES})
    get_filename_component(SOURCE_FILE_NAME "${SOURCE_PATH}" NAME)
    if(SOURCE_FILE_NAME MATCHES "^test.*")
        list(REMOVE_ITEM SOURCES "${SOURCE_PATH}")
    endif()
endforeach()

add_executable(e2cwt ${SOURCES})

