cmake_minimum_required(VERSION 3.26)
project(ZAP_PROJ_2)

set(CMAKE_CXX_STANDARD 17)

# Include directories for libpqxx and libpq
include_directories(/usr/local/opt/libpqxx/include)
include_directories(/usr/local/opt/libpq/include)

# Link directories for libpqxx and libpq
link_directories(/usr/local/opt/libpqxx/lib)
link_directories(/usr/local/opt/libpq/lib)

add_executable(ZAP_PROJ_2 main.cpp)

# Link the libpqxx and libpq libraries
target_link_libraries(ZAP_PROJ_2 pqxx pq)