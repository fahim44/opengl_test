cmake_minimum_required(VERSION 3.0.0)
project(cmake_test VERSION 0.1.0)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CTest)
enable_testing()
add_test(NAME Runs COMMAND cmake_test)


add_executable(${PROJECT_NAME} main.cpp)

#sub_dir

add_subdirectory(utilities)
list(APPEND EXTRA_LIBS utilities)

add_subdirectory(shaderLib)
list(APPEND EXTRA_LIBS shaderLib)

#opengl
find_package(glfw3 3.3 REQUIRED)
list(APPEND EXTRA_LIBS glfw)

find_package(GLEW REQUIRED)
list(APPEND EXTRA_LIBS ${GLEW_LIBRARIES})
list(APPEND EXTRA_DIRS ${GLEW_INCLUDE_DIRS})


find_package(OpenGL REQUIRED)
list(APPEND EXTRA_DIRS ${OPENGL_INCLUDE_DIR})
list(APPEND EXTRA_LIBS ${OPENGL_gl_LIBRARY})
list(APPEND EXTRA_LIBS ${OPENGL_glu_LIBRARY})

##

target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

#copy resource files
configure_file(${PROJECT_SOURCE_DIR}/res/shaders/basic.shader ${PROJECT_BINARY_DIR}/res/shaders/basic.shader COPYONLY)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)