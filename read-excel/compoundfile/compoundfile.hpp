
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

#ifndef COMPOUNDFILE__COMPOUNDFILE_HPP__INCLUDED
#define COMPOUNDFILE__COMPOUNDFILE_HPP__INCLUDED

// CompoundFile include.
#include "compoundfile_stream_and_dir.hpp"
#include "header.hpp"
#include "sat.hpp"
#include "msat.hpp"
#include "utils.hpp"
#include "compoundfile_exceptions.hpp"

// Excel include.
#include "../stream.hpp"

// C++ include.
#include <string>
#include <vector>
#include <fstream>
#include <memory>


namespace CompoundFile {

//
// File
//

//! Compound file.
class File {
public:
	explicit File( std::istream & stream, const std::string & fileName = "<custom-stream>" );
	explicit File( const std::string & fileName );
	~File();

	//! \return Directory entry by its name.
	Directory directory( const std::wstring & name ) const;

	//! \return is Directory entry exist by its name.
	bool hasDirectory(const std::wstring & name ) const;

	//! \return Stream in the directory.
	std::unique_ptr< Excel::Stream > stream( const Directory & dir );

private:
	//! Read stream and initialize m_dirs.
    void initialize( const std::string& fileName );

private:
	//! Inner file stream.
	std::ifstream m_fileStream;
	//! Stream.
	std::istream & m_stream;
	//! Header of the compound file.
	Header m_header;
	//! SAT.
	SAT m_sat;
	//! SSAT.
	SAT m_ssat;
	//! SecID of the first sector of the short-sector stream.
	SecID m_shortStreamFirstSector;
	//! All directories defined in the compound file.
	std::vector< Directory > m_dirs;
}; // class File


//
// loadSSAT
//

inline SAT
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

inline bool
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

inline void
loadChildDirectories( std::vector< Directory > & dirs,
	const Directory & parentDir, Stream & stream )
{
	if( loadChildDir( dirs, parentDir.leftChild(), stream ) )
		loadChildDirectories( dirs, dirs.back(), stream );
	if( loadChildDir( dirs, parentDir.rightChild(), stream ) )
		loadChildDirectories( dirs, dirs.back(), stream );
} // loadChildDirectories


//
// File
//

inline
File::File( std::istream & stream, const std::string & fileName )
	: m_stream( stream )
{
	initialize( fileName );
}

inline
File::File( const std::string & fileName )
	: m_fileStream( fileName, std::ios::in | std::ios::binary )
	, m_stream( m_fileStream )
	
{
	initialize( fileName );
}

inline
File::~File()
{
	m_fileStream.close();
}

inline Directory
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

inline bool
File::hasDirectory( const std::wstring & name ) const
{
	for( std::vector< Directory >::const_iterator it = m_dirs.begin(),
		last = m_dirs.end(); it != last; ++it )
	{
		if ( it->name() == name )
			return true;
	}

	return false;
}

inline std::unique_ptr< Excel::Stream >
File::stream( const Directory & dir )
{
	return std::unique_ptr< Excel::Stream > ( new Stream( m_header,
		m_sat, m_ssat, dir, m_shortStreamFirstSector, m_stream ) );
}

inline void
File::initialize( const std::string & fileName )
{
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

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__COMPOUNDFILE_HPP__INCLUDED
