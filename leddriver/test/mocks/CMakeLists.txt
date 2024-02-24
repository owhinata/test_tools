cmake_minimum_required(VERSION 3.5.0)
project("Mock object for led driver" LANGUAGES C)

add_library(runtime_error_stub STATIC runtime_error_stub.c)
target_include_directories(runtime_error_stub
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE $<TARGET_PROPERTY:led_driver,INTERFACE_INCLUDE_DIRECTORIES>)
