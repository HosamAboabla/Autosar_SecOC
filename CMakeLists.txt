cmake_minimum_required(VERSION 3.22) # this is to check if the version of cmake is older than 3.22 or newer
project(SECOC)  # this is the name of the project
add_executable(a source/) #a is the name of our executable, source files are the dependencies
target_include_directories(a PUBLIC include/) # to include the header files 
