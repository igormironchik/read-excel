
/*!
	\file
	\brief Excel WorkBook.

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

#ifndef EXCEL__BOOK_HPP__INCLUDED
#define EXCEL__BOOK_HPP__INCLUDED

// Excel include.
#include "sst.hpp"
#include "sheet.hpp"
#include "record.hpp"
#include "string.hpp"
#include "bof.hpp"
#include "exceptions.hpp"
#include "stream.hpp"

#include "compoundfile/compoundfile.hpp"
#include "compoundfile/compoundfile_exceptions.hpp"

// C++ include.
#include <vector>
#include <string>
#include <memory>
#include <sstream>


namespace Excel {

//
// Book
//

//! Excel WorkBook.
class Book {
public:
	//! Mode of the day. The base date for displaying date values.
	//! All dates are stored as count of days past this base date.
	enum class DateMode {
		//! Unknown.
		Unknown = -1,
		//! Base date is 1899-Dec-31 (the date value 1 represents 1900-Jan-01)
		Dec31_1899 = 0,
		//! Base date is 1904-Jan-01 (the date value 1 represents 1904-Jan-02)
		Jan01_1904 = 1
	}; // enum DateMode

public:
	Book();
	explicit Book( const std::string & fileName );
	~Book();

	//! \return Date mode.
	DateMode dateMode() const;

	//! \return Count of the sheets.
	size_t sheetsCount() const;

	//! \return Sheet with given index,
	//! or NULL if there is no sheet with such index.
	Sheet * sheet( size_t index ) const;

	//! Load WorkBook from file.
	void loadBook( const std::string & fileName );

private:
	//! Load sheets from file.
	void loadGlobals( std::vector< BoundSheet > & boundSheets,
		Stream & stream );
	//! Load boundsheet.
	BoundSheet parseBoundSheet( Record & record );
	//! Load WorkSheets.
	void loadWorkSheets( const std::vector< BoundSheet > & boundSheets,
		Stream & stream );
	//! Clear book.
	void clear();
	//! Handle date mode.
	void handleDateMode( Record & r );

private:
	//! Parsed WorkSheets.
	std::vector< Sheet* > m_sheets;
	//! Shared string table.
	std::vector< std::wstring > m_sst;
	//! Date mode.
	DateMode m_dateMode;
}; // class Book

inline
Book::Book()
	:	m_dateMode( DateMode::Unknown )
{
	static_assert( sizeof( double ) == 8,
		"Unsupported platform: double has to be 8 bytes." );
}

inline
Book::Book( const std::string & fileName )
	:	m_dateMode( DateMode::Unknown )
{
	static_assert( sizeof( double ) == 8,
		"Unsupported platform: double has to be 8 bytes." );

	loadBook( fileName );
}

inline void
Book::clear()
{
	for( std::vector< Sheet* >::iterator it = m_sheets.begin(),
		last = m_sheets.end(); it != last; ++it )
	{
		delete *it;
		*it = 0;
	}

	m_sheets.clear();
	m_sst.clear();
}

inline
Book::~Book()
{
	clear();
}

inline Book::DateMode
Book::dateMode() const
{
	return m_dateMode;
}

inline size_t
Book::sheetsCount() const
{
	return m_sheets.size();
}

inline Sheet *
Book::sheet( size_t index ) const
{
	if( index < m_sheets.size() )
		return m_sheets[ index ];

	std::wstringstream stream;
	stream << L"There is no such sheet with index : " << index;

	throw Exception( stream.str() );
}

inline void
Book::loadBook( const std::string & fileName )
{
	try {
		clear();

		CompoundFile::File file( fileName );
		auto stream = file.stream( file.directory( L"Workbook" ) );

		std::vector< BoundSheet > boundSheets;

		loadGlobals( boundSheets, *stream );

		loadWorkSheets( boundSheets, *stream );
	}
	catch( const CompoundFile::Exception & x )
	{
		throw Exception( x.whatAsWString() );
	}
}

inline void
Book::handleDateMode( Record & r )
{
	uint16_t mode = 0;

	r.dataStream().read( mode, 2 );

	if( mode )
		m_dateMode = DateMode::Jan01_1904;
	else
		m_dateMode = DateMode::Dec31_1899;
}

inline void
Book::loadGlobals( std::vector< BoundSheet > & boundSheets,
	Stream & stream )
{
	while( true )
	{
		Record r( stream );

		switch( r.code() )
		{
			case XL_SST :
				m_sst = SharedStringTable::parse( r );
				break;

			case XL_BOUNDSHEET :
				boundSheets.push_back( parseBoundSheet( r ) );
				break;

			case XL_DATEMODE :
				handleDateMode( r );
				break;

			case XL_EOF :
				return;

			default:
				break;
		}
	}
}

inline BoundSheet
Book::parseBoundSheet( Record & record )
{
	int32_t pos = 0;
	int16_t sheetType = 0;
	std::wstring sheetName;

	record.dataStream().read( pos, 4 );

	record.dataStream().read( sheetType, 2 );

	sheetName = loadString( record.dataStream(), record.borders(), 1 );

	return BoundSheet( pos,
		BoundSheet::convertSheetType( sheetType ),
		sheetName );
}

inline void
Book::loadWorkSheets( const std::vector< BoundSheet > & boundSheets,
	Stream & stream )
{
	for( std::vector< BoundSheet >::const_iterator it = boundSheets.begin(),
		last = boundSheets.end(); it != last; ++it )
	{
		if( it->sheetType() == BoundSheet::WorkSheet )
		{
			std::unique_ptr< Sheet > sheet( new Sheet( m_sst ) );
			sheet->load( *it, stream );
			m_sheets.push_back( sheet.release() );
		}
	}
}

} /* namespace Excel */

#endif // EXCEL__BOOK_HPP__INCLUDED
