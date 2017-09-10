#STL processing
# top level cmake file

cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (osg-lsystem)

include_directories(${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src "$ENV{OSG_PATH}/include")

if (WIN32)
	link_directories(${CMAKE_BINARY_DIR}/lib "$ENV{OSG_PATH}/lib" )
else()
	link_directories(${CMAKE_BINARY_DIR}/lib "$ENV{OSG_PATH}")
endif()


IF (CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
	string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin )
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(CMAKE_DEBUG_POSTFIX "_Dbg")

add_subdirectory("${CMAKE_SOURCE_DIR}/src/application")


#DEBUG
#message(${EXECUTABLE_OUTPUT_PATH})
