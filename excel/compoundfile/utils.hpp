
/*!
	\file
	\brief Utils.

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

#ifndef COMPOUNDFILE__UTILS_HPP__INCLUDED
#define COMPOUNDFILE__UTILS_HPP__INCLUDED

// CompoundFile include.
#include "sat.hpp"

// C++ include.
#include <iostream>


namespace CompoundFile {

//
// readData
//

//! Read data from the stream.
template< class Type >
void readData( std::istream & stream, Type & data, size_t bytes = 0 )
{
	data = Type(0);
	if( bytes == 0 ) bytes = sizeof( Type );

	for( size_t i = 0; i < bytes; ++i )
	{
		char c = 0x00;
		stream.get( c );

		data |= (((Type) (unsigned char) c ) << 8*i);
	}
} // readData


//
// calcFileOffset
//

//! Calculate file offset for the given sector.
size_t
calcFileOffset( const SecID & id, size_t sectorSize );


//
// loadSATSector
//

//! Load SAT or SSAT sector.
void
loadSATSector( std::istream & stream, std::vector< SecID > & sat,
	size_t sectorSize );

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__UTILS_HPP__INCLUDED
