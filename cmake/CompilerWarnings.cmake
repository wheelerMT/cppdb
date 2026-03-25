add_library(cppdb_warnings INTERFACE)

target_compile_options(cppdb_warnings INTERFACE -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wimplicit-fallthrough)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(cppdb_warnings INTERFACE -fsanitize=address)
    target_link_options(cppdb_warnings INTERFACE -fsanitize=address)
endif ()