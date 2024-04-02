
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/bof.hpp>
#include <read-excel/record.hpp>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>
#include <test/helper/helper.hpp>
#include <test/stream/stream.hpp>


const auto data = make_data(
	0x09u, 0x08u, 0x10u, 0x00u,
	0x00u, 0x06u, 0x10u, 0x00u, 0xBBu, 0x0Du, 0xCCu, 0x07u,
	0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
); // data


TEST_CASE( "test_bof" )
{
	TestStream stream( &data[ 0 ], 20 );

	Excel::Record record( stream );

	Excel::BOF bof;
	bof.parse( record );

	REQUIRE( bof.version() == Excel::BOF::BIFF8 );
	REQUIRE( bof.type() == Excel::BOF::WorkSheet );
}
