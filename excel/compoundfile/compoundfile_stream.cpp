
/*!
	\file
	\brief Stream in the compound file.

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

// CompoundFile include.
#include "compoundfile_stream.hpp"
#include "sat.hpp"
#include "directory.hpp"
#include "utils.hpp"


namespace CompoundFile {

//
// Stream
//

Stream::Stream( const Header & header,
	const SAT & sat,
	const SecID & secID,
	std::istream & stream )
	:	Excel::Stream( header.byteOrder() )
	,	m_header( header )
	,	m_stream( stream )
	,	m_mode( LargeStream )
	,	m_bytesReaded( 0 )
	,	m_sectorSize( m_header.sectorSize() )
	,	m_sectorBytesReaded( 0 )
	,	m_shortSecIDIdx( 0 )
	,	m_largeSecIDIdx( 0 )
	,	m_streamSize( 0 )
{
	m_largeStreamChain = sat.sectors( secID );

	m_stream.seekg( calcFileOffset( m_largeStreamChain.front(),
		m_sectorSize ) );

	m_streamSize = m_largeStreamChain.size() * m_sectorSize;
}

Stream::Stream( const Header & header,
	const SAT & sat,
	const SAT & ssat,
	const Directory & dir,
	const SecID & shortStreamFirstSector,
	std::istream & cstream )
	:	Excel::Stream( header.byteOrder() )
	,	m_header( header )
	,	m_stream( cstream )
	,	m_mode(
		( static_cast< size_t > ( dir.streamSize() ) < m_header.streamMinSize() ?
			ShortStream : LargeStream ) )
	,	m_bytesReaded( 0 )
	,	m_sectorSize(
		( static_cast< size_t > ( dir.streamSize() ) < m_header.streamMinSize() ?
			m_header.shortSectorSize() : m_header.sectorSize() ) )
	,	m_sectorBytesReaded( 0 )
	,	m_shortSecIDIdx( 0 )
	,	m_largeSecIDIdx( 0 )
	,	m_streamSize( dir.streamSize() )
{
	if( m_mode == LargeStream )
	{
		m_largeStreamChain = sat.sectors( dir.streamSecID() );
		m_stream.seekg( calcFileOffset( m_largeStreamChain.front(),
			m_header.sectorSize() ) );
	}
	else
	{
		m_largeStreamChain = sat.sectors( shortStreamFirstSector );
		m_shortStreamChain = ssat.sectors( dir.streamSecID() );

		SecID largeSector;
		const int32_t offset = whereIsShortSector( dir.streamSecID(),
			largeSector );

		std::streampos pos = calcFileOffset( largeSector,
			m_header.sectorSize() );
		pos += offset * m_header.shortSectorSize();

		m_stream.seekg( pos );
	}
}

bool
Stream::eof() const
{
	return ( m_bytesReaded == m_streamSize );
}

void
Stream::seek( int32_t pos, SeekType type )
{
	if( type == FromCurrent )
	{
		pos += m_bytesReaded;

		if( pos < 0 )
			pos += m_streamSize;
	}
	else if( type == FromEnd && pos > 0 )
		pos = m_streamSize - pos;
	else if( type == FromEnd && pos < 0 )
		pos = std::abs( pos );
	else if( type == FromBeginning && pos < 0 )
		pos = m_streamSize - pos;

	if( pos >= m_streamSize )
	{
		m_bytesReaded = m_streamSize;
		return;
	}

	const int32_t offset = pos % m_sectorSize;
	const int32_t sectorIdx = pos / m_sectorSize;
	
	m_bytesReaded = pos;
	m_sectorBytesReaded = offset;
	
	if( m_mode == LargeStream )
	{
		m_largeSecIDIdx = sectorIdx;
		
		m_stream.seekg( calcFileOffset( m_largeStreamChain.at( m_largeSecIDIdx ),
			m_sectorSize ) + offset, std::ios::beg );
	}
	else
	{
		const SecID shortSector = m_shortStreamChain.at( sectorIdx );
		
		SecID largeSector;
		const int32_t offsetInLargeSector = whereIsShortSector( shortSector,
			largeSector );

		m_shortSecIDIdx = sectorIdx;

		std::streampos pos = calcFileOffset( largeSector,
			m_header.sectorSize() );
		pos += offsetInLargeSector * m_header.shortSectorSize();
		pos += offset;

		m_stream.seekg( pos, std::ios::beg );
	}
}

int32_t
Stream::pos()
{
	if( eof() )
		return -1;
	else
		return m_bytesReaded;
}

int32_t
Stream::whereIsShortSector( const SecID & shortSector,
	SecID & largeSector )
{
	const int32_t shortSectorsInLarge =
		m_header.sectorSize() / m_header.shortSectorSize();

	const int32_t idxOfTheShortSector =
		SAT::indexOfTheSecID( shortSector, m_shortStreamChain );

	const int32_t offset = idxOfTheShortSector % shortSectorsInLarge;

	const int32_t largeSectorIdx = idxOfTheShortSector / shortSectorsInLarge;

	largeSector = m_largeStreamChain.at( largeSectorIdx );

	return offset;
}

void
Stream::seekToNextSector()
{
	if( m_mode == LargeStream )
	{
		++m_largeSecIDIdx;

		m_stream.seekg( calcFileOffset( m_largeStreamChain.at( m_largeSecIDIdx ),
			m_sectorSize ), std::ios::beg );
	}
	else
	{
		++m_shortSecIDIdx;

		SecID largeSector;
		const int32_t offset =
			whereIsShortSector( m_shortStreamChain.at( m_shortSecIDIdx ),
				largeSector );

		std::streampos pos = calcFileOffset( largeSector,
			m_header.sectorSize() );
		pos += offset * m_header.shortSectorSize();

		m_stream.seekg( pos, std::ios::beg );
	}
}

char
Stream::getByte()
{
	if( eof() )
		return 0xFFu;

	if( m_sectorBytesReaded == m_sectorSize )
	{
		m_sectorBytesReaded = 0;

		seekToNextSector();
	}

	char ch;
	m_stream.get( ch );

	++m_sectorBytesReaded;
	++m_bytesReaded;

	return ch;
}

} /* namespace CompoundFile */
