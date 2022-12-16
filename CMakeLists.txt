cmake_minimum_required(VERSION 3.25)

if (WIN32)
    file(GLOB SCR_FILES CONFIGURE_DEPENDS "source/*.c")
    file(GLOB HDR_FILES CONFIGURE_DEPENDS "include/*.h")
    list(REMOVE_ITEM SCR_FILES "${CMAKE_SOURCE_DIR}/source/ethernet.c")
    list(REMOVE_ITEM HDR_FILES "${CMAKE_SOURCE_DIR}/include/ethernet.h")
    set (CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "" FORCE)
elseif(UNIX)
    file(GLOB SCR_FILES CONFIGURE_DEPENDS  "source/*.c")
    file(GLOB HDR_FILES CONFIGURE_DEPENDS  "include/*.h")
    set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
endif()


project(SecOC)
add_executable(SecOC ${SCR_FILES})


# configure_file(OSconfig.h.in OSconfig.h)
target_include_directories(SecOC PRIVATE include/)
# target_include_directories(SecOC PRIVATE ${PROJECT_BINARY_DIR})
if(WIN32)
    target_compile_definitions(SecOC PUBLIC WINDOWS)
elseif(UNIX)
    target_compile_definitions(SecOC PUBLIC LINUX)
endif()



