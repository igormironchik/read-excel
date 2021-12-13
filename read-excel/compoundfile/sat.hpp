
/*!
	\file
	\brief Sector allocation table in the compound file.

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2021 Igor Mironchik

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

#ifndef COMPOUNDFILE__SAT_HPP__INCLUDED
#define COMPOUNDFILE__SAT_HPP__INCLUDED

// C++ include.
#include <vector>
#include <cstdint>
#include <string>
#include <sstream>

// CompoundFile include.
#include "compoundfile_exceptions.hpp"


namespace CompoundFile {

//
// SecID
//

//! Sector identifier.
class SecID {
public:
	enum Ids {
		//! Free sector identifier.
		FreeSecID = -1,
		//! End of chain of sectors identifier.
		EndOfChain = -2,
		//! SAT sector identifier.
		SATSecID = -3,
		//! MSAT sector identifier.
		MSATSecID = -4
	}; // enum Ids

public:
	SecID();
	SecID( int32_t id );

	//! Convert SecID into integral value.
	operator int32_t () const;

private:
	//! Integral sector identifier.
	int32_t m_id;
}; // class SecID


//
// SAT
//

//! Sector allocation table.
class SAT {
public:
	SAT();
	explicit SAT( const std::vector< SecID > & sat );

	//! \return Sector allocation table.
	const std::vector< SecID > & sat() const;

	//! \return Chain of sectors for the given stream in the right order.
	std::vector< SecID > sectors( const SecID & firstSector ) const;

	//! \return Index for the given SecID in the chain.
	static std::size_t indexOfTheSecID( const SecID & id,
		const std::vector< SecID > & chain );

private:
	//! SAT.
	std::vector< SecID > m_sat;
}; // class SAT


//
// SecID
//

inline
SecID::SecID()
	:	m_id( EndOfChain )
{}

inline
SecID::SecID( int32_t id )
	:	m_id( id )
{
}

inline
SecID::operator int32_t () const
{
	return m_id;
}


//
// SAT
//

inline
SAT::SAT()
{
}

inline
SAT::SAT( const std::vector< SecID > & sat )
	:	m_sat( sat )
{
}

inline const std::vector< SecID > &
SAT::sat() const
{
	return m_sat;
}

inline std::vector< SecID >
SAT::sectors( const SecID & firstSector ) const
{
	if( firstSector < static_cast< int32_t > ( m_sat.size() ) )
	{
		std::vector< SecID > result;

		result.push_back( firstSector );

		SecID id = m_sat.at( firstSector );

		while( true )
		{
			if( id >= 0 )
				result.push_back( id );
			else
				break;

			id = m_sat.at( id );
		}

		return result;
	}
	else
	{
		std::wstringstream stream;
		stream << L"There is no such sector with id: " << firstSector;

		throw Exception( stream.str() );
	}
}

inline size_t
SAT::indexOfTheSecID( const SecID & id, const std::vector< SecID > & chain )
{
	const size_t chainSize = chain.size();

	for( size_t i = 0; i < chainSize; ++i )
		if( id == chain[ i ] )
			return i;

	std::wstringstream stream;
	stream << L"There is no such sector with id : " << id;

	throw Exception( stream.str() );
}

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__SAT_HPP__INCLUDED
