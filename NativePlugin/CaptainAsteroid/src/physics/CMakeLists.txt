file(GLOB SRC "*.cpp" "*.hpp")

find_package(Entityx REQUIRED CONFIG)

add_subdirectory(components)
add_subdirectory(systems)

add_library(Physics ${SRC})

target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Physics PRIVATE project_options Components Systems Utils entityx::entityx)
