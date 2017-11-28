
/*!
	\file
	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2014 Igor Mironchik

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

// test include.
#include <test/stream/stream.hpp>

// C++ include.
#include <cstdlib>


//
// TestStream
//


TestStream::TestStream( const char * data, size_t size )
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
	return ( m_pos == m_size );
}

void
TestStream::seek( int pos, Excel::Stream::SeekType type )
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

	if( static_cast< std::size_t > ( pos ) >= m_size )
	{
		m_pos = m_size;
		return;
	}

	m_pos = pos;
}

int
TestStream::pos()
{
	return m_pos;
}
