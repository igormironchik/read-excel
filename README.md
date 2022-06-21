[![Build](https://github.com/igormironchik/read-excel/workflows/build/badge.svg)](https://github.com/igormironchik/read-excel/actions)[![codecov](https://codecov.io/gh/igormironchik/read-excel/branch/master/graph/badge.svg)](https://codecov.io/gh/igormironchik/read-excel)[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

This is very simple implementation of the Excel 97-2003 format (BIFF8) written in C++.
Supported reading only.

Partially supported reading of BIFF7 standard (Excel 95). If in global will be set BIFF7, and in worksheets
will be set BIFF8, as in `test/data/strange.xls`, then such file will be loaded. This feature is tested less
of all, so if you will find an issue, please commit a new issue. For BIFF7 support implemented reading of
`LABEL` records, cell with non-unicode string. I found difference between the documentation that I have and
actual record in XLS file, so I implemented by experimenting with real file, that opens with Libre Office,
MS Office and Google Sheets, so I believe that there is an issue in the documentation of `LABEL` record.

Thanks for using this library.

# Comparison

I found on GitHub pure C [libxls](https://github.com/libxls/libxls) library with almost identical
functionality. Dry numbers say that `test/complex` test with `read-excel` runs by 326 ms,
whereas this test with `libxls` runs by 302 ms, what is almost identical.
But C++ this is higher abstraction, that allows to use `read-excel` more developer
friendly, and `read-excel` is cross-platform out of the box.

# Example

```cpp
try {
	Excel::Book book( "sample.xls" );

	Excel::Sheet * sheet = book.sheet( 0 );

	std::wcout << L"There is output of the \"sample.xls\" Excel file."
		<< std::endl << std::endl;

	std::wcout << L"A1 : " << sheet->cell( 0, 0 ).getString()
		<< std::endl;
	std::wcout << L"A2 : " << sheet->cell( 1, 0 ).getString()
		<< L" B2 : " << sheet->cell( 1, 1 ).getDouble() << std::endl;
	std::wcout << L"A3 : " << sheet->cell( 2, 0 ).getString()
		<< L" B3 : " << sheet->cell( 2, 1 ).getDouble() << std::endl;
	std::wcout << L"A4 : " << sheet->cell( 3, 0 ).getString()
		<< L" B4 : " << sheet->cell( 3, 1 ).getFormula().getDouble()
		<< std::endl;
	std::wcout << L"A5 : " << sheet->cell( 4, 0 ).getString()
		<< std::endl << L"Date mode is : "
		<< ( book.dateMode() == Excel::Book::DateMode::Dec31_1899 ?
				L"count of days since 31 December 1899 :" :
				L"count of days since 01 January 1904 :" )
		<< L" B5 : " << sheet->cell( 4, 1 ).getDouble()
		<< " days." << std::endl;

	std::wcout << std::endl << L"Thats all. And thanks for using this library."
		<< std::endl;
}
catch( const Excel::Exception & x )
{
	std::wcout << x.whatAsWString() << std::endl;
}
catch( const std::exception & )
{
	std::wcout << L"Can't open file." << std::endl;
}
```
