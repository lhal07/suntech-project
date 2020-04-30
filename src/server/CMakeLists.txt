cmake_minimum_required(VERSION 3.2)
project(server C CXX)

set(SOURCE_FILES
    server.h
    server.cpp
)

add_library(server SHARED STATIC ${SOURCE_FILES})

install(TARGETS server DESTINATION ${PROJECT_INSTALL_LIB_DIR})
install(FILES server.h DESTINATION ${PROJECT_INSTALL_INCLUDE_DIR})
