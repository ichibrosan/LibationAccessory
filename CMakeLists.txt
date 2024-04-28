cmake_minimum_required(VERSION 3.28)
project(Liberator)

add_executable(Liberator main.cpp)
find_package(Boost REQUIRED COMPONENTS system filesystem)

target_link_libraries(Liberator ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
set(CMAKE_CXX_STANDARD 17)
