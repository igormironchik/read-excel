
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

#ifndef COMPOUNDFILE__STREAM_HPP__INCLUDED
#define COMPOUNDFILE__STREAM_HPP__INCLUDED

// CompoundFile include.
#include "header.hpp"

// Excel include.
#include "../stream.hpp"

// C++ include.
#include <iostream>


namespace CompoundFile {

class SAT;
class Directory;


//
// Stream
//

//! Stream in a compound file.
class Stream
	:	public Excel::Stream
{

	friend class File;

protected:
	Stream( const Header & header,
		const SAT & sat,
		const SecID & secID,
		std::istream & stream );

public:
	Stream( const Header & header,
		const SAT & sat,
		const SAT & ssat,
		const Directory & dir,
		const SecID & shortStreamFirstSector,
		std::istream & cstream );

	//! Read one byte from the stream.
	char getByte();

	//! \return true if EOF reached.
	bool eof() const;

	//! Seek stream to new position.
	void seek( int pos, SeekType type = FromBeginning );

	//! \return Position in the stream.
	int pos();

private:
	//! Seek internal stream to the next sector.
	void seekToNextSector();
	//! \return Offset in sectors from the beginning of the large
	//! stream sector.
	int whereIsShortSector( const SecID & shortSector,
		SecID & largeSector );

private:
	//! Header.
	const Header & m_header;
	//! Large stream sectors chain.
	std::vector< SecID > m_largeStreamChain;
	//! Short stream sectors chain.
	std::vector< SecID > m_shortStreamChain;
	//! File's stream.
	std::istream & m_stream;

	//! Mode of the stream.
	enum Mode {
		//! Large stream mode.
		LargeStream,
		//! Short stream mode.
		ShortStream
	}; // enum Mode

	//! Mode of the stream.
	Mode m_mode;
	//! Bytes readed from the stream.
	int m_bytesReaded;
	//! Size of the sector for this stream.
	int m_sectorSize;
	//! Bytes readed from the current sector.
	int m_sectorBytesReaded;
	//! Current SecID in the short stream.
	int m_shortSecIDIdx;
	//! Current SecID in the large stream.
	int m_largeSecIDIdx;
	//! Size of the stream.
	int m_streamSize;
}; // class Stream

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__STREAM_HPP__INCLUDED
