
/*!
	\file
	\brief Directory in the compound file.

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
#include "directory.hpp"
#include "compoundfile_stream.hpp"


namespace CompoundFile {

class Stream;


//
// Directory
//

Directory::Directory()
	:	m_type( Empty )
	,	m_secID( SecID::EndOfChain )
	,	m_streamSize( 0 )
	,	m_rightChild( -1 )
	,	m_leftChild( -1 )
	,	m_rootNode( -1 )
{
}

const std::wstring &
Directory::name() const
{
	return m_name;
}

Directory::Type
Directory::type() const
{
	return m_type;
}

SecID
Directory::streamSecID() const
{
	return m_secID;
}

int32_t
Directory::streamSize() const
{
	return m_streamSize;
}

int32_t
Directory::rightChild() const
{
	return m_rightChild;
}

int32_t
Directory::leftChild() const
{
	return m_leftChild;
}

int32_t
Directory::rootNode() const
{
	return m_rootNode;
}

void
Directory::load( Stream & stream )
{
	{
		const int16_t maxSymbolsInName = 32;

		int16_t i = 1;

		std::vector< uint16_t > data;
		data.reserve( maxSymbolsInName - 1 );

		for( ; i <= maxSymbolsInName; ++i )
		{
			uint16_t symbol = 0;
			stream.read( symbol, 2 );

			if( symbol != 0 )
				data.push_back( symbol );
			else
				break;
		}

		m_name.assign( data.begin(), data.end() );

		if( i < maxSymbolsInName )
			stream.seek( ( maxSymbolsInName - i ) * 2, Stream::FromCurrent );
	}

	stream.seek( 2, Stream::FromCurrent );
	m_type = (Type)(int32_t) stream.getByte();
	stream.seek( 1, Stream::FromCurrent );
	stream.read( m_leftChild, 4 );
	stream.read( m_rightChild, 4 );
	stream.read( m_rootNode, 4 );
	stream.seek( 36, Stream::FromCurrent );

	{
		int32_t sec = 0;
		stream.read( sec, 4 );
		m_secID = sec;
	}

	stream.read( m_streamSize, 4 );
	stream.seek( 4, Stream::FromCurrent );
}

} /* namespace CompoundFile */
