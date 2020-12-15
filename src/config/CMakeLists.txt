cmake_minimum_required(VERSION 3.2)
project(config C CXX)

set(SOURCE_FILES
    config.h
    config.cpp
)

add_library(config SHARED STATIC ${SOURCE_FILES})

install(TARGETS config DESTINATION ${PROJECT_INSTALL_LIB_DIR})
install(FILES config.h DESTINATION ${PROJECT_INSTALL_INCLUDE_DIR})
