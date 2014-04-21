
/*!
	\file
	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2014 Igor Mironchik

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
#include <excel/cell.hpp>

// unit test helper.
#include <test/helper/helper.hpp>


UNIT_TEST_START

	//
	// test_cell
	//

	UNIT_START( test_cell )

		Excel::Cell cell;

		cell.setData( 0.123456789 );

		CHECK_CONDITION( cell.getDouble() == 0.123456789 );

		cell.setData( L"1234567890" );

		CHECK_CONDITION( cell.getString() == L"1234567890" );

		cell.setData( 1234.0 );

		CHECK_CONDITION( cell.getDouble() == 1234.0 );

		cell.setData( L"qwerty" );

		CHECK_CONDITION( cell.getString() == L"qwerty" );

	UNIT_FINISH( test_cell )

UNIT_TEST_FINISH
