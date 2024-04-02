
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/

#ifndef __TEST__HELPERS_HPP__
#define __TEST__HELPERS_HPP__

// C++ include.
#include <array>


template< typename... D  >
std::array< char, sizeof...( D ) > make_data( D... d )
{
	return std::array< char, sizeof...( D ) > ( { static_cast< char > ( d )... } );
}

#endif // __TEST__HELPERS_HPP__
