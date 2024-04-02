
/*
	SPDX-FileCopyrightText: 2011-2024 Igor Mironchik <igor.mironchik@gmail.com>
	SPDX-License-Identifier: MIT
*/


#ifndef TEST__DOCUMENT_HPP__INCLUDED
#define TEST__DOCUMENT_HPP__INCLUDED

// C++ include.
#include <sstream>


//
// Document
//

//! Test document.
class Document {
public:
	Document();

	//! \return Document's stream.
	std::stringstream & stream();

private:
	//! Document's stream.
	std::stringstream m_stream;
}; // class Document

#endif // TEST__DOCUMENT_HPP__INCLUDED
