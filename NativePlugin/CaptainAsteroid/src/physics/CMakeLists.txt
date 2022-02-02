file(GLOB SRC "*.cpp" "*.hpp")

find_package(Entityx REQUIRED CONFIG)

add_library(Physics ${SRC})

add_subdirectory(components)
add_subdirectory(systems)
add_subdirectory(events)

target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Physics PUBLIC project_options Utils entityx::entityx)
