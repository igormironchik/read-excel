[![Build](https://github.com/igormironchik/read-excel/workflows/build/badge.svg)](https://github.com/igormironchik/read-excel/actions)[![codecov](https://codecov.io/gh/igormironchik/read-excel/branch/master/graph/badge.svg)](https://codecov.io/gh/igormironchik/read-excel)[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

This is very simple implementation of the Excel 97-2003 format (BIFF8) written in C++.
Supported reading only.

Partially supported reading of BIFF7 standard (Excel 95). If in global will be set BIFF7, and in worksheets
will be set BIFF8, as in `test/data/strange.xls`, then such file will be loaded. This feature is tested less
of all, so if you will find an issue, please commit a new issue. For BIFF7 support implemented reading of
`LABEL` records, cell with non-unicode string. I found difference between the documentation that I have and
actual record in XLS file, so I implemented by experimenting with real file, that opens with Libre Office,
MS Office and Google Sheets, so I believe that there is and issue in the documentation of `LABEL` record.

Thanks for using this library.
