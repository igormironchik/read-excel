from conans import ConanFile


class ArgsConan(ConanFile):
    name = "excel"
    version = "1.1.4"
    url = "https://github.com/igormironchik/read-excel.git"
    license = "MIT"
    description = "This is very simple implementation of the Excel 97-2003 format (BIFF8) " \
                  "written in C++. Supported reading only."
    exports = "excel/*.hpp", "COPYING"

    def package(self):
        self.copy("COPYING", src=".", dst=".")
        self.copy("*.hpp", src="excel", dst="excel")
        
    def package_info(self):
        self.cpp_info.includedirs = ["."]
