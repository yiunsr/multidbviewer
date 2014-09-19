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
** row size appendable
*/
#ifndef __VECARRARY2D_H__
#define __VECARRARY2D_H__

// NULL 정의가 되어 있는 곳 stddef : gcc ,  stdlib :  visual c++
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <assert.h>

#include "VecArray1D.h"

using namespace std;

template <class DataType>
class VecArray2D{
	public:
		VecArray2D();
		~VecArray2D();

	public:
		void SetSize(unsigned int a_nRow, unsigned int a_nCol);
		void SetCol(unsigned int a_nCol);
		unsigned int GetRowSize(){	return m_nRow;	}
		unsigned int GetColSize(){	return m_nCol;	}

	public:
		void SetData(unsigned int a_nRow, unsigned int a_nCol, DataType data );
		DataType GetData(unsigned int a_nRow, unsigned int a_nCol);

	public:
		void AppendRows(unsigned int a_nRow = 1);
		void AppendRows(VecArray2D<DataType>* a_pVecArray2D);
		void RemoveRows(unsigned int a_nRow, unsigned int a_nNumRow = 1);

		void InsertCols(unsigned int a_nCol, unsigned int a_nNumCol = 1);
		void InsertCols(unsigned int a_nCol,DataType data, unsigned int a_nNumCol = 1);
		void AppendCols(unsigned int a_nCol, unsigned int a_nNumCol = 1);
		void AppendCols(unsigned int a_nCol,DataType data, unsigned int a_nNumCol = 1);
		void RemoveCols(unsigned int a_nCol, unsigned int a_nNumCol = 1);
		void ClearData(unsigned int a_nRow, unsigned int a_nCol);
		void ClearAll();
		typedef DataType *	DataPtr_t;


	private:
		unsigned int m_nRow;
		unsigned int m_nCol;

		vector<  VecArray1D<DataType>* > m_pRowVec;
};

template <typename DataType>
VecArray2D<DataType>::VecArray2D()
{
	m_nRow = m_nCol = 0;;
}

template <typename DataType>
VecArray2D<DataType>::~VecArray2D()
{
	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nRow; nIndex++)
		delete (m_pRowVec[nIndex]);
}


template <typename DataType>
void VecArray2D<DataType>::SetSize(unsigned int a_nRow, unsigned int a_nCol)
{
	unsigned int nIndex = 0;

	//// Row
	unsigned int nOldRow = m_nRow;
	m_nRow = a_nRow;

	if(m_nRow == nOldRow)
		;	// do noting;
	else if(m_nRow < nOldRow)	// 더 작아졌으면 resize 전 삭제
	{
		for(nIndex = nOldRow; nIndex < m_nRow; nIndex++)
			delete m_pRowVec[nIndex];
		m_pRowVec.resize(a_nRow);
	}
	else	// 더 커졌으면 할당함
	{
		m_pRowVec.resize(a_nRow);
		for(nIndex = nOldRow; nIndex < m_nRow; nIndex++)
		{
			m_pRowVec[nIndex] = new VecArray1D<DataType>;
			m_pRowVec[nIndex]->SetSize(a_nCol);
		}
	}

	SetCol(a_nCol);

}

template <typename DataType>
void VecArray2D<DataType>:: SetCol(unsigned int a_nCol)
{
	unsigned int nOldCol = m_nCol;
	m_nCol = a_nCol;

	if(m_nCol == nOldCol)
		;	// do noting;
	else
	{
		unsigned int nIndex = 0;
		for(nIndex = 0; nIndex < m_nRow; nIndex++)
			m_pRowVec.resize(a_nCol);
	}
}

template <typename DataType>
void VecArray2D<DataType>::SetData(unsigned int a_nRow, unsigned int a_nCol, DataType data )
{
	assert(m_nRow >= a_nRow);
	assert(m_nCol >= a_nCol);

	m_pRowVec[a_nRow]->SetData(a_nCol, data);
}

template <typename DataType>
DataType VecArray2D<DataType>::GetData(unsigned int a_nRow, unsigned int a_nCol )
{
	assert(m_nRow >= a_nRow);
	assert(m_nCol >= a_nCol);
	return m_pRowVec[a_nRow]->GetData(a_nCol);
}

template <typename DataType>
void VecArray2D<DataType>::AppendRows(unsigned int a_nRow)
{
	unsigned int nOldRow = m_nRow;
	m_nRow+= a_nRow;
	m_pRowVec.resize(m_nRow);
	unsigned int nIndex = 0;
	for(nIndex = nOldRow; nIndex < m_nRow; nIndex++)
	{
		m_pRowVec[nIndex] = new VecArray1D<DataType>;
		m_pRowVec[nIndex]->SetSize(m_nCol);
	}
}

template <typename DataType>
void VecArray2D<DataType>::AppendRows(VecArray2D<DataType>* a_pVecArray2D)
{
	unsigned int nOldRow = m_nRow;
	unsigned int lhsRowSize = a_pVecArray2D->GetRowSize();
	m_nRow += lhsRowSize;
	m_pRowVec.resize(m_nRow);

	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex + nOldRow < m_nRow; nIndex++)
		m_pRowVec[nIndex + nOldRow] = new VecArray1D<DataType> (*a_pVecArray2D->m_pRowVec[nIndex]);
}

template <typename DataType>
void VecArray2D<DataType>::RemoveRows(unsigned int a_nRow, unsigned int a_nNumRow)
{
	assert(m_nRow >= a_nRow + a_nNumRow);

	unsigned int nEndRow = a_nRow + a_nNumRow; // STL 특성상 하나 지나치게 가르켜야 한다.

	unsigned int nIndex = 0;
	for(nIndex = a_nRow; nIndex < nEndRow; nIndex++)
		delete m_pRowVec[nIndex];
	m_pRowVec.erase(m_pRowVec.begin() + a_nRow , m_pRowVec.begin() + nEndRow);
	m_nRow -= a_nNumRow;

}

template <typename DataType>
void VecArray2D<DataType>::InsertCols(unsigned int a_nCol, unsigned int a_nNumCol)
{
	assert(m_nCol >= a_nCol);
	m_nCol -= a_nNumCol;

	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nRow; nIndex++)
		m_pRowVec[nIndex]->Insert(a_nCol);
}


template <typename DataType>
void VecArray2D<DataType>::InsertCols(unsigned int a_nCol,DataType data, unsigned int a_nNumCol)
{
	assert(m_nCol >= a_nCol);
	m_nCol -= a_nNumCol;

	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nRow; nIndex++)
		m_pRowVec[nIndex]->Insert(a_nCol, data );
}

template <typename DataType>
void VecArray2D<DataType>::AppendCols(unsigned int a_nCol, unsigned int a_nNumCol)
{
	assert(m_nCol >= a_nCol);
	m_nCol -= a_nNumCol;

	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nRow; nIndex++)
		m_pRowVec[nIndex]->Append(a_nCol );
}

template <typename DataType>
void VecArray2D<DataType>::AppendCols(unsigned int a_nCol,DataType data, unsigned int a_nNumCol)
{
	assert(m_nCol >= a_nCol);
	m_nCol -= a_nNumCol;

	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nRow; nIndex++)
		m_pRowVec[nIndex]->Append(a_nCol, data );
}

template <typename DataType>
void VecArray2D<DataType>::RemoveCols(unsigned int a_nCol, unsigned int a_nNumCol)
{
	assert(m_nCol >= a_nCol + a_nNumCol);

	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nRow; nIndex++)
		m_pRowVec[nIndex]->Remove(a_nCol);
	m_nCol -= a_nNumCol;

}

template <typename DataType>
void VecArray2D<DataType>::ClearData(unsigned int a_nRow, unsigned int a_nCol )
{
	assert(m_nRow >= a_nRow);
	assert(m_nCol >= a_nCol);
	m_pRowVec[a_nRow]->ClearData(a_nCol);
}

template <typename DataType>
void VecArray2D<DataType>::ClearAll()
{
	unsigned int  nIndex = 0;
	for(nIndex = 0; nIndex < m_nRow; nIndex++)
		delete m_pRowVec[nIndex];
	m_pRowVec.clear();

	m_nRow = 0;
	m_nCol = 0;
}





#endif // __VECARRARY2D_H__
