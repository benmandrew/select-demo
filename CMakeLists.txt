
cmake_minimum_required(VERSION 3.9.1)
project(select LANGUAGES C)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-O3 -D_FORTIFY_SOURCE=2 -fasynchronous-unwind-tables
  -fpie -Wl,-pie -fpic -shared -fstack-clash-protection -fstack-protector
  -Werror=implicit-function-declaration)

add_subdirectory(src)
