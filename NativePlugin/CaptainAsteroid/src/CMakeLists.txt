add_subdirectory(utils)
add_subdirectory(physics)

file(GLOB SRC "*.cpp" "*.hpp")

add_library(CaptainAsteroid SHARED ${SRC})

target_link_libraries(CaptainAsteroid PRIVATE project_options project_warnings Utils Physics)

install(TARGETS CaptainAsteroid RUNTIME DESTINATION dll)