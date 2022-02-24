
cmake_minimum_required( VERSION 3.9.1 )

project( select_internal )

include_directories(${CMAKE_SOURCE_DIR}/include)

set(send_source_files send_main.c fd_event.c)
set(receive_source_files receive_main.c fd_event.c)

add_executable(send ${send_source_files})
add_executable(receive ${receive_source_files})
