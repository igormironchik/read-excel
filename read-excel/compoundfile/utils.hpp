
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
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
inline size_t
calcFileOffset( const SecID & id, size_t sectorSize )
{
	return ( 512 + id * sectorSize );
}


//
// loadSATSector
//

//! Load SAT or SSAT sector.
inline void
loadSATSector( std::istream & stream, std::vector< SecID > & sat,
	int32_t sectorSize )
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

#endif // COMPOUNDFILE__UTILS_HPP__INCLUDED
