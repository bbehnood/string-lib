cmake_minimum_required(VERSION 3.16)

project(StringLib LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(strlib
	src/strlib.c
)

target_include_directories(strlib PUBLIC include)

target_compile_options(strlib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(test_string
	test/main.c
)

target_link_libraries(test_string PRIVATE strlib)
