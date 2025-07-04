include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(MyTests
        main_test.cpp
)

target_link_libraries(MyTests
        gtest_main
        NetworkProtocol
)

include(GoogleTest)
gtest_discover_tests(MyTests)