
/*!
	\file
	\brief Utils.

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

// CompoundFile include.
#include "utils.hpp"



namespace CompoundFile {

//
// calcFileOffset
//

//! Calculate file offset for the given sector.
size_t
calcFileOffset( const SecID & id, size_t sectorSize )
{
	return ( 512 + id * sectorSize );
}


//
// loadSATSector
//

//! Load SAT or SSAT sector.
void
loadSATSector( std::istream & stream, std::vector< SecID > & sat,
	size_t sectorSize )
{
	const int32_t secIDCount = sectorSize / 4;

	for( int32_t i = 0; i < secIDCount; ++i )
	{
		int32_t secID = 0;

		readData( stream, secID, 4 );

		sat.push_back( secID );
	}
} // loadSATSector

} /* namespace CompoundFile */
