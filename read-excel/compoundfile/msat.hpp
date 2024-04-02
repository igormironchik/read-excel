
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMPOUNDFILE__MSAT_HPP__INCLUDED
#define COMPOUNDFILE__MSAT_HPP__INCLUDED

// CompoundFile include.
#include "sat.hpp"
#include "header.hpp"
#include "utils.hpp"

// C++ include.
#include <iostream>


namespace CompoundFile {

//
// MSAT
//

//! MSAT.
class MSAT {

public:
	MSAT( const Header & header,
		 std::istream & stream );

	//! \return SAT.
	SAT buildSAT();

private:
	//! Load MSAT.
	void loadMSAT();

private:
	//! Header.
	const Header & m_header;
	//! File.
	std::istream & m_stream;
	//! MSAT.
	std::vector< SecID > m_msat;
}; // class MSAT

inline
MSAT::MSAT( const Header & header,
	 std::istream & stream )
	:	m_header( header )
	,	m_stream( stream )
{
	loadMSAT();
}

inline SAT
MSAT::buildSAT()
{
	std::vector< SecID > sat;

	for( std::vector< SecID >::const_iterator it = m_msat.begin(),
		last = m_msat.end(); it != last; ++it )
	{
		m_stream.seekg( calcFileOffset( *it, m_header.sectorSize() ) );

		loadSATSector( m_stream, sat, m_header.sectorSize() );
	}

	return SAT( sat );
}


//
// loadFirst109SecIDs
//

//! Load first 109 SecIDs.
inline std::vector< SecID >
loadFirst109SecIDs( std::istream & stream )
{
	std::vector< SecID > msat;

	for( int32_t i = 0; i < 109; ++i )
	{
		int32_t secID = 0;

		readData( stream, secID, 4 );

		if( secID != SecID::FreeSecID )
			msat.push_back( secID );
	}

	return msat;
} // loadFirst109SecIDs


//
// loadMSATSector
//

inline void
loadMSATSector( std::istream & stream, std::vector< SecID > & msat,
	SecID & nextMSATSectorID, int32_t sectorSize )
{
	const int32_t secIDCount = ( sectorSize - 4 ) / 4;

	for( int32_t i = 0; i < secIDCount; ++i )
	{
		int32_t secID = 0;

		readData( stream, secID, 4 );

		msat.push_back( secID );
	}

	int32_t nextSecID = 0;

	readData( stream, nextSecID, 4 );

	nextMSATSectorID = nextSecID;
}

inline void
MSAT::loadMSAT()
{
	m_msat = loadFirst109SecIDs( m_stream );

	const int32_t msatSectorsCount = m_header.sectorsInMSAT();

	SecID id = m_header.msatFirstSecID();

	for( int32_t i = 0; i < msatSectorsCount; ++i )
	{
		m_stream.seekg( calcFileOffset( id, m_header.sectorSize() ) );

		loadMSATSector( m_stream, m_msat, id, m_header.sectorSize() );
	}
}

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__MSAT_HPP__INCLUDED
