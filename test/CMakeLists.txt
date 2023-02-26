cmake_minimum_required(VERSION 3.22)

set(This SecOCTests)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "*.cpp")

foreach (_file ${Sources})

    cmake_path(GET _file STEM executable)
    add_executable(${executable} ${_file})
    target_link_libraries(${executable} PUBLIC
        gtest_main 
        SecOCLib
    )
    
    add_test(
        NAME ${executable}
        COMMAND ${executable}
    )

endforeach()
