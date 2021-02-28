cmake_minimum_required(VERSION 3.10)
project(super-mario-bro)

include_directories(deps/glad/include)
include_directories(deps/glfw/include)
include_directories(deps/glm)
include_directories(deps/stb)

add_subdirectory(deps/box2d)

file(GLOB_RECURSE SOURCE_FILES
	 src/*.c src/*.cpp)

file(GLOB_RECURSE HEADER_FILES
	 src/*.h src/*.hpp)

file(GLOB_RECURSE SHADER_FILES
	 assets/*.vert assets/*.frag)

add_executable(super-mario-bro deps/glad/src/glad.c ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})

target_link_libraries(super-mario-bro glfw)
target_link_libraries(super-mario-bro box2d)

target_compile_definitions(super-mario-bro PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")