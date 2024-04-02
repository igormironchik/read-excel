
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/book.hpp>
#include <read-excel/sheet.hpp>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>


TEST_CASE( "test_book" )
{
	Excel::Book book( "test/data/datetime.xls" );

	REQUIRE( book.sheetsCount() == 1 );

	Excel::Sheet * sheet = book.sheet( 0 );

	REQUIRE( sheet->rowsCount() == 1 );
	REQUIRE( sheet->columnsCount() == 1 );

	REQUIRE( std::fabs( sheet->cell( 0, 0 ).getDouble() - 43100.9999884259 ) < 1E-9 );
}
