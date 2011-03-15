
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
#include <excel/compoundfile/h/header.hpp>
#include <excel/compoundfile/h/sat.hpp>
#include <excel/compoundfile/h/exceptions.hpp>

// unit test helper.
#include <test/helper/helper.hpp>

// TestDocument include.
#include <test/testdocument/h/document.hpp>

// C++ include.
#include <sstream>


UNIT_TEST_START

	//
	// test_header
	//

	UNIT_START( test_header )

	{
		Document doc;

		CompoundFile::Header header( doc.stream() );

		CHECK_CONDITION( header.byteOrder() == Excel::Stream::LittleEndian );
		CHECK_CONDITION( header.sectorSize() == 512 );
		CHECK_CONDITION( header.shortSectorSize() == 64 );
		CHECK_CONDITION( header.sectorsInSAT() == 0x01 );
		CHECK_CONDITION( header.dirStreamSecID() == 0x01 );
		CHECK_CONDITION( header.streamMinSize() == 0x1000 );
		CHECK_CONDITION( header.ssatFirstSecID() == 0x1D );
		CHECK_CONDITION( header.sectorsInSSAT() == 0x01 );
		CHECK_CONDITION( header.msatFirstSecID() == CompoundFile::SecID::EndOfChain );
		CHECK_CONDITION( header.sectorsInMSAT() == 0x00 );
	}

	{
		std::stringstream stream( std::ios::in | std::ios::out |
			std::ios::binary );

		const char headerData[] = {
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

		stream.write( headerData, 8 );

		CHECK_THROW( CompoundFile::Exception,
			{
				CompoundFile::Header header( stream );
			} )
	}

	UNIT_FINISH( test_header )

UNIT_TEST_FINISH
