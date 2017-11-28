
/*!
	\file
	\brief Excel WorkBook.

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

#ifndef EXCEL__BOOK_HPP__INCLUDED
#define EXCEL__BOOK_HPP__INCLUDED

// Excel include.
#include "sst.hpp"
#include "sheet.hpp"

// C++ include.
#include <vector>
#include <string>


namespace Excel {

class Record;
class Stream;


//
// Book
//

//! Excel WorkBook.
class Book {
public:
	Book();
	explicit Book( const std::string & fileName );
	~Book();

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

private:
	//! Parsed WorkSheets.
	std::vector< Sheet* > m_sheets;
	//! Shared string table.
	std::vector< std::wstring > m_sst;
}; // class Book

} /* namespace Excel */

#endif // EXCEL__BOOK_HPP__INCLUDED
