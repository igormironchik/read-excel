
/*!
	\file
	\brief Header of the compound file.

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
#include "header.hpp"
#include "compoundfile_exceptions.hpp"
#include "msat.hpp"
#include "utils.hpp"

// C++ include.
#include <iostream>
#include <cstring>


namespace CompoundFile {

//
// Header
//

Header::Header()
	:	m_byteOrder( Excel::Stream::LittleEndian )
	,	m_sectorSize( 0 )
	,	m_shortSectorSize( 0 )
	,	m_sectorsInSAT( 0 )
	,	m_dirStreamSecID( 0 )
	,	m_streamMinSize( 0 )
	,	m_ssatFirstSecID( 0 )
	,	m_sectorsInSSAT( 0 )
	,	m_msatFirstSecID( 0 )
	,	m_sectorsInMSAT( 0 )
{
}

Header::Header( std::istream & stream )
	:	m_byteOrder( Excel::Stream::LittleEndian )
	,	m_sectorSize( 0 )
	,	m_shortSectorSize( 0 )
	,	m_sectorsInSAT( 0 )
	,	m_dirStreamSecID( 0 )
	,	m_streamMinSize( 0 )
	,	m_ssatFirstSecID( 0 )
	,	m_sectorsInSSAT( 0 )
	,	m_msatFirstSecID( 0 )
	,	m_sectorsInMSAT( 0 )
{
	load( stream );
}

Excel::Stream::ByteOrder
Header::byteOrder() const
{
	return m_byteOrder;
}

size_t
Header::sectorSize() const
{
	return m_sectorSize;
}

size_t
Header::shortSectorSize() const
{
	return m_shortSectorSize;
}

size_t
Header::sectorsInSAT() const
{
	return m_sectorsInSAT;
}

SecID
Header::dirStreamSecID() const
{
	return m_dirStreamSecID;
}

size_t
Header::streamMinSize() const
{
	return m_streamMinSize;
}

SecID
Header::ssatFirstSecID() const
{
	return m_ssatFirstSecID;
}

size_t
Header::sectorsInSSAT() const
{
	return m_sectorsInSSAT;
}

SecID
Header::msatFirstSecID() const
{
	return m_msatFirstSecID;
}

size_t
Header::sectorsInMSAT() const
{
	return m_sectorsInMSAT;
}

namespace /* anonymous */ {

//! Compound document file identifier
static const char cIdentifier[] = {
	static_cast< char > ( 0xD0u ),
	static_cast< char > ( 0xCFu ),
	static_cast< char > ( 0x11u ),
	static_cast< char > ( 0xE0u ),
	static_cast< char > ( 0xA1u ),
	static_cast< char > ( 0xB1u ),
	static_cast< char > ( 0x1Au ),
	static_cast< char > ( 0xE1u ),
	static_cast< char > ( 0x00u ) };

//! Byte order identifier.
static const char cLittleEndian[] = {
	static_cast< char > ( 0xFEu ),
	static_cast< char > ( 0xFFu ),
	static_cast< char > ( 0x00u ) };

} /* namespace anonymous */

void
Header::load( std::istream & stream )
{
	{
		char fileID[] =
			{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

		stream.read( fileID, 8 );

		if( std::strcmp( cIdentifier, fileID ) != 0 )
			throw Exception( L"Wrong file identifier. "
				L"It isn't a compound file." );
	}

	stream.seekg( 20, std::ios::cur );

	{
		char byteOrder[] = { 0x00, 0x00, 0x00 };

		stream.read( byteOrder, 2 );

		if( std::strcmp( byteOrder, cLittleEndian ) == 0 )
			m_byteOrder = Excel::Stream::LittleEndian;
		else
			m_byteOrder = Excel::Stream::BigEndian;
	}

	{
		int16_t sectorSizePower = 0;

		readData( stream, sectorSizePower, 2 );

		m_sectorSize = 1 << sectorSizePower;
	}

	{
		int16_t shortSectorSizePower = 0;

		readData( stream, shortSectorSizePower, 2 );

		m_shortSectorSize = 1 << shortSectorSizePower;
	}

	stream.seekg( 10, std::ios::cur );

	{
		int32_t sectorsInSAT = 0;

		readData( stream, sectorsInSAT, 4 );

		m_sectorsInSAT = sectorsInSAT;
	}

	{
		int32_t dirStreamSecID = 0;

		readData( stream, dirStreamSecID, 4 );

		m_dirStreamSecID = dirStreamSecID;
	}

	stream.seekg( 4, std::ios::cur );

	{
		int32_t streamMinSize = 0;

		readData( stream, streamMinSize, 4 );

		m_streamMinSize = streamMinSize;
	}

	{
		int32_t ssatFirstSecID = 0;

		readData( stream, ssatFirstSecID, 4 );

		m_ssatFirstSecID = ssatFirstSecID;
	}

	{
		int32_t sectorsInSSAT = 0;

		readData( stream, sectorsInSSAT, 4 );

		m_sectorsInSSAT = sectorsInSSAT;
	}

	{
		int32_t msatFirstSecID = 0;

		readData( stream, msatFirstSecID, 4 );

		m_msatFirstSecID = msatFirstSecID;
	}

	{
		int32_t sectorsInMSAT = 0;

		readData( stream, sectorsInMSAT, 4 );

		m_sectorsInMSAT = sectorsInMSAT;
	}
}

} /* namespace CompoundFile */
