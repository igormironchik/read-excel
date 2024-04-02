
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/compoundfile/compoundfile.hpp>
#include <read-excel/compoundfile/compoundfile_exceptions.hpp>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>


//
// test_directory
//

TEST_CASE( "test_directory" )
{
	CompoundFile::File file( "./test/data/test.xls" );

	{
		CompoundFile::Directory dir = file.directory( L"Workbook" );

		REQUIRE( dir.name() == L"Workbook" );
		REQUIRE( dir.type() == CompoundFile::Directory::UserStream );
		REQUIRE( dir.streamSecID() == 0x02 );
		REQUIRE( dir.streamSize() == 0x3480 );
		REQUIRE( dir.rightChild() == 0xFFFFFFFF );
		REQUIRE( dir.leftChild() == 0x04 );
		REQUIRE( dir.rootNode() == 0xFFFFFFFF );
	}

	{
		const wchar_t data[] = {
			0x01, 0x43, 0x6F, 0x6D, 0x70, 0x4F, 0x62, 0x6A, 0x00
		};

		CompoundFile::Directory dir = file.directory( data );

		REQUIRE( dir.name() == data );
		REQUIRE( dir.type() == CompoundFile::Directory::UserStream );
		REQUIRE( dir.streamSecID() == 0x08 );
		REQUIRE( dir.streamSize() == 0x6D );
		REQUIRE( dir.rightChild() == 0xFFFFFFFF );
		REQUIRE( dir.leftChild() == 0xFFFFFFFF );
		REQUIRE( dir.rootNode() == 0xFFFFFFFF );
	}

	{
		const wchar_t data[] = {
			0x05, 0x44, 0x6F, 0x63, 0x75, 0x6D, 0x65, 0x6E,
			0x74, 0x53, 0x75, 0x6D, 0x6D, 0x61, 0x72, 0x79,
			0x49, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74,
			0x69, 0x6F, 0x6E, 0x00
		};

		CompoundFile::Directory dir = file.directory( data );

		REQUIRE( dir.name() == data );
		REQUIRE( dir.type() == CompoundFile::Directory::UserStream );
		REQUIRE( dir.streamSecID() == 0x04 );
		REQUIRE( dir.streamSize() == 0xEC );
		REQUIRE( dir.rightChild() == 0xFFFFFFFF );
		REQUIRE( dir.leftChild() == 0xFFFFFFFF );
		REQUIRE( dir.rootNode() == 0xFFFFFFFF );
	}

	{
		const wchar_t data[] = {
			0x05, 0x53, 0x75, 0x6D, 0x6D, 0x61, 0x72, 0x79,
			0x49, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74,
			0x69, 0x6F, 0x6E, 0x00
		};

		CompoundFile::Directory dir = file.directory( data );

		REQUIRE( dir.name() == data );
		REQUIRE( dir.type() == CompoundFile::Directory::UserStream );
		REQUIRE( dir.streamSecID() == 0x00 );
		REQUIRE( dir.streamSize() == 0xE0 );
		REQUIRE( dir.rightChild() == 0x03 );
		REQUIRE( dir.leftChild() == 0x01 );
		REQUIRE( dir.rootNode() == 0xFFFFFFFF );
	}

	REQUIRE_THROWS_AS( file.directory( L"ThereIsNoSuchDir" ),
		CompoundFile::Exception );
}


//
// test_stream
//

TEST_CASE( "test_stream" )
{
	CompoundFile::File file( "./test/data/test.xls" );

	std::unique_ptr< Excel::Stream > stream( file.stream(
		file.directory( L"Workbook" ) ) );

	stream->seek( 512, Excel::Stream::FromBeginning );

	REQUIRE( stream->getByte() == (char) 0x01 );
	REQUIRE( stream->getByte() == (char) 0x00 );
	REQUIRE( stream->getByte() == (char) 0x3F );
	REQUIRE( stream->getByte() == (char) 0x00 );

	stream->seek( -6, Excel::Stream::FromCurrent );

	REQUIRE( stream->getByte() == (char) 0xDC );
	REQUIRE( stream->getByte() == (char) 0x00 );

	stream->seek( 128, Excel::Stream::FromEnd );

	REQUIRE( stream->getByte() == (char) 0x66 );
	REQUIRE( stream->getByte() == (char) 0x0A );
	REQUIRE( stream->getByte() == (char) 0x40 );
	REQUIRE( stream->getByte() == (char) 0x08 );
}


//
// test_stream
//

TEST_CASE( "test_stream_name" )
{
	std::ifstream fileStream( "./test/data/test.xls", std::ios::in | std::ios::binary );
	CompoundFile::File file( fileStream );

	std::unique_ptr< Excel::Stream > stream( file.stream(
		file.directory( L"Workbook" ) ) );

	stream->seek( 512, Excel::Stream::FromBeginning );

	REQUIRE( stream->getByte() == (char) 0x01 );
}
