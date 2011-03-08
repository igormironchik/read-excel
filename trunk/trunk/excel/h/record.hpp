
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

#ifndef EXCEL__RECORD_HPP__INCLUDED
#define EXCEL__RECORD_HPP__INCLUDED

// Excel include.
#include <excel/h/stream.hpp>

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

	void operator = ( const RecordSubstream & stream );

	//! Read one byte from the stream.
	char getByte();

	//! \return true if EOF reached.
	bool eof() const;

	//! Seek stream to new position.
	void seek( int pos, SeekType type = FromBeginning );

	//! \return Position in the stream.
	int pos();

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

	void operator = ( const Record & record );

	//! \return Record's code.
	short code() const;

	//! \return Record's length.
	int length() const;

	//! \return Stream with record's data.
	Stream & dataStream();

	//! \return Borders indexes of the continue records.
	const std::vector< int > & borders() const;

private:
	//! Read record from the stream.
	void read( Stream & stream );

private:
	//! Record's code.
	short m_code;
	//! Record's length.
	int m_length;
	//! Record's substream.
	RecordSubstream m_stream;
	//! Borders indexes of the continue records.
	std::vector< int > m_borders;
}; // class Record

} /* namespace Excel */

#endif // EXCEL__RECORD_HPP__INCLUDED

