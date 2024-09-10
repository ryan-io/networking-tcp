# CMakeList.txt : CMake project for networking-tcp, include source and define
# project specific logic here.
#
project(server)
#each project will also require boost if a library has a dependency on it
find_package(Boost REQUIRED)
include_directories(PUBLIC ${Boost_INCLUDE_DIRS})
# Add source to this project's executable.
add_executable(server src/main.cpp src/server.cpp)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # for 'server' include files
target_link_libraries(server PRIVATE networking)
set(CMAKE_CXX_STANDARD 14)