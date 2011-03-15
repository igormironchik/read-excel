
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
#include <excel/compoundfile/h/compoundfile.hpp>

// unit test helper.
#include <test/helper/helper.hpp>


UNIT_TEST_START

	//
	// test_directory
	//

	UNIT_START( test_directory )

		CompoundFile::File file( L"./test/data/test.xls" );

		{
			CompoundFile::Directory dir = file.directory( L"Workbook" );

			CHECK_CONDITION( dir.name() == L"Workbook" );
			CHECK_CONDITION( dir.type() == CompoundFile::Directory::UserStream );
			CHECK_CONDITION( dir.streamSecID() == 0x02 );
			CHECK_CONDITION( dir.streamSize() == 0x3480 );
			CHECK_CONDITION( dir.rightChild() == 0xFFFFFFFF );
			CHECK_CONDITION( dir.leftChild() == 0x04 );
			CHECK_CONDITION( dir.rootNode() == 0xFFFFFFFF );
		}

		{
			const wchar_t data[] = {
				0x01, 0x43, 0x6F, 0x6D, 0x70, 0x4F, 0x62, 0x6A, 0x00
			};

			CompoundFile::Directory dir = file.directory( data );

			CHECK_CONDITION( dir.name() == data );
			CHECK_CONDITION( dir.type() == CompoundFile::Directory::UserStream );
			CHECK_CONDITION( dir.streamSecID() == 0x08 );
			CHECK_CONDITION( dir.streamSize() == 0x6D );
			CHECK_CONDITION( dir.rightChild() == 0xFFFFFFFF );
			CHECK_CONDITION( dir.leftChild() == 0xFFFFFFFF );
			CHECK_CONDITION( dir.rootNode() == 0xFFFFFFFF );
		}

		{
			const wchar_t data[] = {
				0x05, 0x44, 0x6F, 0x63, 0x75, 0x6D, 0x65, 0x6E,
				0x74, 0x53, 0x75, 0x6D, 0x6D, 0x61, 0x72, 0x79,
				0x49, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74,
				0x69, 0x6F, 0x6E, 0x00
			};

			CompoundFile::Directory dir = file.directory( data );

			CHECK_CONDITION( dir.name() == data );
			CHECK_CONDITION( dir.type() == CompoundFile::Directory::UserStream );
			CHECK_CONDITION( dir.streamSecID() == 0x04 );
			CHECK_CONDITION( dir.streamSize() == 0xEC );
			CHECK_CONDITION( dir.rightChild() == 0xFFFFFFFF );
			CHECK_CONDITION( dir.leftChild() == 0xFFFFFFFF );
			CHECK_CONDITION( dir.rootNode() == 0xFFFFFFFF );
		}

		{
			const wchar_t data[] = {
				0x05, 0x53, 0x75, 0x6D, 0x6D, 0x61, 0x72, 0x79,
				0x49, 0x6E, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74,
				0x69, 0x6F, 0x6E, 0x00
			};

			CompoundFile::Directory dir = file.directory( data );

			CHECK_CONDITION( dir.name() == data );
			CHECK_CONDITION( dir.type() == CompoundFile::Directory::UserStream );
			CHECK_CONDITION( dir.streamSecID() == 0x00 );
			CHECK_CONDITION( dir.streamSize() == 0xE0 );
			CHECK_CONDITION( dir.rightChild() == 0x03 );
			CHECK_CONDITION( dir.leftChild() == 0x01 );
			CHECK_CONDITION( dir.rootNode() == 0xFFFFFFFF );
		}

	UNIT_FINISH( test_directory )


	//
	// test_stream
	//

	UNIT_START( test_stream )

		CompoundFile::File file( L"./test/data/test.xls" );

		std::auto_ptr< Excel::Stream > stream( file.stream(
			file.directory( L"Workbook" ) ) );

		stream->seek( 512, Excel::Stream::FromBeginning );

		CHECK_CONDITION( stream->getByte() == (char) 0x01 );
		CHECK_CONDITION( stream->getByte() == (char) 0x00 );
		CHECK_CONDITION( stream->getByte() == (char) 0x3F );
		CHECK_CONDITION( stream->getByte() == (char) 0x00 );

		stream->seek( -6, Excel::Stream::FromCurrent );

		CHECK_CONDITION( stream->getByte() == (char) 0xDC );
		CHECK_CONDITION( stream->getByte() == (char) 0x00 );

		stream->seek( 128, Excel::Stream::FromEnd );

		CHECK_CONDITION( stream->getByte() == (char) 0x66 );
		CHECK_CONDITION( stream->getByte() == (char) 0x0A );
		CHECK_CONDITION( stream->getByte() == (char) 0x40 );
		CHECK_CONDITION( stream->getByte() == (char) 0x08 );

	UNIT_FINISH( test_stream )

UNIT_TEST_FINISH
