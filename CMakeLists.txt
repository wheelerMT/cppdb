cmake_minimum_required(VERSION 3.28)

project(cppdb VERSION 0.1.0 LANGUAGES CXX)

include(cmake/Ccache.cmake)
set(CMAKE_CXX_EXTENSIONS OFF)

if (APPLE)
    execute_process(COMMAND xcrun --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
endif ()

enable_testing()
include(cmake/FetchCatch2.cmake)

include_directories(include)

include(cmake/CompilerWarnings.cmake)
add_subdirectory(src)

add_subdirectory(tests)