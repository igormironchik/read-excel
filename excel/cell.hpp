
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

#ifndef EXCEL__CELL_HPP__INCLUDED
#define EXCEL__CELL_HPP__INCLUDED

// Excel include.
#include "formula.hpp"

// C++ include
#include <string>
#include <sstream>


namespace Excel {

//
// Cell
//

//! Excel's cell.
class Cell {
public:
	//! Type of the data.
	enum class DataType {
		//! Unknown.
		Unknown,
		//! String.
		String,
		//! Double.
		Double,
		//! Formula.
		Formula
	}; // enum class DataType

	Cell();

	//! \return Data type.
	DataType dataType() const;

	//! \return String data in the cell.
	const std::wstring & getString() const;

	//! \return Double data in the cell.
	const double & getDouble() const;

	//! \return Formula.
	const Formula & getFormula() const;

	//! Set data.
	void setData( const std::wstring & d );

	//! Set data.
	void setData( const double & d );

	//! Set data.
	void setData( const Formula & f );

	//! \return true if there is no data.
	bool isNull() const;

private:
	//! Cell's string data.
	std::wstring m_stringData;
	//! Cell's double data.
	double m_doubleData;
	//! Cell's formula.
	Formula m_formula;
	//! Is data set.
	bool m_isNull;
	//! Type of the data.
	DataType m_type;
}; // class Cell

inline
Cell::Cell()
	:	m_doubleData( 0.0 )
	,	m_isNull( true )
	,	m_type( DataType::Unknown )
{
}

inline Cell::DataType
Cell::dataType() const
{
	return m_type;
}

inline const std::wstring &
Cell::getString() const
{
	return m_stringData;
}

inline const double &
Cell::getDouble() const
{
	return m_doubleData;
}

inline const Formula &
Cell::getFormula() const
{
	return m_formula;
}

inline void
Cell::setData( const std::wstring & d )
{
	m_stringData = d;
	m_isNull = false;
	m_type = DataType::String;
}

inline void
Cell::setData( const double & d )
{
	m_doubleData = d;
	m_isNull = false;
	m_type = DataType::Double;
}

inline void
Cell::setData( const Formula & f )
{
	m_formula = f;
	m_isNull = false;
	m_type = DataType::Formula;
}

inline bool
Cell::isNull() const
{
	return m_isNull;
}

} /* namespace Excel */

#endif // EXCEL__CELL_HPP__INCLUDED
