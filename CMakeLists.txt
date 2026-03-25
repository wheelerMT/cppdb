cmake_minimum_required(VERSION 3.28)

project(cppdp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

if (APPLE)
    execute_process(COMMAND xcrun --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
endif ()

include(cmake/CompilerWarnings.cmake)
add_subdirectory(src)
