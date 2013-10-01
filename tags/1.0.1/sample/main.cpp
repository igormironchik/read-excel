
/*!
	\file
	\brief Sample.

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


// Excel include.
#include <excel/h/book.hpp>
#include <excel/h/exceptions.hpp>

// C++ include.
#include <iostream>


using namespace Excel;


void main()
{
	Book book( L"sample.xls" );

	Sheet * sheet = book.sheet( 0 );

	std::wcout << L"There is output of the \"sample.xls\" Excel file."
		<< std::endl << std::endl;

	std::wcout << L"A1 : " << sheet->cell( 0, 0 ).getString() << std::endl;
	std::wcout << L"A2 : " << sheet->cell( 1, 0 ).getString()
		<< L" B2 : " << sheet->cell( 1, 1 ).getDouble() << std::endl;
	std::wcout << L"A3 : " << sheet->cell( 2, 0 ).getString()
		<< L" B3 : " << sheet->cell( 2, 1 ).getDouble() << std::endl;
	std::wcout << L"A4 : " << sheet->cell( 3, 0 ).getString()
		<< L" B4 : " << sheet->cell( 3, 1 ).getFormula().getDouble() << std::endl;

	std::wcout << std::endl << L"Thats all. And thanks for using this library."
		<< std::endl;
}
