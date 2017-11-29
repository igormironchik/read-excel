
/*!
	\file
	\brief Compound file.

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
#include "compoundfile.hpp"
#include "msat.hpp"
#include "utils.hpp"
#include "compoundfile_stream.hpp"
#include "compoundfile_exceptions.hpp"


namespace CompoundFile {

namespace /* anonymous */ {

//
// loadSSAT
//

SAT
loadSSAT( const Header & header, std::istream & stream,
	const SAT & sat )
{
	std::vector< SecID > ssat;

	if( header.ssatFirstSecID() != SecID::EndOfChain )
	{
		std::vector< SecID > chain = sat.sectors( header.ssatFirstSecID() );

		for( std::vector< SecID >::const_iterator it = chain.begin(),
			last = chain.end(); it != last; ++it )
		{
			stream.seekg( calcFileOffset( *it, header.sectorSize() ) );

			loadSATSector( stream, ssat, header.sectorSize() );
		}
	}

	return SAT( ssat );
} // loadSSAT


//! Size of the dir record.
static const int32_t dirRecordSize = 128;


//
// loadChildDir
//

bool
loadChildDir( std::vector< Directory > & dirs,
	int32_t dirID, Stream & stream )
{
	if( dirID != -1 )
	{
		stream.seek( dirID * dirRecordSize, Stream::FromBeginning );

		Directory dir;
		dir.load( stream );

		dirs.push_back( dir );

		return true;
	}

	return false;
} // loadChildDir


//
// loadChildDirectories
//

void
loadChildDirectories( std::vector< Directory > & dirs,
	const Directory & parentDir, Stream & stream )
{
	if( loadChildDir( dirs, parentDir.leftChild(), stream ) )
		loadChildDirectories( dirs, dirs.back(), stream );
	if( loadChildDir( dirs, parentDir.rightChild(), stream ) )
		loadChildDirectories( dirs, dirs.back(), stream );
} // loadChildDirectories

} /* namespace anonymous */


//
// File
//

File::File( const std::string & fileName )
{
	m_stream.open( fileName, std::ios::in | std::ios::binary );

	if( m_stream.good() )
	{
		m_header.load( m_stream );

		MSAT msat( m_header, m_stream );
		m_sat = msat.buildSAT();

		m_ssat = loadSSAT( m_header, m_stream, m_sat );

		Stream stream( m_header, m_sat, m_header.dirStreamSecID(), m_stream );

		Directory root;
		root.load( stream );

		m_shortStreamFirstSector = root.streamSecID();

		stream.seek( root.rootNode() * dirRecordSize, Stream::FromBeginning );

		Directory rootEntry;
		rootEntry.load( stream );
		m_dirs.push_back( rootEntry );

		loadChildDirectories( m_dirs, rootEntry, stream );
	}
	else
		throw Exception( std::wstring( L"Unable to open file : " ) +
			std::wstring( fileName.cbegin(), fileName.cend() ) );
}

File::~File()
{
	m_stream.close();
}

Directory
File::directory( const std::wstring & name ) const
{
	for( std::vector< Directory >::const_iterator it = m_dirs.begin(),
		last = m_dirs.end(); it != last; ++it )
	{
		if( it->name() == name )
			return *it;
	}

	throw Exception( std::wstring( L"There is no such directory : " ) + name );
}

std::unique_ptr< Excel::Stream >
File::stream( const Directory & dir )
{
	return std::unique_ptr< Excel::Stream > ( new Stream( m_header,
		m_sat, m_ssat, dir, m_shortStreamFirstSector, m_stream ) );
}

} /* namespace CompoundFile */
