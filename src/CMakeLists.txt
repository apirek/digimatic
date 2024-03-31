cmake_minimum_required(VERSION 3.13)

include(../pico-sdk/pico_sdk_init.cmake)

project(digimatic)

pico_sdk_init()

add_executable(digimatic
  digimatic.c
  led.c
  main.c
)

target_link_libraries(digimatic
  hardware_gpio
  pico_stdio
  pico_stdlib
  pico_time
)
pico_add_extra_outputs(digimatic)
