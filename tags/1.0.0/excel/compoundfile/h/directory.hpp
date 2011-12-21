
/*!
	\file
	\brief Directory in the compound file.

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

#ifndef COMPOUNDFILE__DIRECTORY_HPP__INCLUDE
#define COMPOUNDFILE__DIRECTORY_HPP__INCLUDE

// CompoundFile include.
#include <excel/compoundfile/h/sat.hpp>

// C++ include
#include <string>


namespace CompoundFile {

class Stream;


//
// Directory
//

//! Directory in a compound file.
class Directory {
public:
	Directory();

	//! Type of the entry.
	enum Type {
		//! Empty.
		Empty = 0x00,
		//! User storage.
		UserStorage = 0x01,
		//! User stream.
		UserStream = 0x02,
		//! LockBytes.
		LockBytes = 0x03,
		//! Property.
		Property = 0x04,
		//! Root storage.
		RootStorage = 0x05
	}; // enum Type

	//! \return Name of the directory.
	const std::wstring & name() const;

	//! \return Type of the directory.
	Type type() const;

	//! \return SecID of the first sector.
	SecID streamSecID() const;

	//! \return Stream size.
	int streamSize() const;

	//! \return DirID of the right child node.
	int rightChild() const;

	//! \return DirID of the left child node.
	int leftChild() const;

	//! \return DirID of the root node.
	int rootNode() const;

	//! Load directory.
	void load( Stream & stream );

private:
	//! Name of the directory.
	std::wstring m_name;
	//! Type of the directory.
	Type m_type;
	//! SecID of the first sector.
	SecID m_secID;
	//! Stream size.
	int m_streamSize;
	//! DirID of the right child node.
	int m_rightChild;
	//! DirID of the left child node.
	int m_leftChild;
	//! DirID of the root node.
	int m_rootNode;
}; // class Directory

} /* namespace CompoundFile */

#endif // COMPOUNDFILE__DIRECTORY_HPP__INCLUDE
