cmake_minimum_required(VERSION 3.0.0)
project(cmake_test VERSION 0.1.0)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()
add_test(NAME Runs COMMAND cmake_test)


add_executable(${PROJECT_NAME} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)