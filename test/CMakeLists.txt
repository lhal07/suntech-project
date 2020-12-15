cmake_minimum_required(VERSION 3.2)
project(server_tests)

add_subdirectory(lib/googletest)

include_directories(${PROJECT_HEADERS_DIR})
include_directories(${PROJECT_HEADERS_DIR}/src/server)
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/server_tests.cpp)

add_executable(server_tests ${SOURCE_FILES})
target_link_libraries(server_tests server gtest)
install(TARGETS server_tests DESTINATION bin)
