
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
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

	book.clear();

	REQUIRE( book.sheetsCount() == 0 );
}

TEST_CASE( "test_book_via_stream" )
{
	std::ifstream fileStream( "test/data/strange.xls", std::ios::in | std::ios::binary );
	Excel::Book book( fileStream );

	REQUIRE( book.sheetsCount() == 3 );

	Excel::Sheet * sheet = book.sheet( 0 );
	const auto text = sheet->cell( 0, 0 ).getString();
	REQUIRE( text.find( L"Somefile" ) != std::wstring::npos );
	REQUIRE( text.find( L"abcd" ) == 0 );
	REQUIRE( text.length() == 255 );
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

TEST_CASE( "test_very_small_book" )
{
	Excel::Book book( "test/data/MiscOperatorTests.xls" );

	REQUIRE( book.sheetsCount() == 3 );
	REQUIRE( book.sheet( 0 )->sheetName() == L"Sheet1" );
}
