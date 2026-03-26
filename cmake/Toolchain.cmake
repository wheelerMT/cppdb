if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    find_program(CMAKE_C_COMPILER
            NAMES clang
            PATHS /opt/homebrew/opt/llvm/bin
            NO_DEFAULT_PATH
    )
    find_program(CMAKE_CXX_COMPILER
            NAMES clang++
            PATHS /opt/homebrew/opt/llvm/bin
            NO_DEFAULT_PATH
    )
endif ()
