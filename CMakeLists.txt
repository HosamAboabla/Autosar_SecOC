cmake_minimum_required(VERSION 3.20)
set(CMAKE_BUILD_TYPE Debug)


if (WIN32)
    file(GLOB_RECURSE SCR_FILES CONFIGURE_DEPENDS "source/*.c")
    file(GLOB_RECURSE HDR_FILES CONFIGURE_DEPENDS "include/*.h")
    list(REMOVE_ITEM SCR_FILES "${CMAKE_SOURCE_DIR}/source/Ethernet/ethernet.c")
    list(REMOVE_ITEM HDR_FILES "${CMAKE_SOURCE_DIR}/include/Ethernet/ethernet.h")
    list(REMOVE_ITEM SCR_FILES "${CMAKE_SOURCE_DIR}/source/Ethernet/scheduler.c")
    list(REMOVE_ITEM HDR_FILES "${CMAKE_SOURCE_DIR}/include/Ethernet/scheduler.h")
elseif(UNIX)
    file(GLOB_RECURSE SCR_FILES CONFIGURE_DEPENDS  "source/*.c")
    file(GLOB_RECURSE HDR_FILES CONFIGURE_DEPENDS  "include/*.h")
    set( CMAKE_CXX_COMPILER "/usr/bin/g++" )
    set( CMAKE_C_COMPILER "/usr/bin/gcc" )
    set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
endif()

project(SecOC)

find_package(Threads REQUIRED)


add_executable(SecOC ${SCR_FILES})

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(SecOC PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(SecOC "${CMAKE_THREAD_LIBS_INIT}")
endif()

foreach (_file ${HDR_FILES})
    cmake_path(REMOVE_FILENAME _file)

    target_include_directories(SecOC PUBLIC ${_file})
endforeach()


if(WIN32)
    target_compile_definitions(SecOC PUBLIC WINDOWS)
elseif(UNIX)
    target_compile_definitions(SecOC PUBLIC LINUX)
endif()


# Adding unit tests
include(CTest)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# Extract include directories from main target SecOC
set(headerDirs "")
get_target_property(headerDirs SecOC INCLUDE_DIRECTORIES)

# Print include directories one per line for cppchecke extension 
string(REPLACE ";"  "\n" cppincludes "${headerDirs}")
file(WRITE "${CMAKE_SOURCE_DIR}/build/cppcheck_includes.txt" ${cppincludes})

# Create static library for linking with gtest
add_library(SecOCLib STATIC ${SCR_FILES} ${HDR_FILES})
target_include_directories(SecOCLib PUBLIC ${headerDirs})

# Create shared library for linking with the GUI
add_library(SecOCLibShared SHARED ${SCR_FILES} ${HDR_FILES})
target_include_directories(SecOCLibShared PUBLIC ${headerDirs})

# Add our test folder cmakelists
add_subdirectory(test)







