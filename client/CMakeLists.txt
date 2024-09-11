# CMakeList.txt : CMake project for networking-tcp, include source and define
# project specific logic here.
#
project(client)
find_package(Boost REQUIRED)
include_directories(PUBLIC ${Boost_INCLUDE_DIRS})
add_executable(client src/main.cpp src/client.cpp)
include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 14)

target_link_libraries(client PRIVATE networking)
