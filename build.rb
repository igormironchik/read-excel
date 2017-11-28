
require 'rubygems'

gem 'Mxx_ru', '>= 1.4.7'

require 'mxx_ru/cpp'

Mxx_ru::setup_target(
	Mxx_ru::Cpp::Composite_target.new( Mxx_ru::BUILD_ROOT ) {

		global_include_path( "." )
		default_runtime_mode( MxxRu::Cpp::RUNTIME_RELEASE )
		MxxRu::enable_show_brief
		toolset.force_cpp11

#		global_compiler_option '-Zi'
#		global_linker_option '/DEBUG'

		required_prj( "excel/prj.rb" )
		required_prj( "test/prj.rb" )
		required_prj( "sample/prj.rb" )
	}
)
