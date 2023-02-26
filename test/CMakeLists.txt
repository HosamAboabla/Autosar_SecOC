cmake_minimum_required(VERSION 3.22)

set(This SecOCTests)

set(Sources 
    SecOCTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main 
    SecOCLib
)

add_test(
    NAME ${This}
    COMMAND ${This}
)