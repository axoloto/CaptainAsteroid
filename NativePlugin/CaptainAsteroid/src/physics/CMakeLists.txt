file(GLOB SRC "*.cpp" "*.hpp")

add_library(Physics ${SRC})

target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Physics PUBLIC project_options Utils)

install(TARGETS Physics RUNTIME DESTINATION lib)
