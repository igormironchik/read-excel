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
	virtual void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) = 0;
	virtual void onDateMode( uint16_t mode ) = 0;
	virtual void onSheet( size_t idx ) = 0;
	virtual void onCellSharedString( size_t sheetIdx, size_t row, size_t column, size_t sstIndex ) = 0;
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, const std::wstring & value ) = 0;
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, double value ) = 0;
	virtual void onCell( size_t sheetIdx, const Formula & value ) = 0;
}; // struct IStorage

struct EmptyStorage : public IStorage {
	virtual void onSharedString( size_t sstSize, size_t idx, const std::wstring & value ) {}
	virtual void onDateMode( uint16_t mode ) {}
	virtual void onSheet( size_t idx ) {}
	virtual void onCellSharedString( size_t sheetIdx, size_t row, size_t column, size_t sstIndex ) {}
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, const std::wstring & value ) {}
	virtual void onCell( size_t sheetIdx, size_t row, size_t column, double value ) {}
	virtual void onCell( size_t sheetIdx, const Formula & value ) {}
}; // struct EmptyStorage

} /* namespace Excel */
