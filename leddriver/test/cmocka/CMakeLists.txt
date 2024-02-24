cmake_minimum_required(VERSION 3.5.0)
project("Traning of TDD for cmocka" LANGUAGES C)

# cmocka
include(FetchContent)
FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://github.com/clibs/cmocka.git)
FetchContent_MakeAvailable(cmocka)

enable_testing()

add_cmocka_test(cmocka_led_driver
                SOURCES cmocka_led_driver.c
                LINK_LIBRARIES cmocka led_driver runtime_error_stub)
