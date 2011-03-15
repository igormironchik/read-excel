
/*!
	\file
	\brief Excel Record.

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

#ifndef EXCEL__FORMULA_HPP__INCLUDED
#define EXCEL__FORMULA_HPP__INCLUDED

// C++ include.
#include <string>


namespace Excel {

class Record;


//
// Formula
//

//! Formula in the Excel document.
class Formula {
public:
	Formula();
	explicit Formula( Record & record );

	//! Copy operator.
	Formula & operator = ( const Formula & f );

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
		StringValue
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
	short getRow() const;

	//! \return Column index.
	short getColumn() const;

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
	short m_row;
	//! Column index.
	short m_column;
}; // class Formula

} /* namespace Excel */

#endif // EXCEL__FORMULA_HPP__INCLUDED
