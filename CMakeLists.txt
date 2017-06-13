cmake_minimum_required (VERSION 3.6)
project (sodium-cxx-examples)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(sodium ${CMAKE_BINARY_DIR}_sodium)

include(sodium-qt/examples/simple_hold/simple_hold.cmake)
include(sodium-qt/examples/reverse/reverse.cmake)
include(sodium-qt/examples/accumulator/accumulator.cmake)
include(sodium-qt/examples/accumulator_editable/accumulator_editable.cmake)

