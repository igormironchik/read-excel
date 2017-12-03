
/*!
	\file
	\brief Stream interface.

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

#ifndef EXCEL__STREAM_HPP__INCLUDED
#define EXCEL__STREAM_HPP__INCLUDED

// C++ include.
#include <cstdint>

namespace Excel {

//
// Stream
//

//! Stream interface.
class Stream {
public:
	//! Byte order identifier.
	enum ByteOrder {
		//! Big-Endian.
		BigEndian,
		//! Little-Endian.
		LittleEndian
	}; // enum ByteOrder

private:

	//
	// SystemByteOrder
	//

	//! System's byte order.
	class SystemByteOrder {
	public:
		static ByteOrder byteOrder()
		{
			static const int16_t word = 0x0001;
			static const char * byte = (const char *) &word;

			return ( byte[ 0 ] ? LittleEndian : BigEndian );
		}
	}; // class SystemByteOrder

public:

	explicit Stream( ByteOrder byteOrder );
	virtual ~Stream();

	//! \return Byte order in the stream.
	ByteOrder byteOrder() const;

	//! Read one byte from the stream.
	virtual char getByte();

	//! \return true if EOF reached.
	virtual bool eof() const;

	//! Seek type.
	enum SeekType {
		//! Seek from the beginning of the stream.
		FromBeginning,
		//! Seek from the current position in the stream.
		FromCurrent,
		//! Seek from the end of the stream.
		FromEnd
	}; // enum SeekType

	//! Seek stream to new position.
	virtual void seek( int32_t pos, SeekType type = FromBeginning );

	//! \return Position in the stream.
	virtual int32_t pos();

	//! Read data from the stream.
	template< typename Type >
	void read( Type & retVal, int32_t bytes = 0 )
	{
		retVal = Type(0);
		if( bytes == 0 ) bytes = sizeof( Type );

		for( int32_t i = 0; i < bytes; ++i )
		{
			Type c = (Type)(unsigned char) getByte();

			if( SystemByteOrder::byteOrder() != m_byteOrder )
				retVal |= ( c << 8 * ( bytes - i - 1 ) );
			else
				retVal |= ( c << 8 * i );
		}
	}

private:
	//! Byte order.
	ByteOrder m_byteOrder;
}; // class Stream

} /* namespace Excel */

#endif // EXCEL__STREAM_HPP__INCLUDED
