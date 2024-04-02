
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
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
	virtual ~IStorage() = default;

protected:
	friend class Parser;

	//! Handler of SST.
	virtual void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) = 0;
	//! Handler of date mode.
	virtual void onDateMode( uint16_t mode ) = 0;
	//! Handler of sheet.
	virtual void onSheet( size_t idx, const std::wstring & value ) = 0;
	//! Handler of cell with text from SST.
	virtual void onCellSharedString( size_t sheetIdx, size_t row, size_t column, size_t sstIndex ) = 0;
	//! Handler of cell with text.
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, const std::wstring & value ) = 0;
	//! Handler of cell with double.
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, double value ) = 0;
	//! Handler of cell with formula.
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
