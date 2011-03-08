
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
	};


	//
	// test_record
	//

	UNIT_START( test_record )

		TestStream teststream( data, 106 );

		Excel::Record record( teststream );

		CHECK_CONDITION( record.code() == 0xFC );
		CHECK_CONDITION( record.length() == 0x5A );

		const std::vector< int > & borders = record.borders();

		CHECK_CONDITION( borders[ 0 ] == 0x13 );
		CHECK_CONDITION( borders[ 1 ] == 0x24 );
		CHECK_CONDITION( borders[ 2 ] == 0x37 );
		CHECK_CONDITION( borders.size() == 3 );

		Excel::Stream & stream = record.dataStream();

		CHECK_CONDITION( stream.getByte() == (char) 0x03 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x03 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x10 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x01 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x53 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x54 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x10 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x10 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x01 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x51 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );
		CHECK_CONDITION( stream.getByte() == (char) 0x52 );
		CHECK_CONDITION( stream.getByte() == (char) 0x00 );

	UNIT_FINISH( test_record )

UNIT_TEST_FINISH
