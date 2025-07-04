#add_executable(MyTests
#        main_test.cpp
#)
#
#target_link_libraries(MyTests
#        gtest_main
#        NetworkProtocol
#)
#
#include(GoogleTest)
#gtest_discover_tests(MyTests)

add_executable(MyTests
        main_test.cpp
)

target_link_libraries(MyTests
        PRIVATE
        NetworkProtocolLib
        gtest_main
)

add_test(NAME MyTests COMMAND MyTests)