project(OpenFly)

cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

#Add compiling file
file(GLOB_RECURSE EXE_SRC src/*.cpp)

#Add executeable file and build dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)
add_executable(${PROJECT_NAME} ${EXE_SRC})

#Add pthread library
#find_package(Thread)
target_link_libraries(${PROJECT_NAME} pthread)

#Add boost library and include dir
set(BOOST_ROOT /home/sd/boost_1_60_0)
find_package( Boost REQUIRED COMPONENTS system thread )
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
