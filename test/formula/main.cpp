
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
#include <excel/formula.hpp>
#include <excel/record.hpp>
#include <excel/string.hpp>

// unit test helper.
#include <test/helper/helper.hpp>
#include <test/stream/stream.hpp>


UNIT_TEST_START

	const char data1[] = {
		0x06u, 0x00u, 0x16u, 0x00u,
		0x01u, 0x00u, 0x02u, 0x00u, 0x00u, 0x00u,
		0x08u, 0x07u, 0x06u, 0x05u, 0x04u, 0x03u, 0x02u, 0x01u,
		0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
	}; // data1

	const char data2[] = {
		0x06u, 0x00u, 0x16u, 0x00u,
		0x02u, 0x00u, 0x03u, 0x00u, 0x00u, 0x00u,
		0x01u, 0x00u, 0x01u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu,
		0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
	}; // data2

	const char data3[] = {
		0x06u, 0x00u, 0x16u, 0x00u,
		0x03u, 0x00u, 0x04u, 0x00u, 0x00u, 0x00u,
		0x02u, 0x00u, 0x2Au, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu,
		0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
	}; // data3

	const char data4[] = {
		0x06u, 0x00u, 0x16u, 0x00u,
		0x04u, 0x00u, 0x05u, 0x00u, 0x00u, 0x00u,
		0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu,
		0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,

		0x07u, 0x02u, 0x12u, 0x00u,
		0x0Fu, 0x00u, 0x00u, 0x74u, 0x68u, 0x69u, 0x73u, 0x20u,
		0x69u, 0x73u, 0x20u, 0x72u, 0x65u, 0x64u, 0x20u, 0x69u,
		0x6Eu, 0x6Bu
	}; // data4

	const char data5[] = {
		0x06u, 0x00u, 0x16u, 0x00u,
		0x02u, 0x00u, 0x03u, 0x00u, 0x00u, 0x00u,
		0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu,
		0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
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
