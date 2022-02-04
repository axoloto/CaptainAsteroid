add_subdirectory(utils)
add_subdirectory(physics)

file(GLOB SRC "*.cpp" "*.hpp")

add_library(CaptainAsteroid SHARED ${SRC})

target_link_libraries(CaptainAsteroid PRIVATE project_options Utils Physics)

install(TARGETS CaptainAsteroid RUNTIME DESTINATION .)