
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
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

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__SAT_HPP__INCLUDED
