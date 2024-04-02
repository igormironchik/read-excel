
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/record.hpp>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>
#include <test/stream/stream.hpp>
#include <test/helper/helper.hpp>


const auto data = make_data(
	0xFCu, 0x00u, 0x13u, 0x00u,
	0x03u, 0x00u, 0x00u, 0x00u, 0x03u, 0x00u, 0x00u, 0x00u,
	0x10u, 0x00u, 0x00u,
	0x53u, 0x54u, 0x53u, 0x54u, 0x53u, 0x54u, 0x53u, 0x54u,

	0x3Cu, 0x00u, 0x11u, 0x00u,
	0x01u,
	0x53u, 0x00u, 0x54u, 0x00u, 0x53u, 0x00u, 0x54u, 0x00u,
	0x53u, 0x00u, 0x54u, 0x00u, 0x53u, 0x00u, 0x54u, 0x00u,

	0x3Cu, 0x00u, 0x13u, 0x00u,
	0x10u, 0x00u, 0x00u,
	0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u,
	0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u,

	0x3Cu, 0x00u, 0x23u, 0x00u,
	0x10u, 0x00u, 0x01u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u
);


TEST_CASE( "test_record" )
{
	TestStream teststream( &data[ 0 ], 106 );

	Excel::Record record( teststream );

	REQUIRE( record.code() == 0xFC );
	REQUIRE( record.length() == 0x5A );

	const std::vector< int32_t > & borders = record.borders();

	REQUIRE( borders[ 0 ] == 0x13 );
	REQUIRE( borders[ 1 ] == 0x24 );
	REQUIRE( borders[ 2 ] == 0x37 );
	REQUIRE( borders.size() == 3 );

	Excel::Stream & stream = record.dataStream();

	REQUIRE( stream.getByte() == (char) 0x03u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x03u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x10u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x01u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x53u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x54u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x10u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x10u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x01u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x51u );
	REQUIRE( stream.getByte() == (char) 0x00u );
	REQUIRE( stream.getByte() == (char) 0x52u );
	REQUIRE( stream.getByte() == (char) 0x00u );
}
