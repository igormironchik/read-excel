
/*!
	\file
	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2021 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// Excel include.
#include <read-excel/book.hpp>
#include <read-excel/exceptions.hpp>

// C++ include.
#include <cmath>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>


TEST_CASE( "test_complex" )
{
	{
		Excel::Book book( "test/data/sample.xls" );

		REQUIRE( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		REQUIRE( sheet->rowsCount() == 5 );
		REQUIRE( sheet->columnsCount() == 2 );

		REQUIRE( sheet->cell( 0, 0 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 0, 0 ).getString() == L"This is a string." );

		REQUIRE( sheet->cell( 1, 0 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 1, 0 ).getString() ==
			L"There is a double in the next cell: (1,2345)." );
		REQUIRE( sheet->cell( 1, 1 ).dataType() == Excel::Cell::DataType::Double );
		REQUIRE( std::fabs( sheet->cell( 1, 1 ).getDouble() - 1.2345 ) < 1E-9 );

		REQUIRE( sheet->cell( 2, 0 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 2, 0 ).getString() ==
			L"There is a double in the next cell: (5,4321)." );
		REQUIRE( sheet->cell( 2, 1 ).dataType() == Excel::Cell::DataType::Double );
		REQUIRE( std::fabs( sheet->cell( 2, 1 ).getDouble() - 5.4321 ) < 1E-9 );

		REQUIRE( sheet->cell( 3, 0 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 3, 0 ).getString() ==
			L"There is a formula in the next cell: (=B2+B3 = 6,6666)" );
		REQUIRE( sheet->cell( 3, 1 ).dataType() == Excel::Cell::DataType::Formula );
		REQUIRE( sheet->cell( 3, 1 ).getFormula().valueType() ==
			Excel::Formula::DoubleValue );
		REQUIRE( std::fabs( sheet->cell( 3, 1 ).getFormula().getDouble() - 6.6666 ) < 1E-9 );

		REQUIRE( sheet->cell( 4, 0 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 4, 0 ).getString() ==
			L"There is a date and time in the next cell:" );
		REQUIRE( book.dateMode() == Excel::Book::DateMode::Dec31_1899 );
		REQUIRE( sheet->cell( 4, 1 ).dataType() == Excel::Cell::DataType::Double );
		REQUIRE( std::fabs( sheet->cell( 4, 1 ).getDouble() - 43100.9999884259 ) < 1E-9 );
	}

	{
		Excel::Book book( "test/data/big.xls" );

		REQUIRE( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		REQUIRE( sheet->rowsCount() == 7992 );
		REQUIRE( sheet->columnsCount() == 26 );

		REQUIRE( sheet->cell( 0, 0 ).dataType() == Excel::Cell::DataType::Double );
		REQUIRE( std::fabs( sheet->cell( 0, 0 ).getDouble() - 1.0 ) < 1E-9 );
		REQUIRE( sheet->cell( 998, 25 ).dataType() == Excel::Cell::DataType::Double );
		REQUIRE( std::fabs( sheet->cell( 998, 25 ).getDouble() - 9.0 ) < 1E-9 );
		REQUIRE( sheet->cell( 7991, 25 ).dataType() == Excel::Cell::DataType::Double );
		REQUIRE( std::fabs( sheet->cell( 7991, 25 ).getDouble() - 9.0 ) < 1E-9 );
	}

	{
		Excel::Book book( "test/data/verybig.xls" );

		REQUIRE( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		REQUIRE( sheet->rowsCount() == 10000 );
		REQUIRE( sheet->columnsCount() == 26 );

		REQUIRE( sheet->cell( 0, 0 ).dataType() == Excel::Cell::DataType::Double );
		REQUIRE( std::fabs( sheet->cell( 0, 0 ).getDouble() - 1.0 ) < 1E-9 );
		REQUIRE( sheet->cell( 9999, 25 ).dataType() == Excel::Cell::DataType::Formula );
		REQUIRE( sheet->cell( 9999, 25 ).getFormula().valueType() == Excel::Formula::DoubleValue );
		REQUIRE( std::fabs( sheet->cell( 9999, 25 ).getFormula().getDouble() - 260000.0 ) < 1E-9 );

		REQUIRE( sheet->cell( 10000, 26 ).isNull() );

		REQUIRE_THROWS_AS( book.sheet( 1 ), Excel::Exception );
	}

	{
		Excel::Book book( "test/data/stringformula.xls" );

		REQUIRE( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		REQUIRE( sheet->rowsCount() == 2 );
		REQUIRE( sheet->columnsCount() == 3 );

		REQUIRE( sheet->cell( 0, 0 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 0, 0 ).getString() == L"str1" );

		REQUIRE( sheet->cell( 0, 1 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 0, 1 ).getString() == L"str2" );

		REQUIRE( sheet->cell( 0, 2 ).dataType() == Excel::Cell::DataType::Formula );
		REQUIRE( sheet->cell( 0, 2 ).getFormula().valueType() == Excel::Formula::StringValue );
		REQUIRE( sheet->cell( 0, 2 ).getFormula().getString() == L"str1str2" );

		REQUIRE( sheet->cell( 1, 0 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 1, 0 ).getString() == L"str1" );

		REQUIRE( sheet->cell( 1, 1 ).dataType() == Excel::Cell::DataType::String );
		REQUIRE( sheet->cell( 1, 1 ).getString() == L"str1" );

		REQUIRE( sheet->cell( 1, 2 ).dataType() == Excel::Cell::DataType::Formula );
		REQUIRE( sheet->cell( 1, 2 ).getFormula().valueType() == Excel::Formula::EmptyCell );
	}

	try {
		Excel::Book book( "nofile.xls" );

		REQUIRE( false );
	}
	catch( const Excel::Exception & x )
	{
		REQUIRE( x.whatAsWString() == L"Unable to open file : nofile.xls" );
	}
}
