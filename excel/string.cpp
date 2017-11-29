
/*!
	\file
	\brief Excel String.

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

// Excel include.
#include "string.hpp"
#include "stream.hpp"


// C++ include.
#include <algorithm>


namespace Excel {

namespace /* anonymous */ {

//! \name String options masks.
//! \{

//! Is high byte present in character.
char IsHighByte = 0x01;

//! Is extended string follows.
char IsExtString = 0x04;

//! Is rich string follows.
char IsRichString = 0x08;

//! \}


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

} /* namespace anonymous */


//
// loadString
//

//! Load string from the stream.
std::wstring
loadString( Stream & stream,
	const std::vector< int32_t > & borders,
	size_t lengthFieldSize )
{
	int16_t charactersCount = 0;
	char options = 0;
	int16_t formattingRuns = 0;
	int32_t extStringLength = 0;

	stream.read( charactersCount, lengthFieldSize );
	stream.read( options, 1 );

	if( isRichString( options ) )
		stream.read( formattingRuns, 2 );

	if( isExtString( options ) )
		stream.read( extStringLength, 4 );

	int16_t bytesPerChar = ( isHighByte( options ) ? 2 : 1 );

	std::vector< uint16_t > stringData( charactersCount );

	for( int16_t i = 0; i < charactersCount; ++i )
	{
		if( isSkipByte( stream.pos(), borders ) )
		{
			stream.read( options, 1 );
			bytesPerChar = ( isHighByte( options ) ? 2 : 1 );
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
