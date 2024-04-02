
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/book.hpp>
#include <read-excel/exceptions.hpp>

// C++ include.
#include <cmath>
#include <chrono>
#include <iostream>

#include <xls.h>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>

using namespace std::chrono;
using namespace xls;


TEST_CASE( "test_complex" )
{
	auto start = high_resolution_clock::now();

	{
		Excel::Book book( "test/data/sample.xls" );

		REQUIRE( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		REQUIRE( sheet->rowsCount() == 5 );
		REQUIRE( sheet->columnsCount() == 2 );

		REQUIRE( sheet->cell( 0, 0 ).getString() == L"This is a string." );

		REQUIRE( sheet->cell( 1, 0 ).getString() ==
			L"There is a double in the next cell: (1,2345)." );

		REQUIRE( std::fabs( sheet->cell( 1, 1 ).getDouble() - 1.2345 ) < 1E-9 );

		REQUIRE( sheet->cell( 2, 0 ).getString() ==
			L"There is a double in the next cell: (5,4321)." );

		REQUIRE( std::fabs( sheet->cell( 2, 1 ).getDouble() - 5.4321 ) < 1E-9 );


		REQUIRE( sheet->cell( 3, 0 ).getString() ==
			L"There is a formula in the next cell: (=B2+B3 = 6,6666)" );

		REQUIRE( sheet->cell( 4, 0 ).getString() ==
			L"There is a date and time in the next cell:" );
	}

	{
		Excel::Book book( "test/data/big.xls" );

		REQUIRE( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		REQUIRE( sheet->rowsCount() == 7992 );
		REQUIRE( sheet->columnsCount() == 26 );


		REQUIRE( std::fabs( sheet->cell( 0, 0 ).getDouble() - 1.0 ) < 1E-9 );

		REQUIRE( std::fabs( sheet->cell( 998, 25 ).getDouble() - 9.0 ) < 1E-9 );

		REQUIRE( std::fabs( sheet->cell( 7991, 25 ).getDouble() - 9.0 ) < 1E-9 );
	}

	{
		Excel::Book book( "test/data/verybig.xls" );

		REQUIRE( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		REQUIRE( sheet->rowsCount() == 10000 );
		REQUIRE( sheet->columnsCount() == 26 );

		REQUIRE( std::fabs( sheet->cell( 0, 0 ).getDouble() - 1.0 ) < 1E-9 );
	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast< milliseconds > ( stop - start );

	std::cout << "read-excel execution time is " << duration.count() << " ms." << std::endl;
}

TEST_CASE( "test_complex_libxls" )
{
	auto start = high_resolution_clock::now();

	{
		xls_error_t error = LIBXLS_OK;
		xlsWorkBook * wb = xls_open_file( "test/data/sample.xls", "UTF-8", &error );

		if( wb == NULL )
		{
			printf("Error reading file: %s\n", xls_getError(error));
			REQUIRE( false );
		}

		REQUIRE( wb->sheets.count == 1 );

		xlsWorkSheet * sheet = xls_getWorkSheet( wb, 0 );
		error = xls_parseWorkSheet( sheet );

		REQUIRE( sheet->rows.lastrow == 4 );
		REQUIRE( sheet->rows.lastcol == 1 );

		xlsRow * row0 = xls_row( sheet, 0 );
		xlsCell * cell = &row0->cells.cell[ 0 ];

		REQUIRE( strcmp( cell->str, "This is a string." ) == 0 );

		xlsRow * row1 = xls_row( sheet, 1 );
		cell = &row1->cells.cell[ 0 ];

		REQUIRE( strcmp( cell->str,
			"There is a double in the next cell: (1,2345)." ) == 0 );

		cell = &row1->cells.cell[ 1 ];

		REQUIRE( std::fabs( cell->d - 1.2345 ) < 1E-9 );

		xlsRow * row2 = xls_row( sheet, 2 );
		cell = &row2->cells.cell[ 0 ];

		REQUIRE( strcmp( cell->str,
			"There is a double in the next cell: (5,4321)." ) == 0 );

		cell = &row2->cells.cell[ 1 ];

		REQUIRE( std::fabs( cell->d - 5.4321 ) < 1E-9 );

		xlsRow * row3 = xls_row( sheet, 3 );
		cell = &row3->cells.cell[ 0 ];

		REQUIRE( strcmp( cell->str,
			"There is a formula in the next cell: (=B2+B3 = 6,6666)" ) == 0 );

		xlsRow * row4 = xls_row( sheet, 4 );
		cell = &row4->cells.cell[ 0 ];

		REQUIRE( strcmp( cell->str,
			"There is a date and time in the next cell:" ) == 0 );

		xls_close_WS( sheet );
		xls_close_WB( wb );
	}

	{
		xls_error_t error = LIBXLS_OK;
		xlsWorkBook * wb = xls_open_file( "test/data/big.xls", "UTF-8", &error );

		if( wb == NULL )
		{
			printf("Error reading file: %s\n", xls_getError(error));
			REQUIRE( false );
		}

		REQUIRE( wb->sheets.count == 1 );

		xlsWorkSheet * sheet = xls_getWorkSheet( wb, 0 );
		error = xls_parseWorkSheet( sheet );

		REQUIRE( sheet->rows.lastrow == 7991 );
		REQUIRE( sheet->rows.lastcol == 25 );

		xlsRow * row0 = xls_row( sheet, 0 );
		xlsCell * cell = &row0->cells.cell[ 0 ];

		REQUIRE( std::fabs( cell->d - 1.0 ) < 1E-9 );

		xlsRow * row998 = xls_row( sheet, 998 );
		cell = &row998->cells.cell[ 25 ];

		REQUIRE( std::fabs( cell->d - 9.0 ) < 1E-9 );

		xlsRow * row7991 = xls_row( sheet, 7991 );
		cell = &row7991->cells.cell[ 25 ];

		REQUIRE( std::fabs( cell->d - 9.0 ) < 1E-9 );

		xls_close_WS( sheet );
		xls_close_WB( wb );
	}

	{
		xls_error_t error = LIBXLS_OK;
		xlsWorkBook * wb = xls_open_file( "test/data/verybig.xls", "UTF-8", &error );

		if( wb == NULL )
		{
			printf("Error reading file: %s\n", xls_getError(error));
			REQUIRE( false );
		}

		REQUIRE( wb->sheets.count == 1 );

		xlsWorkSheet * sheet = xls_getWorkSheet( wb, 0 );
		error = xls_parseWorkSheet( sheet );

		REQUIRE( sheet->rows.lastrow == 9999 );
		REQUIRE( sheet->rows.lastcol == 25 );

		xlsRow * row0 = xls_row( sheet, 0 );
		xlsCell * cell = &row0->cells.cell[ 0 ];

		REQUIRE( std::fabs( cell->d - 1.0 ) < 1E-9 );

		xls_close_WS( sheet );
		xls_close_WB( wb );
	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast< milliseconds > ( stop - start );

	std::cout << "libxls execution time is " << duration.count() << " ms." << std::endl;
}
