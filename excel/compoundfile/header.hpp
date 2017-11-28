
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

#ifndef COMPOUNDFILE__HEADER_HPP__INCLUDED
#define COMPOUNDFILE__HEADER_HPP__INCLUDED

// CompoundFile include.
#include "sat.hpp"

// Excel include.
#include "../stream.hpp"

// C++ include.
#include <istream>


namespace CompoundFile {

//
// Header
//

//! Header of the compound file.
class Header {

	friend class File;

public:
	Header();
	Header( std::istream & stream );

	//! \return Byte order in the file.
	Excel::Stream::ByteOrder byteOrder() const;

	//! \return Size of a sector.
	std::size_t sectorSize() const;

	//! \return Size of a short-sector.
	std::size_t shortSectorSize() const;

	//! \return Total number of sectors used for the sector allocation table.
	std::size_t sectorsInSAT() const;

	//! \return SecID of first sector of the directory stream.
	SecID dirStreamSecID() const;

	//! \return Minimum size of a standard stream.
	std::size_t streamMinSize() const;

	//! \return SecID of first sector of the short-sector allocation table.
	SecID ssatFirstSecID() const;

	//! \return Total number of sectors used for the short-sector allocation table.
	std::size_t sectorsInSSAT() const;

	//! \return SecID of first sector of the master sector allocation table.
	SecID msatFirstSecID() const;

	//! \return Total number of sectors used for the master sector allocation table.
	std::size_t sectorsInMSAT() const;

protected:
	//! Load header from the file.
	void load( std::istream & stream );

private:
	//! Byte order.
	Excel::Stream::ByteOrder m_byteOrder;
	//! Size of a sector.
	std::size_t m_sectorSize;
	//! Size of a short-sector.
	std::size_t m_shortSectorSize;
	//! Total number of sectors used for the sector allocation table.
	std::size_t m_sectorsInSAT;
	//! SecID of first sector of the directory stream.
	SecID m_dirStreamSecID;
	//! Minimum size of a standard stream.
	std::size_t m_streamMinSize;
	//! SecID of first sector of the short-sector allocation table.
	SecID m_ssatFirstSecID;
	//! Total number of sectors used for the short-sector allocation table.
	std::size_t m_sectorsInSSAT;
	//! SecID of first sector of the master sector allocation table.
	SecID m_msatFirstSecID;
	//! Total number of sectors used for the master sector allocation table.
	std::size_t m_sectorsInMSAT;
}; // class Header

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__HEADER_HPP__INCLUDED
