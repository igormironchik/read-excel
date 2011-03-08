
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
#include <excel/h/formula.hpp>
#include <excel/h/record.hpp>
#include <excel/h/string.hpp>

// unit test helper.
#include <test/helper/helper.hpp>
#include <test/stream/h/stream.hpp>


UNIT_TEST_START

	const char data1[] = {
		0x06, 0x00, 0x16, 0x00,
		0x01, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}; // data1

	const char data2[] = {
		0x06, 0x00, 0x16, 0x00,
		0x02, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}; // data2

	const char data3[] = {
		0x06, 0x00, 0x16, 0x00,
		0x03, 0x00, 0x04, 0x00, 0x00, 0x00,
		0x02, 0x00, 0x2A, 0x00, 0x00, 0x00, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}; // data3

	const char data4[] = {
		0x06, 0x00, 0x16, 0x00,
		0x04, 0x00, 0x05, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		0x07, 0x02, 0x12, 0x00,
		0x0F, 0x00, 0x00, 0x74, 0x68, 0x69, 0x73, 0x20,
		0x69, 0x73, 0x20, 0x72, 0x65, 0x64, 0x20, 0x69,
		0x6E, 0x6B
	}; // data4

	const char data5[] = {
		0x06, 0x00, 0x16, 0x00,
		0x02, 0x00, 0x03, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	}; // data5


	//
	// test_formula
	//

	UNIT_START( test_formula )

		union {
			double asDouble;
			long long asLongLong;
		} un;

		{
			TestStream stream( data1, 26 );

			Excel::Record record( stream );

			Excel::Formula formula( record );

			CHECK_CONDITION( formula.valueType() == Excel::Formula::DoubleValue );
			CHECK_CONDITION( formula.getRow() == 0x01 );
			CHECK_CONDITION( formula.getColumn() == 0x02 );

			un.asLongLong = 0x0102030405060708;

			CHECK_CONDITION( formula.getDouble() == un.asDouble );
		}

		{
			TestStream stream( data2, 26 );

			Excel::Record record( stream );

			Excel::Formula formula( record );

			CHECK_CONDITION( formula.valueType() == Excel::Formula::BooleanValue );
			CHECK_CONDITION( formula.getRow() == 0x02 );
			CHECK_CONDITION( formula.getColumn() == 0x03 );

			un.asLongLong = 0xFFFF000000010001;

			CHECK_CONDITION( formula.getBoolean() == true );
		}

		{
			TestStream stream( data3, 26 );

			Excel::Record record( stream );

			Excel::Formula formula( record );

			CHECK_CONDITION( formula.valueType() == Excel::Formula::ErrorValue );
			CHECK_CONDITION( formula.getRow() == 0x03 );
			CHECK_CONDITION( formula.getColumn() == 0x04 );

			un.asLongLong = 0xFFFF0000002A0002;

			CHECK_CONDITION( formula.getErrorValue() == Excel::Formula::NA );
		}

		{
			TestStream stream( data4, 48 );

			Excel::Record record( stream );

			Excel::Formula formula( record );

			Excel::Record stringRecord( stream );
			std::vector< int > borders;

			formula.setString( Excel::loadString( stringRecord.dataStream(),
				borders ) );

			CHECK_CONDITION( formula.valueType() == Excel::Formula::StringValue );
			CHECK_CONDITION( formula.getRow() == 0x04 );
			CHECK_CONDITION( formula.getColumn() == 0x05 );

			un.asLongLong = 0xFFFF000000000000;

			CHECK_CONDITION( formula.getString() == L"this is red ink" );
		}

		{
			TestStream stream( data5, 26 );

			Excel::Record record( stream );

			Excel::Formula formula( record );

			CHECK_CONDITION( formula.valueType() == Excel::Formula::BooleanValue );
			CHECK_CONDITION( formula.getRow() == 0x02 );
			CHECK_CONDITION( formula.getColumn() == 0x03 );

			un.asLongLong = 0xFFFF000000010001;

			CHECK_CONDITION( formula.getBoolean() == false );
		}

	UNIT_FINISH( test_formula )

UNIT_TEST_FINISH
