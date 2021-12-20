
/*!
	\file
	\brief Exceptions of the compound file.

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
