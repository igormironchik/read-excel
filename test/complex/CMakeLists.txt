
project( test.complex )

if( ENABLE_COVERAGE )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage" )
	set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage" )
endif( ENABLE_COVERAGE )

set( SRC main.cpp )
    
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/../.. )

add_executable( test.complex ${SRC} )

add_test( NAME test.complex
	COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test.complex
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../.. )

if( BUILD_BENCHMARK )
	add_executable( test.complex.benchmark benchmark.cpp )
	target_link_libraries( test.complex.benchmark PRIVATE xlsreader )
endif( BUILD_BENCHMARK )
