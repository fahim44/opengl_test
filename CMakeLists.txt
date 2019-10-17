cmake_minimum_required(VERSION 3.0.0)
project(cmake_test VERSION 0.1.0)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()
add_test(NAME Runs COMMAND cmake_test)


add_executable(${PROJECT_NAME} main.cpp)

#sub_dir
add_subdirectory(test_2)
list(APPEND EXTRA_LIBS test_2)

#opengl
find_package(glfw3 3.3 REQUIRED)
list(APPEND EXTRA_LIBS glfw)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
list(APPEND EXTRA_LIBS ${OPENGL_gl_LIBRARY})
list(APPEND EXTRA_LIBS ${OPENGL_glu_LIBRARY})
##


target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)