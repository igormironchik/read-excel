
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
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
