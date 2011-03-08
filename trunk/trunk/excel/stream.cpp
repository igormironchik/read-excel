
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

// Excel include.
#include <excel/h/stream.hpp>


namespace Excel {

//
// Stream
//

Stream::Stream( ByteOrder byteOrder )
	:	m_byteOrder( byteOrder )
{
}

Stream::~Stream()
{
}

void
Stream::operator = ( const Stream & stream )
{
	m_byteOrder = stream.byteOrder();
}

Stream::ByteOrder
Stream::byteOrder() const
{
	return m_byteOrder;
}

char
Stream::getByte()
{
	return 0xFF;
}

bool
Stream::eof() const
{
	return true;
}

void
Stream::seek( int pos, SeekType type )
{
}

int
Stream::pos()
{
	return -1;
}

} /* namespace Excel */
