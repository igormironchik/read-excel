
/*!
	\file
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

// Excel include.
#include <read-excel/stream.hpp>

// C++ include.
#include <cstddef>


//
// TestStream
//

//! Test stream.
class TestStream
	:	public Excel::Stream
{
public:
	TestStream( const char * data, int32_t size );
	virtual ~TestStream();

	//! Read one byte from the stream.
	char getByte() override;

	//! \return true if EOF reached.
	bool eof() const override;

	//! Seek stream to new position.
	void seek( int32_t pos, Excel::Stream::SeekType type =
		Excel::Stream::FromBeginning ) override;

	//! \return Position in the stream.
	int32_t pos() override;

private:
	//! Data.
	const char * m_data;
	//! Position in the stream.
	int32_t m_pos;
	//! Size of the stream;
	int32_t m_size;
}; // class TestStream
