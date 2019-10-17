add_library(test_2 test_2.cpp)

target_include_directories(test_2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS test_2 DESTINATION lib)
install(FILES test_2.h DESTINATION include)