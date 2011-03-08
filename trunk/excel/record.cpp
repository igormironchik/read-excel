
/*!
	\file
	\brief Excel Record.

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
#include <excel/h/record.hpp>


namespace Excel {

//
// RecordSubstream
//

RecordSubstream::RecordSubstream( Stream::ByteOrder byteOrder )
	:	Stream( byteOrder )
{
}

void
RecordSubstream::operator = ( const RecordSubstream & stream )
{
	Stream::operator = ( stream );

	m_stream.clear();
	m_stream << stream.m_stream.rdbuf();
}

char
RecordSubstream::getByte()
{
	char ch;
	m_stream.get( ch );

	return ch;
}

bool
RecordSubstream::eof() const
{
	return m_stream.eof();
}

void
RecordSubstream::seek( int pos, SeekType type )
{
	std::ios::seekdir dir;

	if( type == Stream::FromBeginning )
		dir = std::ios::beg;
	else if( type == Stream::FromCurrent )
		dir = std::ios::cur;
	else
		dir = std::ios::end;

	m_stream.seekg( pos, dir );
}

int
RecordSubstream::pos()
{
	return m_stream.tellg();
}

void
RecordSubstream::write( const char * data, size_t size )
{
	m_stream.write( data, size );
}


//
// Record
//

Record::Record( Stream & stream )
	:	m_code( 0 )
	,	m_length( 0 )
	,	m_stream( stream.byteOrder() )
{
	read( stream );
}

Record::~Record()
{
}

void
Record::operator = ( const Record & record )
{
	m_code = record.code();
	m_length = record.length();
	m_stream = record.m_stream;
	m_borders = record.borders();
}

void
Record::read( Stream & stream )
{
	stream.read( m_code, 2 );
	stream.read( m_length, 2 );

	short nextRecordCode = 0;
	short nextRecordLength = 0;

	std::vector< char > data;

	if( m_length )
	{
		data.reserve( m_length );

		for( size_t i = 0; i < m_length; ++i )
			data.push_back( stream.getByte() );
	}

	stream.read( nextRecordCode, 2 );

	while( nextRecordCode == XL_CONTINUE )
	{
		m_borders.push_back( m_length );

		stream.read( nextRecordLength, 2 );

		data.reserve( data.size() + nextRecordLength );
		if( nextRecordLength )
		{
			for( size_t i = 0; i < nextRecordLength; ++i )
				data.push_back( stream.getByte() );
		}
		m_length += nextRecordLength;
		stream.read( nextRecordCode, 2 );
	}

	stream.seek( -2, Stream::FromCurrent );

	if( data.size() )
		m_stream.write( &data[ 0 ], data.size() );
}

short
Record::code() const
{
	return m_code;
}

int
Record::length() const
{
	return m_length;
}

Stream &
Record::dataStream()
{
	return m_stream;
}

const std::vector< int > &
Record::borders() const
{
	return m_borders;
}

} /* namespace Excel */
