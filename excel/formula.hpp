
/*!
	\file
	\brief Excel Record.

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

#ifndef EXCEL__FORMULA_HPP__INCLUDED
#define EXCEL__FORMULA_HPP__INCLUDED

// C++ include.
#include <string>
#include <cstdint>

// Excel include.
#include "record.hpp"


namespace Excel {

//
// Formula
//

//! Formula in the Excel document.
class Formula {
public:
	Formula();
	explicit Formula( Record & record );

	//! Possible tpes of the formula's value.
	enum ValueType {
		//! Unknown value type.
		UnknownValue,
		//! Double value.
		DoubleValue,
		//! Boolean value.
		BooleanValue,
		//! Error value.
		ErrorValue,
		//! String value.
		StringValue,
		//! Empty cell.
		EmptyCell
	}; // enum ValueType

	//! Error values.
	enum ErrorValues {
		//! Unknown error value.
		UnknownError = 0xFF,
		//! #NULL!
		Null = 0x00,
		//! #DIV/0!
		DivZero = 0x07,
		//! #VALUE!
		Value = 0x0F,
		//! #REF!
		Ref = 0x17,
		//! #NAME?
		Name = 0x1D,
		//! #NUM!
		Num = 0x24,
		//! #N/A
		NA = 0x2A
	}; // enum ErrorValues

	//! \return Type of the value.
	ValueType valueType() const;

	//! \return Double value.
	const double & getDouble() const;

	//! \return Error value.
	ErrorValues getErrorValue() const;

	//! \return Boolean value.
	bool getBoolean() const;

	//! \return String value.
	const std::wstring & getString() const;

	//! Set string value.
	void setString( const std::wstring & str );

	//! \return Row index.
	int16_t getRow() const;

	//! \return Column index.
	int16_t getColumn() const;

private:
	//! Parse record.
	void parse( Record & record );

private:
	//! Type of the value.
	ValueType m_valueType;
	//! Double value.
	double m_doubleValue;
	//! Error value.
	ErrorValues m_errorValue;
	//! Boolean value.
	bool m_boolValue;
	//! String value.
	std::wstring m_stringValue;
	//! Row index.
	int16_t m_row;
	//! Column index.
	int16_t m_column;
}; // class Formula

inline
Formula::Formula()
	:	m_valueType( UnknownValue )
	,	m_doubleValue( 0.0 )
	,	m_errorValue( UnknownError )
	,	m_boolValue( false )
	,	m_row( 0 )
	,	m_column( 0 )
{
}

inline
Formula::Formula( Record & record )
	:	m_valueType( UnknownValue )
	,	m_doubleValue( 0.0 )
	,	m_errorValue( UnknownError )
	,	m_boolValue( false )
	,	m_row( 0 )
	,	m_column( 0 )
{
	parse( record );
}

inline Formula::ValueType
Formula::valueType() const
{
	return m_valueType;
}

inline const double &
Formula::getDouble() const
{
	return m_doubleValue;
}

inline Formula::ErrorValues
Formula::getErrorValue() const
{
	return m_errorValue;
}

inline bool
Formula::getBoolean() const
{
	return m_boolValue;
}

inline const std::wstring &
Formula::getString() const
{
	return m_stringValue;
}

inline void
Formula::setString( const std::wstring & str )
{
	m_stringValue = str;
}

inline int16_t
Formula::getRow() const
{
	return m_row;
}

inline int16_t
Formula::getColumn() const
{
	return m_column;
}

inline void
Formula::parse( Record & record )
{
	record.dataStream().read( m_row, 2 );
	record.dataStream().read( m_column, 2 );

	record.dataStream().seek( 2, Stream::FromCurrent );

	union {
		double m_double;
		int64_t m_long;
	} doubleAsLongLong;

	record.dataStream().read( doubleAsLongLong.m_long, 8 );

	unsigned long long isBool = doubleAsLongLong.m_long & 0xFFFFFFFFFF00FFFF;

	if( isBool == 0xFFFF000000000001 )
	{
		m_boolValue = ( doubleAsLongLong.m_long & 0x0000000000FF0000 ) >> 16;
		m_valueType = BooleanValue;

		return;
	}

	unsigned long long isError = doubleAsLongLong.m_long & 0xFFFFFFFFFF00FFFF;

	if( isError == 0xFFFF000000000002 )
	{
		unsigned char error =
			static_cast< unsigned char >
				( ( doubleAsLongLong.m_long & 0x0000000000FF0000 ) >> 16 );

		m_errorValue = (ErrorValues) error;
		m_valueType = ErrorValue;

		return;
	}

	unsigned long long isEmpty = doubleAsLongLong.m_long & 0xFFFFFFFFFF00FFFF;

	if( isEmpty == 0xFFFF000000000003 )
	{
		m_valueType = EmptyCell;

		return;
	}

	unsigned long long isString = doubleAsLongLong.m_long & 0xFFFFFFFFFFFFFFFF;

	if( isString == 0xFFFF000000000000 )
	{
		m_valueType = StringValue;

		return;
	}

	m_doubleValue = doubleAsLongLong.m_double;
	m_valueType = DoubleValue;
}

} /* namespace Excel */

#endif // EXCEL__FORMULA_HPP__INCLUDED
