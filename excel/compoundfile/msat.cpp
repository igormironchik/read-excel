
/*!
	\file
	\brief Master sector allocation table in the compound file.

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

// CompoundFile include.
#include <excel/compoundfile/h/msat.hpp>
#include <excel/compoundfile/h/utils.hpp>


namespace CompoundFile {

//
// MSAT
//

MSAT::MSAT( const Header & header,
	 std::istream & stream )
	:	m_header( header )
	,	m_stream( stream )
{
	loadMSAT();
}

SAT
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

namespace /* anonymous */ {

//
// loadFirst109SecIDs
//

//! Load first 109 SecIDs.
std::vector< SecID >
loadFirst109SecIDs( std::istream & stream )
{
	std::vector< SecID > msat;

	for( int i = 0; i < 109; ++i )
	{
		int secID = 0;

		readData( stream, secID, 4 );

		if( secID != SecID::FreeSecID )
			msat.push_back( secID );
	}

	return msat;
} // loadFirst109SecIDs


//
// loadMSATSector
//

void
loadMSATSector( std::istream & stream, std::vector< SecID > & msat,
	SecID & nextMSATSectorID, size_t sectorSize )
{
	const int secIDCount = ( sectorSize - 4 ) / 4;

	for( int i = 0; i < secIDCount; ++i )
	{
		int secID = 0;

		readData( stream, secID, 4 );

		msat.push_back( secID );
	}

	int nextSecID = 0;

	readData( stream, nextSecID, 4 );

	nextMSATSectorID = nextSecID;
}

} /* namespace anonymous */

void
MSAT::loadMSAT()
{
	m_msat = loadFirst109SecIDs( m_stream );

	const size_t msatSectorsCount = m_header.sectorsInMSAT();

	SecID id = m_header.msatFirstSecID();

	for( size_t i = 0; i < msatSectorsCount; ++i )
	{
		m_stream.seekg( calcFileOffset( id, m_header.sectorSize() ) );

		loadMSATSector( m_stream, m_msat, id, m_header.sectorSize() );
	}
}

} /* namespace CompoundFile */
