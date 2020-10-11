cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "DwfStateMachine")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR})

### Application Files Setup ###
# Locate all source files
file(

        GLOB_RECURSE

        source_files

        src/*.cpp

        src/*.c

)

# Add all header files
include_directories(include)

# Locate all header files
file(

        GLOB_RECURSE

        header_files

        include/*.h

        include/*.hpp

)
set(header_install ${header_files})

# Generate dynamic library
add_library(

        ${PROJECT_NAME}

        SHARED

        ${source_files}

        ${header_files}
)

target_link_libraries(

        ${PROJECT_NAME}

        pthread
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# List test directories
file(

        GLOB

        tests_folders

        ${CMAKE_CURRENT_LIST_DIR}/test/*

)

# Build all tests
foreach(folder ${tests_folders})
    add_subdirectory(${folder})
endforeach(folder)
