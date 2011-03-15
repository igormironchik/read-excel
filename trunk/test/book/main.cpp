
/*!
	\file
	\author Igor P. Mironchik (imironchick at gmail dot com).

	Copyright (c) 2011 Igor P. Mironchik

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
#include <excel/h/book.hpp>

// C++ include.
#include <cmath>

// unit test helper.
#include <test/helper/helper.hpp>


UNIT_TEST_START

	//
	// test_book
	//

	UNIT_START( test_book )

		Excel::Book book( L"test/data/test.xls" );

		CHECK_CONDITION( book.sheetsCount() == 1 );

		Excel::Sheet * sheet = book.sheet( 0 );

		CHECK_CONDITION( sheet->rowsCount() == 3 );
		CHECK_CONDITION( sheet->columnsCount() == 4 );

		CHECK_CONDITION( sheet->cell( 0, 0 ).getString() == L"String #1" );
		CHECK_CONDITION( sheet->cell( 1, 0 ).getString() == L"String #2" );
		CHECK_CONDITION( sheet->cell( 2, 0 ).getString() == L"String #3" );

		CHECK_CONDITION( std::fabs( sheet->cell( 0, 1 ).getDouble() - 1.0 ) < 1E-9 );
		CHECK_CONDITION( std::fabs( sheet->cell( 1, 1 ).getDouble() - 2.0 ) < 1E-9 );
		CHECK_CONDITION( std::fabs( sheet->cell( 2, 1 ).getDouble() - 3.0 ) < 1E-9 );

		CHECK_CONDITION( std::fabs( sheet->cell( 0, 2 ).getDouble() - 0.1 ) < 1E-9 );
		CHECK_CONDITION( std::fabs( sheet->cell( 1, 2 ).getDouble() - 0.2 ) < 1E-9 );
		CHECK_CONDITION( std::fabs( sheet->cell( 2, 2 ).getDouble() - 0.3 ) < 1E-9 );

		CHECK_CONDITION( std::fabs( sheet->cell( 0, 3 ).getFormula().getDouble() - 1.1 ) < 1E-9 );
		CHECK_CONDITION( std::fabs( sheet->cell( 1, 3 ).getFormula().getDouble() - 2.2 ) < 1E-9 );
		CHECK_CONDITION( std::fabs( sheet->cell( 2, 3 ).getFormula().getDouble() - 3.3 ) < 1E-9 );

	UNIT_FINISH( test_book )

UNIT_TEST_FINISH
