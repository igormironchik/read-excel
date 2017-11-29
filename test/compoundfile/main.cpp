
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
#include <excel/compoundfile/compoundfile.hpp>

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
