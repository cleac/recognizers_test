cmake_minimum_required(VERSION 2.8)
project(pattern_recognize CXX)

enable_testing()

set(BIN_NAME test.app)

add_executable(test.app main.cpp)

set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

install (TARGETS ${BIN_NAME} DESTINATION bin)
