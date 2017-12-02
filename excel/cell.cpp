
/*!
	\file
	\brief Excel Cell.

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

// Excel include.
#include "cell.hpp"

// C++ include.
#include <sstream>


namespace Excel {

//
// Cell
//

Cell::Cell()
	:	m_doubleData( 0.0 )
	,	m_isNull( true )
	,	m_type( DataType::Unknown )
{
}

Cell::DataType
Cell::dataType() const
{
	return m_type;
}

const std::wstring &
Cell::getString() const
{
	return m_stringData;
}

const double &
Cell::getDouble() const
{
	return m_doubleData;
}

const Formula &
Cell::getFormula() const
{
	return m_formula;
}

void
Cell::setData( const std::wstring & d )
{
	m_stringData = d;
	m_isNull = false;
	m_type = DataType::String;
}

void
Cell::setData( const double & d )
{
	m_doubleData = d;
	m_isNull = false;
	m_type = DataType::Double;
}

void
Cell::setData( const Formula & f )
{
	m_formula = f;
	m_isNull = false;
	m_type = DataType::Formula;
}

bool
Cell::isNull() const
{
	return m_isNull;
}

} /* namespace Excel */
