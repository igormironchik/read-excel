
/*!
	\file
	\brief Excel WorkSheet.

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2014 Igor Mironchik

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

// C++ include.
#include <vector>
#include <string>


namespace Excel {

class BOF;
class Record;
class Stream;


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

	BoundSheet( int pos,
		SheetType type, const std::wstring & name );

	//! \return BOF position.
	int BOFPosition() const;

	//! \return Sheet's type.
	SheetType sheetType() const;

	//! \return Sheet's name.
	const std::wstring & sheetName() const;

	//! Convert 2-bytes type field to the SheetType.
	static SheetType convertSheetType( int16_t type );

private:
	//! BOF position.
	int m_BOFPosition;
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
	explicit Sheet( const std::vector< std::wstring > & sst );

	//! \return Cell.
	const Cell & cell( size_t row, size_t column ) const;

	//! \return Row's count.
	size_t rowsCount() const;

	//! \return Column's count.
	size_t columnsCount() const;

	//! Load sheet.
	void load( const BoundSheet & boundSheet,
		Stream & stream );

private:
	//! Init cell's table.
	void initCells( size_t rows, size_t columns );
	//! Init cell's table with given cell.
	void initCell( size_t row, size_t column );
	//! Handle DIMENSIONS record.
	void handleDimensions( const BOF & bof,
		Record & record );
	//! Handle LABELSST record.
	void handleLabelSST( Record & record );
	//! Handle RK record.
	void handleRK( Record & record );
	//! Handle MULRK record.
	void handleMULRK( Record & record );
	//! Handle NUMBER record.
	void handleNUMBER( Record & record );
	//! Handle FORMULA record.
	void handleFORMULA( Record & record, Stream & stream );

private:
	//! Cells.
	std::vector< std::vector< Cell > > m_cells;
	//! Dummy cell.
	Cell m_dummyCell;
	//! Shared String Table.
	const std::vector< std::wstring > & m_sst;
	//! Column's count;
	size_t m_columnsCount;
}; // class Sheet

} /* namespace Excel */

#endif // EXCEL__SHEET_HPP__INCLUDED

