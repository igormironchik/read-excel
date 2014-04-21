
/*!
	\file
	\brief Excel SharedStringTable.

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
#include "sst.hpp"
#include "record.hpp"
#include "string.hpp"


namespace Excel {

//
// SharedStringTable.
//

std::vector< std::wstring >
SharedStringTable::parse( Record & record )
{
	int totalStrings = 0;
	int uniqueStrings = 0;

	record.dataStream().read( totalStrings, 4 );
	record.dataStream().read( uniqueStrings, 4 );

	std::vector< std::wstring > sst( uniqueStrings );

	for( int i = 0; i < uniqueStrings; ++i )
		sst[ i ] = loadString( record.dataStream(), record.borders() );

	return sst;
}

} /* namespace Excel */
