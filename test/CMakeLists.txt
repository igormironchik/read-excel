
project( tests )

file( COPY data/big.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )
file( COPY data/datetime.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )
file( COPY data/sample.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )
file( COPY data/stringformula.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )
file( COPY data/test.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )
file( COPY data/verybig.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )
file( COPY data/old.xls
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data )

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	add_subdirectory( testdocument )
	add_subdirectory( header )
endif()

add_subdirectory( stream )
add_subdirectory( bof )
add_subdirectory( book )
add_subdirectory( cell )
add_subdirectory( complex )
add_subdirectory( compoundfile )
add_subdirectory( datetime )
add_subdirectory( formula )
add_subdirectory( record )
add_subdirectory( sst )
add_subdirectory( string )
