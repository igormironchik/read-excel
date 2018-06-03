
project( sample )

set( SRC main.cpp )

file( COPY sample.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
    
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_executable( sample ${SRC} )
