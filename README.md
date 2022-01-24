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
functionality. Dry numbers say that `test/complex` test with `read-excel` runs by 350 ms,
whereas this test with `libxls` runs by 310 ms, what is almost identical.
But C++ this is higher abstraction, that allows to use `read-excel` more developer
friendly, and `read-excel` is cross-platform out of the box.
