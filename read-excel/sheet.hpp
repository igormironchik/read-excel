
/*!
	\file
	\brief Excel WorkSheet.

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

#ifndef EXCEL__SHEET_HPP__INCLUDED
#define EXCEL__SHEET_HPP__INCLUDED

// Excel include.
#include "cell.hpp"
#include "record.hpp"
#include "bof.hpp"
#include "formula.hpp"
#include "string.hpp"
#include "exceptions.hpp"
#include "storage.hpp"

// C++ include.
#include <vector>
#include <string>


namespace Excel {

//
// BoundSheet
//

//! BoundSheet record.
class BoundSheet {
public:
	//! Sheet's type.
	enum SheetType {
		//! Worksheet.
		WorkSheet = 0x0000,
		//! Excel 4.0 macro sheet.
		MacroSheet = 0x0100,
		//! Chart.
		Chart = 0x0200,
		//! Visual Basic module.
		VisualBasicModule = 0x0600
	}; // enum SheetType

	BoundSheet( int32_t pos,
		SheetType type, const std::wstring & name );

	//! \return BOF position.
	int32_t BOFPosition() const;

	//! \return Sheet's type.
	SheetType sheetType() const;

	//! \return Sheet's name.
	const std::wstring & sheetName() const;

	//! Convert 2-bytes type field to the SheetType.
	static SheetType convertSheetType( int16_t type );

private:
	//! BOF position.
	int32_t m_BOFPosition;
	//! Sheet's type.
	SheetType m_sheetType;
	//! Sheet's name.
	std::wstring m_sheetName;
}; // class BoundSheet


//
// Sheet
//

//! Excel's sheet.
class Sheet {
public:
	explicit Sheet( const std::wstring & name );

	//! \return Cell.
	const Cell & cell( size_t row, size_t column ) const;

	//! \return Row's count.
	size_t rowsCount() const;

	//! \return Column's count.
	size_t columnsCount() const;

	//! Set cell.
	template< typename Value >
	void setCell( size_t row, size_t column, Value value );

	//! \return Name of the sheet.
	const std::wstring & sheetName() const;

private:
	//! Init cell's table with given cell.
	void initCell( size_t row, size_t column );

private:
	//! Cells.
	std::vector< std::vector< Cell > > m_cells;
	//! Dummy cell.
	Cell m_dummyCell;
	//! Column's count;
	size_t m_columnsCount;
	//! Name of the sheet.
	std::wstring m_name;
}; // class Sheet

//
// BoundSheet
//

//! Sheet's type.
enum SheetType {
	//! Worksheet.
	WorkSheet = 0x0000,
	//! Excel 4.0 macro sheet.
	MacroSheet = 0x0100,
	//! Chart.
	Chart = 0x0200,
	//! Visual Basic module.
	VisualBasicModule = 0x0600
}; // enum SheetType

inline
BoundSheet::BoundSheet( int32_t pos,
	SheetType type, const std::wstring & name )
	:	m_BOFPosition( pos )
	,	m_sheetType( type )
	,	m_sheetName( name )
{
}

inline int32_t
BoundSheet::BOFPosition() const
{
	return m_BOFPosition;
}

inline BoundSheet::SheetType
BoundSheet::sheetType() const
{
	return m_sheetType;
}

inline const std::wstring &
BoundSheet::sheetName() const
{
	return m_sheetName;
}

inline BoundSheet::SheetType
BoundSheet::convertSheetType( int16_t type )
{
	return ( (SheetType) ( type & 0xFF00 ) );
}


//
// Sheet
//

inline
Sheet::Sheet( const std::wstring & name )
	:	m_columnsCount( 0 )
	,	m_name( name )
{
}

template< typename Value >
inline void
Sheet::setCell( size_t row, size_t column, Value value )
{
	initCell( row, column );
	m_cells[ row ][ column ].setData( value );
}

inline const std::wstring &
Sheet::sheetName() const
{
	return m_name;
}

inline void
Sheet::initCell( size_t row, size_t column )
{
	if( m_cells.size() < row + 1 )
		m_cells.resize( row + 1 );

	if( m_cells[ row ].size() < column + 1 )
	{
		if( column + 1 > m_columnsCount )
			m_columnsCount = column + 1;

		for( std::vector< std::vector< Cell > >::iterator it = m_cells.begin(),
			last = m_cells.end(); it != last; ++it )
		{
			it->resize( m_columnsCount );
		}
	}
}

inline const Cell &
Sheet::cell( size_t row, size_t column ) const
{
	if( m_cells.size() > 0 )
	{
		if( m_cells.size() - 1 < row || m_cells[ 0 ].size() - 1 < column )
			return m_dummyCell;
		else
			return m_cells[ row ][ column ];
	}

	return m_dummyCell;
}

inline size_t
Sheet::rowsCount() const
{
	return m_cells.size();
}

inline size_t
Sheet::columnsCount() const
{
	return m_columnsCount;
}

} /* namespace Excel */

#endif // EXCEL__SHEET_HPP__INCLUDED

