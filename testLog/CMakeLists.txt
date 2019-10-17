add_library(testLog testLog.cpp)

target_include_directories(testLog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS testLog DESTINATION lib)
install(FILES testLog.h DESTINATION include)