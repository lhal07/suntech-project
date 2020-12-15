cmake_minimum_required(VERSION 3.2)
project(suntech-server)

include_directories(server config connection)
add_subdirectory(config)
add_subdirectory(connection)
add_subdirectory(server)
set(SOURCE_FILES main.cpp )

add_executable(suntech-server ${SOURCE_FILES})
target_link_libraries(suntech-server config)
target_link_libraries(suntech-server connection)
target_link_libraries(suntech-server server)
target_link_libraries(suntech-server pthread)
target_link_libraries(suntech-server boost_system)
target_link_libraries(suntech-server boost_chrono)
target_link_libraries(suntech-server stdc++fs)

install(TARGETS suntech-server DESTINATION ${PROJECT_INSTALL_BIN_DIR})
