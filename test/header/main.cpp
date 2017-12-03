
/*!
	\file
	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2017 Igor Mironchik

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
#include <excel/compoundfile/header.hpp>
#include <excel/compoundfile/sat.hpp>
#include <excel/compoundfile/compoundfile_exceptions.hpp>
#include <excel/compoundfile/sat.hpp>
#include <excel/compoundfile/msat.hpp>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>

// TestDocument include.
#include <test/testdocument/document.hpp>

// C++ include.
#include <sstream>


TEST_CASE( "test_header" )
{
	{
		Document doc;

		CompoundFile::Header header( doc.stream() );

		REQUIRE( header.byteOrder() == Excel::Stream::LittleEndian );
		REQUIRE( header.sectorSize() == 512 );
		REQUIRE( header.shortSectorSize() == 64 );
		REQUIRE( header.sectorsInSAT() == 0x01 );
		REQUIRE( header.dirStreamSecID() == 0x01 );
		REQUIRE( header.streamMinSize() == 0x1000 );
		REQUIRE( header.ssatFirstSecID() == 0x1D );
		REQUIRE( header.sectorsInSSAT() == 0x01 );
		REQUIRE( header.msatFirstSecID() == CompoundFile::SecID::EndOfChain );
		REQUIRE( header.sectorsInMSAT() == 0x00 );

		CompoundFile::MSAT msat( header, doc.stream() );
		CompoundFile::SAT sat = msat.buildSAT();

		REQUIRE( sat.sat().size() == 128 );
		REQUIRE_THROWS_AS( sat.sectors( 129 ), CompoundFile::Exception );
		REQUIRE_THROWS_AS( sat.indexOfTheSecID( 129, sat.sat() ),
			CompoundFile::Exception );
	}

	{
		std::stringstream stream( std::ios::in | std::ios::out |
			std::ios::binary );

		const char headerData[] = {
			0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u
		};

		stream.write( headerData, 8 );

		REQUIRE_THROWS_AS( CompoundFile::Header header( stream ),
			CompoundFile::Exception );
	}
}
