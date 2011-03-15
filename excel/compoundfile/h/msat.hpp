
/*!
	\file
	\brief Master sector allocation table in the compound file.

	\author Igor P. Mironchik (imironchick at gmail dot com).

	Copyright (c) 2011 Igor P. Mironchik

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

#ifndef COMPOUNDFILE__MSAT_HPP__INCLUDED
#define COMPOUNDFILE__MSAT_HPP__INCLUDED

// CompoundFile include.
#include <excel/compoundfile/h/sat.hpp>
#include <excel/compoundfile/h/header.hpp>

// C++ include.
#include <iostream>


namespace CompoundFile {

//
// MSAT
//

//! MSAT.
class MSAT {

public:
	MSAT( const Header & header,
		 std::istream & stream );

	//! \return SAT.
	SAT buildSAT();

private:
	//! Load MSAT.
	void loadMSAT();

private:
	//! Header.
	const Header & m_header;
	//! File.
	std::istream & m_stream;
	//! MSAT.
	std::vector< SecID > m_msat;
}; // class MSAT

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__MSAT_HPP__INCLUDED
