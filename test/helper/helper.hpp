
/*!
	\file
	\author Igor P. Mironchik (imironchick at gmail dot com).

	Copyright (c) 2011 Igor P. Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __TEST__HELPERS_HPP__
#define __TEST__HELPERS_HPP__

#include <iostream>
#include <stdexcept>
#include <sstream>


namespace /* anonymous */ {

	class unit_test_counter_t {
		private:
			unit_test_counter_t( const unit_test_counter_t & );
			unit_test_counter_t & operator = ( const unit_test_counter_t & );

		protected:
			unit_test_counter_t()
				:	m_counter( 0 )
			{}

			static unit_test_counter_t & instance()
			{
				static unit_test_counter_t counter;
				return counter;
			}

		public:

			static std::size_t unit_test_number()
			{
				++instance().m_counter;

				return instance().m_counter;
			}

		private:
			std::size_t m_counter;
	}; // class unit_test_counter

	inline std::string
	int2str( int v )
	{
		std::ostringstream str;
		str << v;

		return str.str();
	}

	inline void
	check_and_throw( bool check_result,
		const std::string & condition,
		const std::string & file,
		int line )
	{
		if( !check_result )
			throw std::runtime_error( file + ":" + int2str( line )
				+ "\n      ! { " + condition + " } [ FALSE ]" );
	}

} /* namespace anonymous */

#define CHECK_CONDITION(condition) \
check_and_throw( (condition), #condition, __FILE__, __LINE__ );

#define CHECK_THROW__(file, line, exception_class, body)\
do \
	{ \
		bool exception_thrown__ = false; \
		try { \
			body \
		} \
		catch( const exception_class & ) { \
			exception_thrown__ = true; \
		} \
		catch( const std::exception & x ) { \
			throw std::runtime_error( std::string( file ) + ":" \
				+ int2str( line ) \
				+ "\n      ! Expected: " \
				+ #exception_class \
				+ "\n      ! But caught: " \
				+ typeid( x ).name() ); \
		} \
		catch( ... ) { \
			throw std::runtime_error( std::string( file  ) + ":" \
				+ int2str( line ) \
				+ "\n      ! Expected: " \
				+ #exception_class \
				+ "\n      ! But caught: unknown exception" ); \
		} \
		if( !exception_thrown__ ) \
			throw std::runtime_error( std::string( file ) + ":" \
				+ int2str( line ) + ": " \
				+ "\n      ! Expected: " \
				+ #exception_class \
				+ "\n      ! But nothing thrown" ); \
	} \
while( false );

#define CHECK_THROW(exception_class, body) \
CHECK_THROW__(__FILE__, __LINE__, exception_class, body )


//
// UNIT_TEST_START
//

#define UNIT_TEST_START


//
// UNIT_TEST_FINISH
//

#define UNIT_TEST_FINISH \
int \
main( int argc, char ** argv ) \
{ \
	return 0; \
}


//
// UNIT_START
//

#define UNIT_START(test_name) \
void \
test_name() \
{ \
	std::cout << "  " << unit_test_counter_t::unit_test_number() << ". " \
		<< #test_name << " ... ";


//
// UNIT_FINISH
//

#define UNIT_FINISH(test_name) \
	std::cout << "[ OK ]" << std::endl; \
} \
\
struct test_name##_t { \
	test_name##_t() \
	{ \
		try \
		{ \
			test_name##(); \
		} \
		catch( const std::exception & x ) \
		{ \
			std::cerr << "[ FAILED ]" << std::endl \
				<< "      ! Unexpected exception: " << typeid( x ).name() << std::endl \
				<< "      ! " << x.what() << std::endl; \
			exit( 2 ); \
		} \
	} \
}; \
\
test_name##_t g_##test_name;

#endif // __TEST__HELPERS_HPP__
