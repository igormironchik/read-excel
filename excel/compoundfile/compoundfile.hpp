
/*!
	\file
	\brief Compound file.

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

#ifndef COMPOUNDFILE__COMPOUNDFILE_HPP__INCLUDED
#define COMPOUNDFILE__COMPOUNDFILE_HPP__INCLUDED

// CompoundFile include.
#include "directory.hpp"
#include "compoundfile_stream.hpp"
#include "header.hpp"
#include "sat.hpp"

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
	explicit File( const std::wstring & fileName );
	~File();

	//! \return Directory entry by its name.
	Directory directory( const std::wstring & name ) const;

	//! \return Stream in the directory.
	std::auto_ptr< Excel::Stream > stream( const Directory & dir );

private:
	//! Stream.
	std::ifstream m_stream;
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

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__COMPOUNDFILE_HPP__INCLUDED
