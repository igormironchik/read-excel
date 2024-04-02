
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/cell.hpp>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>


TEST_CASE( "test_cell" )
{
	Excel::Cell cell;

	cell.setData( 0.123456789 );

	REQUIRE( cell.getDouble() == 0.123456789 );

	cell.setData( L"1234567890" );

	REQUIRE( cell.getString() == L"1234567890" );

	cell.setData( 1234.0 );

	REQUIRE( cell.getDouble() == 1234.0 );

	cell.setData( L"qwerty" );

	REQUIRE( cell.getString() == L"qwerty" );

}
