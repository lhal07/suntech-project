cmake_minimum_required(VERSION 3.2)
project(server C CXX)

include_directories(../connection ../config)

set(SOURCE_FILES
    server.h
    server.cpp
)

add_library(server SHARED STATIC ${SOURCE_FILES})
target_link_libraries(server connection)
target_link_libraries(server config)

install(TARGETS server DESTINATION ${PROJECT_INSTALL_LIB_DIR})
install(FILES server.h DESTINATION ${PROJECT_INSTALL_INCLUDE_DIR})
