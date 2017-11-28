
require 'rubygems'

gem 'Mxx_ru', '>= 1.4.7'

require 'mxx_ru/cpp'

Mxx_ru::Cpp::lib_target {

	rtl_mode( Mxx_ru::Cpp::RTL_SHARED )
	rtti_mode( Mxx_ru::Cpp::RTTI_ENABLED )
	threading_mode( Mxx_ru::Cpp::THREADING_MULTI )

	target( "lib/excel" )

	sources_root( "compoundfile" ) {
		cpp_source( "directory.cpp" )
		cpp_source( "compoundfile_exceptions.cpp" )
		cpp_source( "header.cpp" )
		cpp_source( "msat.cpp" )
		cpp_source( "sat.cpp" )
		cpp_source( "compoundfile_stream.cpp" )
		cpp_source( "compoundfile.cpp" )
		cpp_source( "utils.cpp" )
	}

	cpp_source( "exceptions.cpp" )
	cpp_source( "formula.cpp" )
	cpp_source( "stream.cpp" )
	cpp_source( "book.cpp" )
	cpp_source( "record.cpp" )
	cpp_source( "sheet.cpp" )
	cpp_source( "sst.cpp" )
	cpp_source( "string.cpp" )
	cpp_source( "bof.cpp" )
	cpp_source( "cell.cpp" )
}
