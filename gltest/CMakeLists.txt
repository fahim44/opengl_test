add_executable(gltest gltest.cpp)

list(APPEND EXTRA_LIBS gtest_main)
list(APPEND EXTRA_LIBS shaderLib)
list(APPEND EXTRA_LIBS utilities)

#conan dependency
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
list(APPEND EXTRA_LIBS ${CONAN_LIBS})

#find_package(glfw3 3.3 REQUIRED)
#list(APPEND EXTRA_LIBS glfw)

#find_package(GLEW REQUIRED)
#list(APPEND EXTRA_LIBS ${GLEW_LIBRARIES})
#list(APPEND EXTRA_DIRS ${GLEW_INCLUDE_DIRS})


#list(APPEND EXTRA_DIRS ${OPENGL_INCLUDE_DIR})
#list(APPEND EXTRA_LIBS ${OPENGL_gl_LIBRARY})
#list(APPEND EXTRA_LIBS ${OPENGL_glu_LIBRARY})

target_link_libraries(gltest PUBLIC ${EXTRA_LIBS})

target_include_directories(gltest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME gltest COMMAND gltest)