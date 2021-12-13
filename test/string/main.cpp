
/*!
	\file
	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2021 Igor Mironchik

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
#include <read-excel/string.hpp>

// C++ include.
#include <vector>

// unit test helper.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <test/doctest/doctest.h>
#include <test/helper/helper.hpp>
#include <test/stream/stream.hpp>


const auto data = make_data(
	0x0Fu, 0x00u, 0x08u, 0x02u, 0x00u, 0x74u, 0x68u, 0x69u,
	0x73u, 0x20u, 0x69u, 0x73u, 0x20u, 0x72u, 0x65u, 0x64u,
	0x20u, 0x69u, 0x6Eu, 0x6Bu, 0x08u, 0x00u, 0x06u, 0x00u,
	0x0Bu, 0x00u, 0x05u, 0x00u,

	0x0Fu, 0x00u, 0x00u, 0x74u, 0x68u, 0x69u, 0x73u, 0x20u,
	0x69u, 0x73u, 0x20u, 0x72u, 0x65u, 0x64u, 0x20u, 0x69u,
	0x6Eu, 0x6Bu,

	0x0Fu, 0x00u, 0x01u, 0x74u, 0x00u, 0x68u, 0x00u, 0x69u,
	0x00u, 0x73u, 0x00u, 0x20u, 0x00u, 0x69u, 0x00u, 0x73u,
	0x00u, 0x20u, 0x00u, 0x72u, 0x00u, 0x65u, 0x00u, 0x64u,
	0x00u, 0x20u, 0x00u, 0x69u, 0x00u, 0x6Eu, 0x00u, 0x6Bu,
	0x00u,

	0x0Fu, 0x00u, 0x04u, 0x04u, 0x00u, 0x00u, 0x00u, 0x74u,
	0x68u, 0x69u, 0x73u, 0x20u, 0x69u, 0x73u, 0x20u, 0x72u,
	0x65u, 0x64u, 0x20u, 0x69u, 0x6Eu, 0x6Bu, 0x00u, 0x00u,
	0x00u, 0x00u,

	0x0Fu, 0x00u, 0x0Cu, 0x02u, 0x00u, 0x04u, 0x00u, 0x00u,
	0x00u, 0x74u, 0x68u, 0x69u, 0x73u, 0x20u, 0x69u, 0x73u,
	0x20u, 0x72u, 0x65u, 0x64u, 0x20u, 0x69u, 0x6Eu, 0x6Bu,
	0x08u, 0x00u, 0x06u, 0x00u, 0x0Bu, 0x00u, 0x05u, 0x00u,
	0x00u, 0x00u, 0x00u, 0x00u,

	0x0Fu, 0x00u, 0x00u, 0x74u, 0x68u, 0x69u, 0x73u, 0x20u,
	0x69u, 0x73u, 0x20u, 0x72u, 0x65u, 0x64u, 0x20u, 0x69u,
	0x6Eu, 0x6Bu
); // data


TEST_CASE( "test_string" )
{
	std::vector< int32_t > borders;
	std::wstring str;

	TestStream stream( &data[ 0 ], 159 );

	str = Excel::loadString( stream, borders );

	REQUIRE( str == L"this is red ink" );

	str = Excel::loadString( stream, borders );

	REQUIRE( str == L"this is red ink" );

	str = Excel::loadString( stream, borders );

	REQUIRE( str == L"this is red ink" );

	str = Excel::loadString( stream, borders );

	REQUIRE( str == L"this is red ink" );

	str = Excel::loadString( stream, borders );

	REQUIRE( str == L"this is red ink" );

	str = Excel::loadString( stream, borders );

	REQUIRE( str == L"this is red ink" );
}
