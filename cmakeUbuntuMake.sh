#!/bin/bash

# file :  cmakeUbuntuMake.sh
# author : SignCodingDwarf
# version : 0.1
# date : 26 May 2020
# Script to run CMake application and set some compilation and build options

### Initialization
# Colors
helpCommandColor='\033[1;34m' #Help on command is printed in light blue
helpOptionsColor='\033[1;32m' #Help on options is printed in light green
helpCategoryColor="\033[1;33m" # Help options categories are printed in yellow
statusColor='\033[1;32m' #Status messages are printed in light green
NC='\033[0m' # No Color

# Control Variables
BUILD_DIR="build-dir"
TESTS_DIR=$(ls test)

# Help
Help()
{
	printf "Usage\n"
	printf "\n"
	printf "${helpCommandColor} ./cmakeUbuntuMake.sh [options]\n"
	printf "\n"
	
	printf "${NC}Options\n"
	printf "${helpCategoryColor}------ General Options ------\n"
	printf "${helpOptionsColor}-h ${NC}or ${helpOptionsColor}--help${NC}                   =  Print help and exit\n"
	printf "${helpOptionsColor}-c ${NC}or ${helpOptionsColor}--clean${NC}                  =  Clean CMake and compiling temporary files before compilation\n"
	printf "${helpOptionsColor}-s ${NC}or ${helpOptionsColor}--clean-stop${NC}             =  Clean CMake and compiling temporary files and stop\n"
}

# Clean
CleanTestDir()
{
    local testName="$1"
    rm -f "test/${testName}/${testName}"
}

Clean()
{
    printf "${statusColor}Cleaning main directory${NC}\n"
	rm -rf "${BUILD_DIR}"
	rm -f *.so 
	for testDir in ${TESTS_DIR}; do
        printf "${statusColor}Cleaning test directory ${testDir}${NC}\n"
	    CleanTestDir ${testDir}
	done
	
}

### Parse arguments values : 
for i in "$@" # for every input argument
do
	case $i in
		-h|--help) # if ask to render help
		    Help
		    exit 0
		;;
		-c|--clean) # remove temporary CMake and compile Files and produced libraries and binaries
            Clean
		;;
		-s|--clean-stop) # remove temporary CMake and compile Files and produced libraries and binaries then stop
            Clean
            exit 0
		;;
		*) #default nothing is done
		;;
	esac
done

### Creating storage directory
if [ ! -d "build_dir" ]; then #if temporary directory does not exist
  printf "${statusColor}Creating compile files directory ${NC}\n"
  mkdir $BUILD_DIR
fi

### Running CMake
printf "${statusColor}Running CMake ${NC}\n"
cmake -H. -B$BUILD_DIR -G "Unix Makefiles" $CMAKE_OPTIONS #set up cmake and generate makefile

### Compiling
printf "${statusColor}Compiling ${NC}\n"
cd $BUILD_DIR
make

