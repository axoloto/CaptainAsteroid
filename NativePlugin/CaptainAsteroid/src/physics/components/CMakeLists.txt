file(GLOB SRC "*.cpp" "*.hpp")

find_package(Entityx REQUIRED CONFIG)

add_library(Components ${SRC})

target_include_directories(Components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Components PUBLIC project_options Utils entityx::entityx)
