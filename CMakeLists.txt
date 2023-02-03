
set(CMAKE_BUILD_TYPE Debug)

if (WIN32)
    file(GLOB_RECURSE SCR_FILES CONFIGURE_DEPENDS "source/*.c")
    file(GLOB_RECURSE HDR_FILES CONFIGURE_DEPENDS "include/*.h")
    list(REMOVE_ITEM SCR_FILES "${CMAKE_SOURCE_DIR}/source/ethernet.c")
    list(REMOVE_ITEM HDR_FILES "${CMAKE_SOURCE_DIR}/include/ethernet.h")
    set (CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
elseif(UNIX)
    file(GLOB_RECURSE SCR_FILES CONFIGURE_DEPENDS  "source/*.c")
    file(GLOB_RECURSE HDR_FILES CONFIGURE_DEPENDS  "include/*.h")
    set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
endif()

project(SecOC)

add_executable(SecOC ${SCR_FILES})

foreach (_file ${HDR_FILES})
    cmake_path(REMOVE_FILENAME _file)

    target_include_directories(SecOC PUBLIC ${_file})
endforeach()


if(WIN32)
    target_compile_definitions(SecOC PUBLIC WINDOWS)
elseif(UNIX)
    target_compile_definitions(SecOC PUBLIC LINUX)
endif()



