
/*!
	\file
	\brief Excel Record.

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2011-2014 Igor Mironchik

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
#include "record.hpp"
#include "formula.hpp"


namespace Excel {

//
// Formula
//

Formula::Formula()
	:	m_valueType( UnknownValue )
	,	m_doubleValue( 0.0 )
	,	m_errorValue( UnknownError )
	,	m_boolValue( false )
	,	m_row( 0 )
	,	m_column( 0 )
{
}

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

Formula &
Formula::operator =( const Formula & f )
{
	m_valueType = f.valueType();
	m_doubleValue = f.getDouble();
	m_errorValue = f.getErrorValue();
	m_boolValue = f.getBoolean();
	m_stringValue = f.getString();
	m_row = f.getRow();
	m_column = f.getColumn();

	return *this;
}

Formula::ValueType
Formula::valueType() const
{
	return m_valueType;
}

const double &
Formula::getDouble() const
{
	return m_doubleValue;
}

Formula::ErrorValues
Formula::getErrorValue() const
{
	return m_errorValue;
}

bool
Formula::getBoolean() const
{
	return m_boolValue;
}

const std::wstring &
Formula::getString() const
{
	return m_stringValue;
}

void
Formula::setString( const std::wstring & str )
{
	m_stringValue = str;
}

short
Formula::getRow() const
{
	return m_row;
}

short
Formula::getColumn() const
{
	return m_column;
}

void
Formula::parse( Record & record )
{
	record.dataStream().read( m_row, 2 );
	record.dataStream().read( m_column, 2 );

	record.dataStream().seek( 2, Stream::FromCurrent );

	union {
		double m_double;
		long long m_long;
	} doubleAsLongLong;

	record.dataStream().read( doubleAsLongLong.m_long, 8 );

	long long isBool = doubleAsLongLong.m_long & 0xFFFFFFFFFF00FFFF;

	if( isBool == 0xFFFF000000000001 )
	{
		m_boolValue = ( doubleAsLongLong.m_long & 0x0000000000FF0000 ) >> 16;
		m_valueType = BooleanValue;

		return;
	}

	long long isError = doubleAsLongLong.m_long & 0xFFFFFFFFFF00FFFF;

	if( isError == 0xFFFF000000000002 )
	{
		unsigned char error =
			static_cast< unsigned char >
				( ( doubleAsLongLong.m_long & 0x0000000000FF0000 ) >> 16 );

		m_errorValue = (ErrorValues) error;
		m_valueType = ErrorValue;

		return;
	}

	long long isString = doubleAsLongLong.m_long & 0xFFFFFFFFFFFFFFFF;

	if( isString == 0xFFFF000000000000 )
	{
		m_valueType = StringValue;

		return;
	}

	m_doubleValue = doubleAsLongLong.m_double;
	m_valueType = DoubleValue;
}

} /* namespace Excel */
