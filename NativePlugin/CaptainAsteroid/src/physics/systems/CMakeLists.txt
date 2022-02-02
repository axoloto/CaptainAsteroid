file(GLOB SRC "*.cpp" "*.hpp")

find_package(Entityx REQUIRED CONFIG)

add_library(Systems ${SRC})

target_include_directories(Systems PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Systems PUBLIC project_options Utils entityx::entityx)
