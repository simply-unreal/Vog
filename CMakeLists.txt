cmake_minimum_required(VERSION 3.20)

project(Vog
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_PREFIX_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows"
    ${CMAKE_PREFIX_PATH}
)

find_package(SFML 3 REQUIRED CONFIG COMPONENTS Graphics Window System)

add_executable(Vog
    src/Vog.cpp
    src/app/Application.cpp
    src/app/SourceLoader.cpp
    src/cli/Help.cpp
    src/lexer/Lexer.cpp
    src/output/TokenPrinter.cpp
    src/compiler/debugger/CompilerDebugger.cpp
    src/cli/ArgumentParser.cpp
)

target_include_directories(Vog
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/include
)

target_link_libraries(Vog
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

if(WIN32)
    file(GLOB VCPKG_DLLS_RELEASE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/bin/*.dll"
    )
    file(GLOB VCPKG_DLLS_DEBUG
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows/debug/bin/*.dll"
    )

    add_custom_command(TARGET Vog POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${VCPKG_DLLS_RELEASE} ${VCPKG_DLLS_DEBUG} $<TARGET_FILE_DIR:Vog>
        VERBATIM
    )
endif()

if(MSVC)
    target_compile_options(Vog PRIVATE /W4)
else()
    target_compile_options(Vog PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

set_target_properties(Vog PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)