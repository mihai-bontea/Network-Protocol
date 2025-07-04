add_library(NetworkProtocolLib
        protocol.cpp
)

target_include_directories(NetworkProtocolLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(NetworkProtocol
        main.cpp
)

target_link_libraries(NetworkProtocol
        PRIVATE NetworkProtocolLib
)

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