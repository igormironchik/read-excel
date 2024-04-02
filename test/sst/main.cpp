
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// Excel include.
#include <read-excel/parser.hpp>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>
#include <test/helper/helper.hpp>
#include <test/stream/stream.hpp>


const auto data = make_data(
	0xFCu, 0x00u, 0x13u, 0x00u,
	0x03u, 0x00u, 0x00u, 0x00u, 0x03u, 0x00u, 0x00u, 0x00u,
	0x10u, 0x00u, 0x00u,
	0x53u, 0x54u, 0x53u, 0x54u, 0x53u, 0x54u, 0x53u, 0x54u,

	0x3Cu, 0x00u, 0x11u, 0x00u,
	0x01u,
	0x53u, 0x00u, 0x54u, 0x00u, 0x53u, 0x00u, 0x54u, 0x00u,
	0x53u, 0x00u, 0x54u, 0x00u, 0x53u, 0x00u, 0x54u, 0x00u,

	0x3Cu, 0x00u, 0x13u, 0x00u,
	0x10u, 0x00u, 0x00u,
	0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u,
	0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u, 0x51u, 0x52u,

	0x3Cu, 0x00u, 0x23u, 0x00u,
	0x10u, 0x00u, 0x01u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u,
	0x51u, 0x00u, 0x52u, 0x00u, 0x51u, 0x00u, 0x52u, 0x00u
); // data


struct TestSstStorage : public Excel::EmptyStorage {
	std::vector< std::wstring > m_sst;
	void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) override;
}; // struct TestSstStorage

inline void
TestSstStorage::onSharedString( size_t sstSize, size_t idx, const std::wstring & value )
{
	m_sst.push_back( value );
}

//
// test_sst
//

TEST_CASE( "test_sst" )
{
	TestStream testStream( &data[ 0 ], 106 );

	Excel::Record record( testStream );

	TestSstStorage sst;
	Excel::Parser::parseSST( record, sst );

	REQUIRE( sst.m_sst.size() == 3 );

	REQUIRE( sst.m_sst[ 0 ] == L"STSTSTSTSTSTSTST" );
	REQUIRE( sst.m_sst[ 1 ] == L"QRQRQRQRQRQRQRQR" );
	REQUIRE( sst.m_sst[ 2 ] == L"QRQRQRQRQRQRQRQR" );
}
