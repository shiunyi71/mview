cmake_minimum_required( VERSION 3.6.0 )
project( MViewParser )
include_directories( include )
include_directories( vendors/json/src )
include_directories( vendors/glm )
# Set all .cpp files to variable SOURCES
file( GLOB SOURCES "src/*.cpp")
add_executable( MViewParser ${SOURCES} )
