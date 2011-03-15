
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
#include <excel/h/string.hpp>

// C++ include.
#include <vector>

// unit test helper.
#include <test/helper/helper.hpp>
#include <test/stream/h/stream.hpp>


UNIT_TEST_START

	const char data[] = {
		0x0F, 0x00, 0x08, 0x02, 0x00, 0x74, 0x68, 0x69,
		0x73, 0x20, 0x69, 0x73, 0x20, 0x72, 0x65, 0x64,
		0x20, 0x69, 0x6E, 0x6B, 0x08, 0x00, 0x06, 0x00,
		0x0B, 0x00, 0x05, 0x00,

		0x0F, 0x00, 0x00, 0x74, 0x68, 0x69, 0x73, 0x20,
		0x69, 0x73, 0x20, 0x72, 0x65, 0x64, 0x20, 0x69,
		0x6E, 0x6B,

		0x0F, 0x00, 0x01, 0x74, 0x00, 0x68, 0x00, 0x69,
		0x00, 0x73, 0x00, 0x20, 0x00, 0x69, 0x00, 0x73,
		0x00, 0x20, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64,
		0x00, 0x20, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x6B,
		0x00,

		0x0F, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x74,
		0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x72,
		0x65, 0x64, 0x20, 0x69, 0x6E, 0x6B, 0x00, 0x00,
		0x00, 0x00,

		0x0F, 0x00, 0x0C, 0x02, 0x00, 0x04, 0x00, 0x00,
		0x00, 0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73,
		0x20, 0x72, 0x65, 0x64, 0x20, 0x69, 0x6E, 0x6B,
		0x08, 0x00, 0x06, 0x00, 0x0B, 0x00, 0x05, 0x00,
		0x00, 0x00, 0x00, 0x00,

		0x0F, 0x00, 0x00, 0x74, 0x68, 0x69, 0x73, 0x20,
		0x69, 0x73, 0x20, 0x72, 0x65, 0x64, 0x20, 0x69,
		0x6E, 0x6B
	}; // data


	//
	// test_string
	//

	UNIT_START( test_string )

		std::vector< int > borders;
		std::wstring str;

		TestStream stream( data, 159 );

		str = Excel::loadString( stream, borders );

		CHECK_CONDITION( str == L"this is red ink" );

		str = Excel::loadString( stream, borders );

		CHECK_CONDITION( str == L"this is red ink" );

		str = Excel::loadString( stream, borders );

		CHECK_CONDITION( str == L"this is red ink" );

		str = Excel::loadString( stream, borders );

		CHECK_CONDITION( str == L"this is red ink" );

		str = Excel::loadString( stream, borders );

		CHECK_CONDITION( str == L"this is red ink" );

		str = Excel::loadString( stream, borders );

		CHECK_CONDITION( str == L"this is red ink" );

	UNIT_FINISH( test_string )

UNIT_TEST_FINISH
