project(aRPiGi)

cmake_minimum_required(VERSION 2.8)
add_definitions(-DARM9)
set(EXE_NAME aRPiGi)

add_executable(${EXE_NAME} source/main.c )

target_link_libraries(${EXE_NAME} nds9)
set_target_properties(${EXE_NAME}
	PROPERTIES
	LINK_FLAGS -specs=ds_arm9.specs
	COMPILER_FLAGS "-mthumb -mthumb-interwork")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
include(ndsmacros)
	
objcopy_file(${EXE_NAME})
ndstool_file(${EXE_NAME})
 
set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_SUPPRESS_REGENERATION TRUE)
#set(CMAKE_USE_RELATIVE_PATHS TRUE)

#add_subdirectory(arm7)
#add_subdirectory(arm9)