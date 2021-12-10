
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
#include "sheet.hpp"
#include "record.hpp"
#include "string.hpp"
#include "bof.hpp"
#include "exceptions.hpp"
#include "stream.hpp"
#include "parser.hpp"

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
class Book : public IStorage {
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
	explicit Book( std::istream & stream );
	explicit Book( const std::string & fileName );
	~Book();

protected:
	void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) override;
	void onDateMode( uint16_t mode ) override;
	void onSheet( size_t idx, const std::wstring & value ) override;
	void onCellSharedString( size_t sheetIdx, size_t row, size_t column, size_t sstIndex ) override;
	void onCell( size_t sheetIdx, size_t row, size_t column, const std::wstring & value ) override;
	void onCell( size_t sheetIdx, size_t row, size_t column, double value ) override;
	void onCell( size_t sheetIdx, const Formula & value ) override;

public:
	//! \return Date mode.
	DateMode dateMode() const;

	//! \return Count of the sheets.
	size_t sheetsCount() const;

	//! \return Sheet with given index,
	//! or NULL if there is no sheet with such index.
	Sheet * sheet( size_t index ) const;

	//! Clear book.
	void clear();

private:
	//! Parsed WorkSheets.
	std::vector< std::unique_ptr< Sheet > > m_sheets;
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
Book::Book( std::istream & stream )
	:	m_dateMode( DateMode::Unknown )
{
	static_assert( sizeof( double ) == 8,
		"Unsupported platform: double has to be 8 bytes." );

	Parser::loadBook( stream, *this );
}

inline
Book::Book( const std::string & fileName )
	:	m_dateMode( DateMode::Unknown )
{
	static_assert( sizeof( double ) == 8,
		"Unsupported platform: double has to be 8 bytes." );

	std::ifstream fileStream( fileName, std::ios::in | std::ios::binary );
	Parser::loadBook( fileStream, *this, fileName );
}

inline void
Book::clear()
{
	m_sheets.clear();
	m_sst.clear();
}

inline
Book::~Book()
{
}

inline Book::DateMode
Book::dateMode() const
{
	return m_dateMode;
}

inline void
Book::onSharedString( size_t sstSize, size_t idx, const std::wstring & value )
{
	m_sst.resize( sstSize );
	m_sst[ idx ] = value;
}

inline void
Book::onDateMode( uint16_t mode )
{
	if( mode )
		m_dateMode = DateMode::Jan01_1904;
	else
		m_dateMode = DateMode::Dec31_1899;
}

inline void
Book::onSheet( size_t idx, const std::wstring & )
{
	auto sheet = std::make_unique< Sheet > ();
	if( m_sheets.size() <= idx )
		m_sheets.resize( idx + 1 );
	m_sheets[ idx ] = std::move( sheet );
}

inline void
Book::onCellSharedString( size_t sheetIdx, size_t row, size_t column, size_t sstIndex )
{
	onCell( sheetIdx, row, column, m_sst[ sstIndex ] );
}

inline void
Book::onCell( size_t sheetIdx, size_t row, size_t column, const std::wstring & value )
{
	sheet( sheetIdx )->setCell( row, column, value );
}

inline void
Book::onCell( size_t sheetIdx, size_t row, size_t column, double value )
{
	sheet( sheetIdx )->setCell( row, column, value );
}

inline void
Book::onCell( size_t sheetIdx, const Formula & formula )
{
	sheet( sheetIdx )->setCell( formula.getRow(), formula.getColumn(), formula );
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
		return m_sheets[ index ].get();

	std::wstringstream stream;
	stream << L"There is no such sheet with index : " << index;

	throw Exception( stream.str() );
}

} /* namespace Excel */

#endif // EXCEL__BOOK_HPP__INCLUDED
