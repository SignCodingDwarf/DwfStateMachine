cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "testDwfQueue")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR})

### CPPUnit content
find_path(cppunit_include_dir cppunit/TestCase.h /usr/local/include /usr/include)
find_library(cppunit_library cppunit ${CPPUNIT_INCLUDE_DIR}/../lib /usr/local/lib /usr/lib)

### Application Files Setup ###
# Locate all source files
file(

        GLOB_RECURSE

        source_files

        src/*.cpp

        src/*.c

)

# Add all header files
include_directories(include ${cppunit_include_dir})
include_directories(${CMAKE_CURRENT_LIST_DIR}/../../include)

# Locate all header files
file(

        GLOB_RECURSE

        header_files

        include/*.h

        include/*.hpp

)

# Generate binary
add_executable(

        ${PROJECT_NAME}

        ${source_files}

        ${header_files}
)

target_link_libraries(

	${PROJECT_NAME}

	${cppunit_library}

        pthread
	
	DwfStateMachine
)
