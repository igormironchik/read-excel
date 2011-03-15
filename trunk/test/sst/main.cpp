
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
#include <excel/h/sst.hpp>
#include <excel/h/record.hpp>

// unit test helper.
#include <test/helper/helper.hpp>
#include <test/stream/h/stream.hpp>


UNIT_TEST_START

	const char data[] = {
		0xFC, 0x00, 0x13, 0x00,
		0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x10, 0x00, 0x00,
		0x53, 0x54, 0x53, 0x54, 0x53, 0x54, 0x53, 0x54,

		0x3C, 0x00, 0x11, 0x00,
		0x01,
		0x53, 0x00, 0x54, 0x00, 0x53, 0x00, 0x54, 0x00,
		0x53, 0x00, 0x54, 0x00, 0x53, 0x00, 0x54, 0x00,

		0x3C, 0x00, 0x13, 0x00,
		0x10, 0x00, 0x00,
		0x51, 0x52, 0x51, 0x52, 0x51, 0x52, 0x51, 0x52,
		0x51, 0x52, 0x51, 0x52, 0x51, 0x52, 0x51, 0x52,

		0x3C, 0x00, 0x23, 0x00,
		0x10, 0x00, 0x01,
		0x51, 0x00, 0x52, 0x00, 0x51, 0x00, 0x52, 0x00,
		0x51, 0x00, 0x52, 0x00, 0x51, 0x00, 0x52, 0x00,
		0x51, 0x00, 0x52, 0x00, 0x51, 0x00, 0x52, 0x00,
		0x51, 0x00, 0x52, 0x00, 0x51, 0x00, 0x52, 0x00
	}; // data


	//
	// test_sst
	//

	UNIT_START( test_sst )

		TestStream testStream( data, 106 );

		Excel::Record record( testStream );

		std::vector< std::wstring > strings =
			Excel::SharedStringTable::parse( record );

		CHECK_CONDITION( strings.size() == 3 );

		CHECK_CONDITION( strings[ 0 ] == L"STSTSTSTSTSTSTST" );
		CHECK_CONDITION( strings[ 1 ] == L"QRQRQRQRQRQRQRQR" );
		CHECK_CONDITION( strings[ 2 ] == L"QRQRQRQRQRQRQRQR" );

	UNIT_FINISH( test_sst )

UNIT_TEST_FINISH
