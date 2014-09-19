//The contents of this file are subject to the Mozilla Public License Version 1.1 
//(the "License"); you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//http://www.mozilla.org/MPL/
//
//Software distributed under the License is distributed on an "AS IS" basis,
//WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
//specific language governing rights and limitations under the License.
//
//The Original Code is MultiDBViewer(http://code.google.com/p/multidbviewer/).
//The Initial Developer of the Original Code is Yiun Seungryong(http://yiunsr.tistory.com/) .
// Portions created by  Initial Developer are Copyright (C) 2011 the Initial Developer.
//All Rights Reserved.
//Contributor(s): Yiun Seungryong(http://yiunsr.tistory.com/)
/******************************************************************************
** 단순한 2차원 배열
** row, col size fiexed
*/
#ifndef __ARRARY2D_H__
#define __ARRARY2D_H__

// NULL 정의가 되어 있는 곳 stddef : gcc ,  stdlib :  visual c++
#include <cstddef>
#include <cstdlib>
#include <assert.h>


using namespace std;

template <typename DataType>
class Array2D{
	public:
		Array2D(int a_nRow, int a_nCol);
		~Array2D();

	public:
		int GetRowSize(){	return m_nRow;	}
		int GetColSize(){	return m_nCol;	}

	public:
		void SetData(int a_nRow, int a_nCol, DataType data );
		DataType GetData(int a_nRow, int a_nCol);

	public:
		void ClearData(int a_nRow, int a_nCol);
		void ClearAll();
		typedef DataType *	DataPtr_t;


	private:
		int m_nRow;
		int m_nCol;
		DataType** m_ppData;


};

template <typename DataType>
Array2D<DataType>::Array2D(int a_nRow, int a_nCol)
{
	m_nRow = a_nRow;
	m_nCol = a_nCol;
	int nTotal = a_nRow*a_nCol;
	m_ppData = new DataPtr_t[nTotal];
	int i = 0;
	for(i = 0; i < nTotal; i++)
		m_ppData[i] = NULL;
}

template <typename DataType>
Array2D<DataType>::~Array2D()
{
	int nTotal = m_nRow * m_nCol;
	int i = 0;
	for(i = 0; i < nTotal; i++)
		delete m_ppData[i];
	delete[]	m_ppData;
}


template <typename DataType>
void Array2D<DataType>::SetData(int a_nRow, int a_nCol, DataType data )
{
	assert(m_nRow > a_nRow);
	assert(m_nCol > a_nCol);
	int nIndex = a_nRow * m_nCol + a_nCol;
	delete m_ppData[nIndex];
	m_ppData[nIndex] = new DataType(data);
}

template <typename DataType>
DataType Array2D<DataType>::GetData(int a_nRow, int a_nCol )
{
	assert(m_nRow > a_nRow);
	assert(m_nCol > a_nCol);
	return *m_ppData[a_nRow*m_nCol + a_nCol];
}


template <typename DataType>
void Array2D<DataType>::ClearData(int a_nRow, int a_nCol )
{
	ClearAll();
	assert(m_nRow > a_nRow);
	assert(m_nCol > a_nCol);
	int nIndex = a_nRow * m_nCol + a_nCol;
	delete m_ppData[nIndex];
}

template <typename DataType>
void Array2D<DataType>::ClearAll()
{
	int i = 0, nTotal = m_nRow * m_nCol;
	for(i = 0; i < nTotal; i++)
		delete m_ppData[i];
	delete	m_ppData;


}





#endif // __ARRARY2D_H__
