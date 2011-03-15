
/*!
	\file
	\brief Excel WorkBook.

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
#include <excel/h/book.hpp>
#include <excel/h/record.hpp>
#include <excel/h/string.hpp>
#include <excel/h/bof.hpp>
#include <excel/h/exceptions.hpp>
#include <excel/h/stream.hpp>

#include <excel/compoundfile/h/compoundfile.hpp>
#include <excel/compoundfile/h/directory.hpp>
#include <excel/compoundfile/h/exceptions.hpp>

// C++ include.
#include <memory>
#include <sstream>


namespace Excel {

//
// Book
//

Book::Book()
{
}

Book::Book( const std::wstring & fileName )
{
	loadBook( fileName );
}

Book::~Book()
{
	for( std::vector< Sheet* >::iterator it = m_sheets.begin(),
		last = m_sheets.end(); it != last; ++it )
	{
		delete *it;
		*it = 0;
	}
}

size_t
Book::sheetsCount() const
{
	return m_sheets.size();
}

Sheet *
Book::sheet( size_t index ) const
{
	if( index < m_sheets.size() )
		return m_sheets[ index ];

	std::wstringstream stream;
	stream << L"There is no such sheet with index : " << index;

	throw Exception( stream.str() );
}

void
Book::loadBook( const std::wstring & fileName )
{
	try {
		CompoundFile::File file( fileName );
		std::auto_ptr< Stream > stream = file.stream(
			file.directory( L"Workbook" ) );

		std::vector< BoundSheet > boundSheets;

		loadGlobals( boundSheets, *stream.get() );

		loadWorkSheets( boundSheets, *stream.get() );
	}
	catch( const CompoundFile::Exception & x )
	{
		throw Exception( x.whatAsWString() );
	}
}

void
Book::loadGlobals( std::vector< BoundSheet > & boundSheets,
	Stream & stream )
{
	while( true )
	{
		Record r( stream );

		switch( r.code() )
		{
			case XL_SST:
				m_sst = SharedStringTable::parse( r );
				break;

			case XL_BOUNDSHEET:
				boundSheets.push_back( parseBoundSheet( r ) );
				break;

			case XL_EOF:
				return;

			default:
				break;
		}
	}
}

BoundSheet
Book::parseBoundSheet( Record & record )
{
	int pos = 0;
	short sheetType = 0;
	std::wstring sheetName;

	record.dataStream().read( pos, 4 );

	record.dataStream().read( sheetType, 2 );

	sheetName = loadString( record.dataStream(), record.borders(), 1 );

	return BoundSheet( pos,
		BoundSheet::convertSheetType( sheetType ),
		sheetName );
}

void
Book::loadWorkSheets( const std::vector< BoundSheet > & boundSheets,
	Stream & stream )
{
	for( std::vector< BoundSheet >::const_iterator it = boundSheets.begin(),
		last = boundSheets.end(); it != last; ++it )
	{
		if( it->sheetType() == BoundSheet::WorkSheet )
		{
			std::auto_ptr< Sheet > sheet( new Sheet( m_sst ) );
			sheet->load( *it, stream );
			m_sheets.push_back( sheet.release() );
		}
	}
}

} /* namespace Excel */
