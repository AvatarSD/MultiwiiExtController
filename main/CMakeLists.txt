
#Specify the cross compiler
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)


project(OpenFly)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

#Add build dir and turn on verbose gcc output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SKIP_RULE_DEPENDENCY ON)

#Add compiling file
file(GLOB_RECURSE EXE_SRC src/*.cpp)

#Main executable file
add_executable(${PROJECT_NAME} ${EXE_SRC})

#Add pthread library
target_link_libraries(${PROJECT_NAME} pthread)

#Add boost library and include dir
set(BOOST_ROOT /home/sd/boost_1_60_0)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage_arm/lib/)

find_package( Boost REQUIRED COMPONENTS system thread )
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
