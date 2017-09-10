#STL_processing library
#cmake file for  application


file(GLOB_RECURSE L_SYSTEM_APP_HEADER "${CMAKE_CURRENT_SRC_DIR}" *.h)
file(GLOB_RECURSE L_SYSTEM_APP_SRC "${CMAKE_CURRENT_SRC_DIR}" *.cpp)

add_executable(LSystemDemonstrator ${L_SYSTEM_APP_HEADER} ${L_SYSTEM_APP_SRC})

set(CMAKE_DEBUG_POSTFIX "d")

target_link_libraries(STLProcessingDemonstrator
		debug osg${CMAKE_DEBUG_POSTFIX} optimized osg
		debug osgDB${CMAKE_DEBUG_POSTFIX} optimized osgDB
		debug osgViewer${CMAKE_DEBUG_POSTFIX} optimized osgViewer
		debug osgGA${CMAKE_DEBUG_POSTFIX} optimized osgGA
		debug osgText${CMAKE_DEBUG_POSTFIX} optimized osgText
		debug osgUtil${CMAKE_DEBUG_POSTFIX} optimized osgUtil
		debug osgVolume${CMAKE_DEBUG_POSTFIX} optimized osgVolume
		debug osgManipulator${CMAKE_DEBUG_POSTFIX} optimized osgManipulator
		debug OpenThreads${CMAKE_DEBUG_POSTFIX} optimized OpenThreads
		
		debug STLProcessing optimized STLProcessing
				
	)
