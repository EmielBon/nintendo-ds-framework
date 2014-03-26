macro(OBJCOPY_FILE EXE_NAME)
	set(FO ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.bin)
	set(FI ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME})
	message(STATUS ${FO})
	add_custom_command(
		OUTPUT "${FO}"
		COMMAND ${CMAKE_OBJCOPY}
		ARGS -O binary ${FI} ${FO}
		DEPENDS ${FI})
	get_filename_component(TGT "${EXE_NAME}" NAME)
	add_custom_target("TargetObjCopy_${TGT}" ALL DEPENDS ${FO} VERBATIM)
	get_directory_property(extra_clean_files ADDITIONAL_MAKE_CLEAN_FILES)
	set_directory_properties(
		PROPERTIES
		ADDITIONAL_MAKE_CLEAN_FILES "${extra_clean_files};${FO}")
	set_source_files_properties("${FO}" PROPERTIES GENERATED TRUE)
endmacro(OBJCOPY_FILE)

if(NOT NDSTOOL_EXE)
	message(STATUS "Looking for arm-eabi-objcopy")
	find_program(NDSTOOL_EXE ndstool ${DEVKITARM}/bin)
	if(NDSTOOL_EXE)
		message(STATUS "Looking for arm-eabi-objcopy -- ${NDSTOOL_EXE}")
	endif(NDSTOOL_EXE)
endif(NOT NDSTOOL_EXE)

if(NDSTOOL_EXE)
	macro(NDSTOOL_FILE EXE_NAME)
		set(FO ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.nds)
		set(I9 ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.bin)
		add_custom_command(
			OUTPUT ${FO}
			COMMAND ${NDSTOOL_EXE}
			ARGS -c ${FO} -9 ${I9}
			MAIN_DEPENDENCY ${I9}
		)
		get_filename_component(TGT "${EXE_NAME}" NAME)
		add_custom_target("Target9_${TGT}" ALL DEPENDS ${FO} VERBATIM)
		get_directory_property(extra_clean_files ADDITIONAL_MAKE_CLEAN_FILES)
		set_directory_properties(
			PROPERTIES
			ADDITIONAL_MAKE_CLEAN_FILES "${extra_clean_files};${FO}")
		set_source_files_properties(${FO} PROPERTIES GENERATED TRUE)
	endmacro(NDSTOOL_FILE)
endif(NDSTOOL_EXE)