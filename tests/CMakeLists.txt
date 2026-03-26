add_executable(cppdb_tests main.cpp)

target_link_libraries(cppdb_tests PRIVATE Catch2::Catch2WithMain cppdb_warnings cppdb_lib)

include(Catch)
catch_discover_tests(cppdb_tests)