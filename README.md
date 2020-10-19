[![Build](https://github.com/igormironchik/read-excel/workflows/build/badge.svg)](https://github.com/igormironchik/read-excel/actions)[![codecov](https://codecov.io/gh/igormironchik/read-excel/branch/master/graph/badge.svg)](https://codecov.io/gh/igormironchik/read-excel)[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

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

