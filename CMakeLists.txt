#cmake_minimum_required(VERSION 3.27)
#project(Network_Protocol)
#
#set(CMAKE_CXX_STANDARD 23)
#
#add_executable(Network_Protocol
#        main.cpp)
#
#enable_testing()
#add_subdirectory(third_party/googletest)
#add_subdirectory(test)


cmake_minimum_required(VERSION 3.27)
project(Network_Protocol)

set(CMAKE_CXX_STANDARD 23)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third_party/googletest)