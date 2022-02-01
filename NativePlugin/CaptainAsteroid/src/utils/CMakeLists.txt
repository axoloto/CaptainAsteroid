find_package(fmt CONFIG)
find_package(spdlog CONFIG)

file(GLOB SRC "*.cpp" "*.hpp")

add_library(Utils ${SRC})

# Not sure why it is not given through spdlog findPackage
target_compile_definitions(Utils PUBLIC -DSPDLOG_FMT_EXTERNAL)

target_compile_definitions(Utils PUBLIC -DVERSION_MAJOR="${PROJECT_VERSION_MAJOR}")
target_compile_definitions(Utils PUBLIC -DVERSION_MINOR="${PROJECT_VERSION_MINOR}")
target_compile_definitions(Utils PUBLIC -DVERSION_PATCH="${PROJECT_VERSION_PATCH}")

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Utils PUBLIC fmt::fmt spdlog::spdlog)
