add_executable(cppdb_tests main.cpp
        page_test.cpp
        disk_manager_test.cpp)

target_link_libraries(cppdb_tests PRIVATE Catch2::Catch2WithMain cppdb_warnings cppdb_lib)

include(Catch)
catch_discover_tests(cppdb_tests)