cmake_minimum_required(VERSION 2.8)

project(backtrace)
set(TARGET ${CMAKE_PROJECT_NAME})

# flags
if (CMAKE_BUILD_TYPE)
else()
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

message("------------ Options -------------")
message("  CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("  CMAKE_COMMAND: ${CMAKE_COMMAND}")

set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_CXX_FLAGS_DEBUG "-g ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 ${CMAKE_CXX_FLAGS}")

message("------------ Cxx flags -------------")
message("  CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}: ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
message("------------------------------------")

# source
aux_source_directory(${PROJECT_SOURCE_DIR} LIST_SRC)
add_library(${TARGET} STATIC ${LIST_SRC})

install(TARGETS ${STATIC_T} LIBRARY DESTINATION "lib" ARCHIVE DESTINATION "lib")
install(FILES ${PROJECT_SOURCE_DIR}/backtrace.h DESTINATION "include/backtrace")
