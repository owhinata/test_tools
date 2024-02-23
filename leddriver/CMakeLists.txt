cmake_minimum_required(VERSION 3.5.0)
project("Traning of TDD" LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(led_driver SHARED
  src/driver.c)

target_include_directories(led_driver
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test/cmocka)

execute_process(COMMAND cmake -E create_symlink
                "${CMAKE_BINARY_DIR}/compile_commands.json"
                "${CMAKE_SOURCE_DIR}/compile_commands.json")
