add_library(cppdb_warnings INTERFACE)

target_compile_options(cppdb_warnings INTERFACE -Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wimplicit-fallthrough)

# __COUNTER__ is used by Catch2 macros and is flagged as a C2y extension
# by Clang 22+. Safe to suppress — it's universally supported.
target_compile_options(cppdb_warnings INTERFACE -Wno-c2y-extensions)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(cppdb_warnings INTERFACE -fsanitize=address)
    target_link_options(cppdb_warnings INTERFACE -fsanitize=address)
endif ()