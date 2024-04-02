
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef COMPOUNDFILE__EXCEPTIONS_HPP__INCLUDED
#define COMPOUNDFILE__EXCEPTIONS_HPP__INCLUDED


// C++ include.
#include <stdexcept>
#include <string>


namespace CompoundFile {

//
// Exception
//

//! Base exception in the compound file.
class Exception
	:	public std::runtime_error
{
public:
	explicit Exception( const std::wstring & what );
	virtual ~Exception() noexcept;

	//! \return Reason of the exception.
	const std::wstring & whatAsWString() const noexcept;

private:
	//! Reason of the exception.
	std::wstring m_what;
}; // class Exception

inline
Exception::Exception( const std::wstring & what )
	:	std::runtime_error( "Use whatAsWString() method." )
	,	m_what( what )
{
}

inline
Exception::~Exception() noexcept
{
}

inline const std::wstring &
Exception::whatAsWString() const noexcept
{
	return m_what;
}

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__EXCEPTIONS_HPP__INCLUDED
