
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
#include <read-excel/book.hpp>

// C++ include.
#include <cmath>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>


TEST_CASE( "test_book" )
{
	Excel::Book book( "test/data/test.xls" );

	REQUIRE( book.sheetsCount() == 1 );

	Excel::Sheet * sheet = book.sheet( 0 );

	REQUIRE( sheet->rowsCount() == 3 );
	REQUIRE( sheet->columnsCount() == 4 );

	REQUIRE( sheet->cell( 0, 0 ).getString() == L"String #1" );
	REQUIRE( sheet->cell( 1, 0 ).getString() == L"String #2" );
	REQUIRE( sheet->cell( 2, 0 ).getString() == L"String #3" );

	REQUIRE( std::fabs( sheet->cell( 0, 1 ).getDouble() - 1.0 ) < 1E-9 );
	REQUIRE( std::fabs( sheet->cell( 1, 1 ).getDouble() - 2.0 ) < 1E-9 );
	REQUIRE( std::fabs( sheet->cell( 2, 1 ).getDouble() - 3.0 ) < 1E-9 );

	REQUIRE( std::fabs( sheet->cell( 0, 2 ).getDouble() - 0.1 ) < 1E-9 );
	REQUIRE( std::fabs( sheet->cell( 1, 2 ).getDouble() - 0.2 ) < 1E-9 );
	REQUIRE( std::fabs( sheet->cell( 2, 2 ).getDouble() - 0.3 ) < 1E-9 );

	REQUIRE( std::fabs( sheet->cell( 0, 3 ).getFormula().getDouble() - 1.1 ) < 1E-9 );
	REQUIRE( std::fabs( sheet->cell( 1, 3 ).getFormula().getDouble() - 2.2 ) < 1E-9 );
	REQUIRE( std::fabs( sheet->cell( 2, 3 ).getFormula().getDouble() - 3.3 ) < 1E-9 );

}

TEST_CASE( "test_book_via_stream" )
{
	std::ifstream fileStream( "test/data/strange.xls", std::ios::in | std::ios::binary );
	Excel::Book book( fileStream );

	REQUIRE( book.sheetsCount() == 3 );

	Excel::Sheet * sheet = book.sheet( 0 );
	const auto text = sheet->cell( 0, 0 ).getString();
	REQUIRE( text.find( L"Somefile" ) != std::wstring::npos );
}

struct CustomStorage : public Excel::EmptyStorage {
	std::wstring m_text;
	std::wstring m_sheetName;
	void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) override;
	void onSheet( size_t idx, const std::wstring & value ) override;
}; // struct CustomStorage

inline void
CustomStorage::onSharedString( size_t , size_t , const std::wstring & value )
{
	m_text += value;
}

inline void
CustomStorage::onSheet( size_t , const std::wstring & value )
{
	m_sheetName = value;
}

TEST_CASE( "test_book_custom_storage" )
{
	std::ifstream fileStream( "test/data/test.xls", std::ios::in | std::ios::binary );
	CustomStorage storage;
	Excel::Parser::loadBook( fileStream, storage );

	REQUIRE( storage.m_text.find( L"String #1" ) != std::wstring::npos );
	REQUIRE( storage.m_sheetName == L"Sheet" );
}

TEST_CASE( "test_book_empty_storage" )
{
	std::ifstream fileStream( "test/data/test.xls", std::ios::in | std::ios::binary );
	Excel::EmptyStorage emptyStorage;
	Excel::Parser::loadBook( fileStream, emptyStorage );
}