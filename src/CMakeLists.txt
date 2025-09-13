add_library(NetworkProtocolLib
        main.cpp
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