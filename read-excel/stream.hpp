
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef EXCEL__STREAM_HPP__INCLUDED
#define EXCEL__STREAM_HPP__INCLUDED

// C++ include.
#include <cstdint>

// read-excel include.
#include "exceptions.hpp"

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
	virtual char getByte() = 0;

	//! \return true if EOF reached.
	virtual bool eof() const = 0;

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
	virtual void seek( int32_t pos, SeekType type = FromBeginning ) = 0;

	//! \return Position in the stream.
	virtual int32_t pos() = 0;

	//! Read data from the stream.
	template< typename Type >
	void read( Type & retVal, int32_t bytes = 0 )
	{
		retVal = Type(0);
		if( bytes == 0 ) bytes = sizeof( Type );

		for( int32_t i = 0; i < bytes; ++i )
		{
			Type c = (Type)(unsigned char) getByte();

			if( eof() )
				throw Exception( L"Unexpected end of file." );

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

inline
Stream::Stream( ByteOrder byteOrder )
	:	m_byteOrder( byteOrder )
{
}

inline
Stream::~Stream()
{
}

inline Stream::ByteOrder
Stream::byteOrder() const
{
	return m_byteOrder;
}

} /* namespace Excel */

#endif // EXCEL__STREAM_HPP__INCLUDED
