cmake_minimum_required(VERSION 3.2)
project(server-proj)

add_subdirectory(server)
set(SOURCE_FILES main.cpp)

add_executable(server-proj ${SOURCE_FILES})
target_link_libraries(server-proj server)
install(TARGETS server-proj DESTINATION ${PROJECT_INSTALL_BIN_DIR})
