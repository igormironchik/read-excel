
/*!
	\file
	\brief Stream interface.

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

#ifndef EXCEL__STREAM_HPP__INCLUDED
#define EXCEL__STREAM_HPP__INCLUDED


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

	explicit Stream( ByteOrder byteOrder );
	virtual ~Stream();

	void operator = ( const Stream & stream );

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
	virtual void seek( int pos, SeekType type = FromBeginning );

	//! \return Position in the stream.
	virtual int pos();

	//! Read data from the stream.
	template< typename Type >
	void read( Type & retVal, int bytes = 0 )
	{
		retVal = Type(0);
		if( bytes == 0 ) bytes = sizeof( Type );

		for( int i = 0; i < bytes; ++i )
		{
			Type c = (Type)(unsigned char) getByte();

			#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
				if( m_byteOrder == BigEndian )
					retVal |= ( c << 8 * ( bytes - i ) );
				else
					retVal |= ( c << 8 * i );
			#else
				if( m_byteOrder == LittleEndian )
					retVal |= ( c << 8 * ( bytes - i ) );
				else
					retVal |= ( c << 8 * i );
			#endif
		}
	}

private:
	//! Byte order.
	ByteOrder m_byteOrder;
}; // class Stream

} /* namespace Excel */

#endif // EXCEL__STREAM_HPP__INCLUDED
