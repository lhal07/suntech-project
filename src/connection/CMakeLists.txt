cmake_minimum_required(VERSION 3.2)
project(connection C CXX)

include_directories(../config)

set(SOURCE_FILES
    connection.h
    connection.cpp
)

add_library(connection SHARED STATIC ${SOURCE_FILES})
target_link_libraries(connection config)

install(TARGETS connection DESTINATION ${PROJECT_INSTALL_LIB_DIR})
install(FILES connection.h DESTINATION ${PROJECT_INSTALL_INCLUDE_DIR})
