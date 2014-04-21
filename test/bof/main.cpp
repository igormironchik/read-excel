
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
#include <excel/bof.hpp>
#include <excel/record.hpp>

// unit test helper.
#include <test/helper/helper.hpp>
#include <test/stream/stream.hpp>


UNIT_TEST_START

	const char data[] = {
		0x09u, 0x08u, 0x10u, 0x00u,
		0x00u, 0x06u, 0x10u, 0x00u, 0xBBu, 0x0Du, 0xCCu, 0x07u,
		0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
	}; // data


	//
	// test_bof
	//

	UNIT_START( test_bof )

		TestStream stream( data, 20 );

		Excel::Record record( stream );

		Excel::BOF bof;
		bof.parse( record );

		CHECK_CONDITION( bof.version() == Excel::BOF::BIFF8 );
		CHECK_CONDITION( bof.type() == Excel::BOF::WorkSheet );

	UNIT_FINISH( test_bof )

UNIT_TEST_FINISH
