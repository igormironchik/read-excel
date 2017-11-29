require 'rubygems'

gem 'Mxx_ru', '>= 1.4.7'

require 'mxx_ru/cpp'

MxxRu::Cpp::composite_target() {

	if( "vc" != toolset.name )
		required_prj( "test/header/prj.ut.rb" )
		required_prj( "test/compoundfile/prj.ut.rb" )
	end

	required_prj( "test/bof/prj.ut.rb" )
	required_prj( "test/book/prj.ut.rb" )
	required_prj( "test/cell/prj.ut.rb" )
	required_prj( "test/record/prj.ut.rb" )
	required_prj( "test/sst/prj.ut.rb" )
	required_prj( "test/string/prj.ut.rb" )
	required_prj( "test/formula/prj.ut.rb" )
	required_prj( "test/datetime/prj.ut.rb" )
}
