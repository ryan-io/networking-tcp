# CMakeList.txt : CMake project for networking-tcp, include source and define
# project specific logic here.
#
project(networking)
# project commands
include_directories(networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include) # use '${CMAKE_CURRENT_SOURCE_DIR}' for library headers
add_library(networking src/networking-tcp.cpp) # do not include header files

# library commands
find_package(Boost REQUIRED)
include_directories(PUBLIC ${Boost_INCLUDE_DIRS})

# libraries require target_include_directors for include and src
#	this allows us to include the library header files in the project, but will not
#	expose the implementations
target_include_directories(networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE src)