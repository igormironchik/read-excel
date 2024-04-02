
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef EXCEL__STRING_HPP__INCLUDED
#define EXCEL__STRING_HPP__INCLUDED

// C++ include.
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

// Excel include.
#include "stream.hpp"
#include "bof.hpp"


namespace Excel {

//! Is high byte present in character.
static const char IsHighByte = 0x01;

//! Is extended string follows.
static const char IsExtString = 0x04;

//! Is rich string follows.
static const char IsRichString = 0x08;


//
// isHighByte
//

inline bool
isHighByte( char options )
{
	return ( options & IsHighByte );
} // isHighByte


//
// isExtString
//

inline bool
isExtString( char options )
{
	return ( options & IsExtString );
} // isExtString


//
// isRichString
//

inline bool
isRichString( char options )
{
	return ( options & IsRichString );
} // isRichString


//
// isSkipByte
//

/*!
	If string spleated between two or more records
	there is one byte on the border wich should be
	skipped.
*/

inline bool
isSkipByte( int32_t pos, const std::vector< int32_t > & borders )
{
	return( std::find( borders.begin(), borders.end(), pos ) != borders.end() );
} // isSkipByte


//
// loadString
//

//! Load string from the stream.
inline std::wstring
loadString( Stream & stream,
	const std::vector< int32_t > & borders,
	int32_t lengthFieldSize = 2,
	BOF::BiffVersion biffVer = BOF::BIFF8 )
{
	int16_t charactersCount = 0;
	char options = 0;
	int16_t formattingRuns = 0;
	int32_t extStringLength = 0;

	stream.read( charactersCount, lengthFieldSize );

	if( biffVer == BOF::BIFF7 && charactersCount > 255 )
		throw Exception( L"Wrong format of XLS file." );

	if( biffVer == BOF::BIFF8 )
	{
		stream.read( options, 1 );

		if( isRichString( options ) )
			stream.read( formattingRuns, 2 );

		if( isExtString( options ) )
			stream.read( extStringLength, 4 );
	}

	int16_t bytesPerChar = ( biffVer == BOF::BIFF8 ? ( isHighByte( options ) ? 2 : 1 ) : 1 );

	std::vector< uint16_t > stringData( charactersCount );

	for( int16_t i = 0; i < charactersCount; ++i )
	{
		if( isSkipByte( stream.pos(), borders ) )
		{
			stream.read( options, 1 );
			bytesPerChar = ( biffVer == BOF::BIFF8 ? ( isHighByte( options ) ? 2 : 1 ) : 1 );
		}

		stream.read( stringData[ i ], bytesPerChar );
	}

	if( formattingRuns > 0 )
	{
		const size_t dummySize = formattingRuns * 4;
		std::vector< char > dummy( dummySize );

		for( size_t i = 0; i < dummySize; ++i )
			stream.read( dummy[ i ], 1 );
	}

	if( extStringLength > 0 )
	{
		const size_t dummySize = extStringLength;
		std::vector< char > dummy( dummySize );

		for( size_t i = 0; i < dummySize; ++i )
			stream.read( dummy[ i ], 1 );
	}

	std::wstring str;
	str.assign( stringData.begin(), stringData.end() );

	return str;
}

} /* namespace Excel */

#endif // EXCEL__STRING_HPP__INCLUDED
