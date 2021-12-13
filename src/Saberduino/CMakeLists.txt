cmake_minimum_required(VERSION 3.5)

project(test_arduino_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(saberduino
    saberduino/base_defines.hpp

    saberduino/level.hpp
    saberduino/level.cpp

    saberduino/saber.hpp
    saberduino/saber.cpp

    saberduino/printer.hpp
    saberduino/printer.cpp

    saberduino/display.hpp
    saberduino/display.cpp
)

option(SABERDUINO_DESKTOP_COMPUTER "Use saberduino on a desktop computer" ON)
if(${SABERDUINO_DESKTOP_COMPUTER})
    target_compile_definitions(saberduino PUBLIC SABERDUINO_DESKTOP_COMPUTER=1)

    find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
    target_link_libraries(saberduino PUBLIC sfml-system sfml-graphics sfml-window)
endif()

add_executable(main main.cpp)
target_link_libraries(main PRIVATE saberduino)
