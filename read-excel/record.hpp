
/*!
	\file
	\brief Excel Record.

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

#ifndef EXCEL__RECORD_HPP__INCLUDED
#define EXCEL__RECORD_HPP__INCLUDED

// Excel include.
#include "stream.hpp"

// C++ include.
#include <vector>
#include <sstream>


namespace Excel {


//
// RecordSubstream
//

class RecordSubstream
	:	public Stream
{
	friend class Record;

public:
	explicit RecordSubstream( Stream::ByteOrder byteOrder );

	//! Read one byte from the stream.
	char getByte() override;

	//! \return true if EOF reached.
	bool eof() const override;

	//! Seek stream to new position.
	void seek( int32_t pos, SeekType type = FromBeginning ) override;

	//! \return Position in the stream.
	int32_t pos() override;

protected:
	//! Write data to the stream.
	void write( const char * data, size_t size );

private:
	//! Stream.
	std::stringstream m_stream;
}; // class RecordSubstream


//
// RecordType
//

//! Types of the Excel's records.
enum RecordType {
	XL_BOF = 0x809,
	XL_EOF = 0x0A,
	XL_BOUNDSHEET = 0x85,
	XL_DIMENSION = 0x200,
	XL_ROW = 0x208,
	XL_NOTE = 0x1C,
	XL_TXO = 0x1B6,
	XL_RK = 0x7E,
	XL_RK2 = 0x27E,
	XL_MULRK = 0xBD,
	XL_INDEX = 0x20B,
	XL_SST = 0xFC,
	XL_EXTSST = 0xFF,
	XL_CONTINUE = 0x3C,
	XL_LABEL = 0x204,
	XL_LABELSST = 0xFD,
	XL_NUMBER = 0x203,
	XL_NAME = 0x18,
	XL_ARRAY = 0x221,
	XL_STRING = 0x207,
	XL_FORMULA = 0x06,
	XL_FORMAT = 0x41E,
	XL_XF = 0xE0,
	XL_BOOLERR = 0x205,
	XL_DATEMODE = 0x22,
	XL_UNKNOWN = 0xFFFF
}; // enum RecordType

//
// Record
//

//! Record in the Excel file.
class Record {
public:
	Record( Stream & stream );
	~Record();

	//! \return Record's code.
	uint16_t code() const;

	//! \return Record's length.
	uint32_t length() const;

	//! \return Stream with record's data.
	Stream & dataStream();

	//! \return Borders indexes of the continue records.
	const std::vector< int32_t > & borders() const;

private:
	//! Read record from the stream.
	void read( Stream & stream );

private:
	//! Record's code.
	uint16_t m_code;
	//! Record's length.
	uint32_t m_length;
	//! Record's substream.
	RecordSubstream m_stream;
	//! Borders indexes of the continue records.
	std::vector< int32_t > m_borders;
}; // class Record

//
// RecordSubstream
//

inline
RecordSubstream::RecordSubstream( Stream::ByteOrder byteOrder )
	:	Stream( byteOrder )
{
}

inline char
RecordSubstream::getByte()
{
	char ch;
	m_stream.get( ch );

	return ch;
}

inline bool
RecordSubstream::eof() const
{
	return m_stream.eof();
}

inline void
RecordSubstream::seek( int32_t pos, SeekType type )
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

inline int32_t
RecordSubstream::pos()
{
	return static_cast< int32_t > ( m_stream.tellg() );
}

inline void
RecordSubstream::write( const char * data, size_t size )
{
	m_stream.write( data, size );
}


//
// Record
//

inline
Record::Record( Stream & stream )
	:	m_code( 0 )
	,	m_length( 0 )
	,	m_stream( stream.byteOrder() )
{
	read( stream );
}

inline
Record::~Record()
{
}

inline void
Record::read( Stream & stream )
{
	stream.read( m_code, 2 );
	stream.read( m_length, 2 );

	uint16_t nextRecordCode = 0;
	uint16_t nextRecordLength = 0;

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
			for( uint16_t i = 0; i < nextRecordLength; ++i )
				data.push_back( stream.getByte() );
		}
		m_length += nextRecordLength;
		stream.read( nextRecordCode, 2 );
	}

	if( !stream.eof() )
		stream.seek( -2, Stream::FromCurrent );

	if( data.size() )
		m_stream.write( &data[ 0 ], data.size() );
}

inline uint16_t
Record::code() const
{
	return m_code;
}

inline uint32_t
Record::length() const
{
	return m_length;
}

inline Stream &
Record::dataStream()
{
	return m_stream;
}

inline const std::vector< int32_t > &
Record::borders() const
{
	return m_borders;
}

} /* namespace Excel */

#endif // EXCEL__RECORD_HPP__INCLUDED

