add_executable(cppdb main.cpp)

target_compile_features(cppdb PRIVATE cxx_std_23)

target_link_libraries(cppdb PRIVATE cppdb_warnings)