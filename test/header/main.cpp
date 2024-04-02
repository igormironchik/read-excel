
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/compoundfile/header.hpp>
#include <read-excel/compoundfile/sat.hpp>
#include <read-excel/compoundfile/compoundfile_exceptions.hpp>
#include <read-excel/compoundfile/sat.hpp>
#include <read-excel/compoundfile/msat.hpp>

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
