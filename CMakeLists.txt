
cmake_minimum_required( VERSION 3.1 )

set( EXCEL_VERSION "1.1.4" )

option( BUILD_EXAMPLES "Build examples? Default ON." ON )
option( BUILD_TESTS "Build tests? Default ON." ON )

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Release"
		CACHE STRING "Choose the type of build."
		FORCE)
endif( NOT CMAKE_BUILD_TYPE )

SET( CMAKE_CXX_STANDARD 14 )

SET( CMAKE_CXX_STANDARD_REQUIRED ON )

project( readexcel )

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

if( ${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME} )

	if( BUILD_EXAMPLES )
		add_subdirectory( sample )
	endif()

	if( BUILD_TESTS )
		enable_testing()

		add_subdirectory( test )
	endif()
	
	add_library( excel INTERFACE )

	install( DIRECTORY excel
		DESTINATION include
	)

	install( TARGETS excel
		EXPORT excel-targets
		RUNTIME DESTINATION bin
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
		INCLUDES DESTINATION include
	)

	install( EXPORT excel-targets
		DESTINATION lib/cmake/excel
	)

	include( CMakePackageConfigHelpers )

	write_basic_package_version_file(
		"${CMAKE_CURRENT_BINARY_DIR}/excel-config-version.cmake"
		VERSION ${EXCEL_VERSION}
		COMPATIBILITY AnyNewerVersion
	)

	configure_package_config_file( excel-config.cmake.in
		"${CMAKE_CURRENT_BINARY_DIR}/excel-config.cmake"
		INSTALL_DESTINATION lib/cmake/excel )

	install( FILES ${PROJECT_BINARY_DIR}/excel-config.cmake
			${PROJECT_BINARY_DIR}/excel-config-version.cmake
		DESTINATION lib/cmake/excel
	)
else()

	set( excel_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE )

endif( ${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME} )
