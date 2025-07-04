cmake_minimum_required(VERSION 3.27)
project(NetworkProtocol)

set(CMAKE_CXX_STANDARD 23)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party/googletest)