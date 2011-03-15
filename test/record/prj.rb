require 'rubygems'

gem 'Mxx_ru', '>= 1.4.7'

require 'mxx_ru/cpp'

Mxx_ru::Cpp::exe_target {

	rtti_mode( Mxx_ru::Cpp::RTTI_ENABLED )

	required_prj( "excel/prj.rb" )
	required_prj( "test/stream/prj.rb" )

	target( "test/record/test" )

	cpp_source( "main.cpp" )
}
