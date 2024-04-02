
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
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
