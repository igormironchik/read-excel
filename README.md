[![Build Status](https://travis-ci.org/igormironchik/read-excel.svg?branch=master)](https://travis-ci.org/igormironchik/read-excel)[![Coverage Status](https://coveralls.io/repos/github/igormironchik/read-excel/badge.svg?branch=master)](https://coveralls.io/github/igormironchik/read-excel?branch=master)[![Build status](https://ci.appveyor.com/api/projects/status/qp5re03oy20932ve/branch/master?svg=true)](https://ci.appveyor.com/project/igormironchik/read-excel/branch/master)[![Coverity Scan](https://scan.coverity.com/projects/14470/badge.svg)](https://scan.coverity.com/projects/igormironchik-read-excel)[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

[![Donate](https://liberapay.com/assets/widgets/donate.svg)](https://liberapay.com/imironchik/donate)

This is very simple implementation of the Excel 97-2003 format (BIFF8) written in C++.
Supported reading only.


# COMPILING

 * You should have installed Ruby programming language and installed Mxx_ru gem.
   Run in the command prompt: gem install Mxx_ru.

 * After this you have to configure MxxRu: make "MXX_RU_CPP_TOOLSET" system enveronment
   with "vc9" value, for example if you have Microsoft Visual Studio 9.0 installed. All
   possible values for this enveronment you can see in the documentation for MxxRu
   (https://sourceforge.net/projects/mxxru/files/).

 * And now just run build.rb which is a Ruby program and compillation process will start.

 * Or use QMake, QtCreator.

