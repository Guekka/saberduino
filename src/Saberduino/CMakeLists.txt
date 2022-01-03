cmake_minimum_required(VERSION 3.5)

project(test_arduino_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR "libraries/saberduino")
set(SOURCE_DIR "main")

add_library(saberduino
    ${INCLUDE_DIR}/base_defines.hpp

    ${INCLUDE_DIR}/level.hpp
    ${INCLUDE_DIR}/level.cpp

    ${INCLUDE_DIR}/saber.hpp
    ${INCLUDE_DIR}/saber.cpp

    ${INCLUDE_DIR}/printer.hpp
    ${INCLUDE_DIR}/printer.cpp

    ${INCLUDE_DIR}/display.hpp
    ${INCLUDE_DIR}/display.cpp
)

option(SABERDUINO_DESKTOP_COMPUTER "Use saberduino on a desktop computer" ON)
if(${SABERDUINO_DESKTOP_COMPUTER})
    target_compile_definitions(saberduino PUBLIC SABERDUINO_DESKTOP_COMPUTER=1)

    find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
    target_link_libraries(saberduino PUBLIC sfml-system sfml-graphics sfml-window)
endif()

add_executable(main ${SOURCE_DIR}/main.cpp)
target_link_libraries(main PRIVATE saberduino)
target_include_directories(main PRIVATE libraries)
