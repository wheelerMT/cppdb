add_library(cppdb_lib STATIC page.cpp disk_manager.cpp buffer_pool.cpp)
target_compile_features(cppdb_lib PUBLIC cxx_std_23)

add_executable(cppdb main.cpp)

target_link_libraries(cppdb PRIVATE cppdb_warnings cppdb_lib)