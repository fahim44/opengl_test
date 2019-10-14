cmake_minimum_required(VERSION 3.10.2)

project(cmake_test VERSION 1.0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND SOURCE main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})

configure_file(ProjectConfig.h.in ProjectConfig.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})