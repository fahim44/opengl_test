add_library(utilities utilities.cpp)

target_include_directories(utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS utilities DESTINATION lib)
install(FILES utilities.h DESTINATION include)