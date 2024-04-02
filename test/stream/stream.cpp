
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

// test include.
#include <test/stream/stream.hpp>

// C++ include.
#include <cstdlib>


//
// TestStream
//


TestStream::TestStream( const char * data, int32_t size )
	:	Excel::Stream( Excel::Stream::LittleEndian )
	,	m_data( data )
	,	m_pos( 0 )
	,	m_size( size )
{
}

TestStream::~TestStream()
{
}

char
TestStream::getByte()
{
	char byte = m_data[ m_pos ];
	++m_pos;

	return byte;
}

bool
TestStream::eof() const
{
	return ( m_pos > m_size );
}

void
TestStream::seek( int32_t pos, Excel::Stream::SeekType type )
{
	if( type == Excel::Stream::FromCurrent )
	{
		pos += m_pos;

		if( pos < 0 )
			pos += m_size;
	}
	else if( type == Excel::Stream::FromEnd && pos > 0 )
		pos = m_size - pos;
	else if( type == Excel::Stream::FromEnd && pos < 0 )
		pos = std::abs( pos );
	else if( type == Excel::Stream::FromBeginning && pos < 0 )
		pos = m_size - pos;

	if( pos >= m_size )
	{
		m_pos = m_size;
		return;
	}

	m_pos = pos;
}

int32_t
TestStream::pos()
{
	return m_pos;
}
