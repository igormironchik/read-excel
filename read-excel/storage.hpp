/*!
	\file
	\brief Excel storage interface.

	\author Gennadii Marianychenko (argent dot genesis at gmail dot com).

	Copyright (c) 2021 Gennadii Marianychenko

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

#pragma once
// C++ include.
#include <string>

// Excel include.
#include "formula.hpp"

namespace Excel {

//
// IStorage
//

//! Excel storage interface.
struct IStorage {
	~IStorage() {}
protected:
	friend class Parser;

	virtual void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) = 0;
	virtual void onDateMode( uint16_t mode ) = 0;
	virtual void onSheet( size_t idx, const std::wstring & value ) = 0;
	virtual void onCellSharedString( size_t sheetIdx, size_t row, size_t column, size_t sstIndex ) = 0;
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, const std::wstring & value ) = 0;
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, double value ) = 0;
	virtual void onCell( size_t sheetIdx, const Formula & value ) = 0;
}; // struct IStorage

struct EmptyStorage : public IStorage {
protected:
	void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) override {}
	void onDateMode( uint16_t mode ) override {}
	void onSheet( size_t idx, const std::wstring & value ) override {}
	void onCellSharedString( size_t sheetIdx, size_t row, size_t column, size_t sstIndex ) override {}
	void onCell( size_t sheetIdx, size_t row, size_t column, const std::wstring & value ) override {}
	void onCell( size_t sheetIdx, size_t row, size_t column, double value ) override {}
	void onCell( size_t sheetIdx, const Formula & value ) override {}
}; // struct EmptyStorage

} /* namespace Excel */
