add_library(shaderLib shaderLib.cpp)

target_include_directories(shaderLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


list(APPEND EXTRA_LIBS_SHADER_LIBS utilities)
target_link_libraries(shaderLib PUBLIC ${EXTRA_LIBS_SHADER_LIBS})

install(TARGETS shaderLib DESTINATION lib)
install(FILES shaderLib.h DESTINATION include)