cmake_minimum_required(VERSION 3.20)

project(Vog
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Vog
    src/Vog.cpp
    src/lexer/Lexer.cpp
)

target_include_directories(Vog
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(Vog PRIVATE /W4)
else()
    target_compile_options(Vog PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(Vog PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)