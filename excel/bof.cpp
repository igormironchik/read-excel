
/*!
	\file
	\brief Excel BOF record.

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
#include "bof.hpp"
#include "record.hpp"


namespace Excel {

//
// BOF
//

BOF::BOF()
	:	m_version( UnknownVersion )
	,	m_type( UnknownType )
{
}

BOF::BiffVersion
BOF::version() const
{
	return m_version;
}

BOF::SubstreamType
BOF::type() const
{
	return m_type;
}

void
BOF::parse( Record & record )
{
	int16_t version = 0;
	int16_t type = 0;

	record.dataStream().read( version, 2 );
	record.dataStream().read( type, 2 );

	switch( version )
	{
		case BIFF8 :
			m_version = BIFF8;
			break;

		case BIFF7 :
			m_version = BIFF7;
			break;

		default :
			m_version = UnknownVersion;
			break;
	}

	switch( type )
	{
		case WorkBookGlobals :
			m_type = WorkBookGlobals;
			break;

		case VisualBasicModule :
			m_type = VisualBasicModule;
			break;

		case WorkSheet :
			m_type = WorkSheet;
			break;

		case Chart :
			m_type = Chart;
			break;

		case MacroSheet :
			m_type = MacroSheet;
			break;

		case WorkSpace :
			m_type = WorkSpace;
			break;

		default :
			m_type = UnknownType;
			break;
	}
}

} /* namespace Excel */
