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
*/
#ifndef __VECARRARY1D_H__
#define __VECARRARY1D_H__

// NULL 정의가 되어 있는 곳 stddef : gcc ,  stdlib :  visual c++
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <assert.h>


using namespace std;

template <class DataType>
class VecArray1D{
	public:
		VecArray1D();
		VecArray1D(VecArray1D<DataType>&a_rVecArray1D);
		~VecArray1D();

	public:
		void SetSize(unsigned int a_nSize);
		unsigned int GetSize(){	return m_nSize;	}
	public:
		void SetData(unsigned int a_nIndex, DataType data);
		DataType GetData(unsigned int a_nIndex);
		void Append(unsigned int a_nCount = 1);
		void Append(DataType data, unsigned int a_nCount = 1);
		void Insert(unsigned int a_nIndex, unsigned int a_nCount = 1);
		void Insert(unsigned int a_nIndex, DataType data, unsigned int a_nCount = 1);


	public:
		void Remove(unsigned int a_nIndex, unsigned int a_nCount = 1);
		void ClearData(unsigned int a_nInex);
		void ClearAll();
		typedef DataType *	DataPtr_t;


	private:
		unsigned int m_nSize;
		vector<DataPtr_t> m_VecData;
};

template <typename DataType>
VecArray1D<DataType>::VecArray1D()
{
	m_nSize = 0;
}

template <typename DataType>
VecArray1D<DataType>::VecArray1D(VecArray1D<DataType>& a_rVecArray1D)
{
	m_nSize = a_rVecArray1D.m_nSize;
	m_VecData.resize(m_nSize);

	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nSize; nIndex++)
		m_VecData[nIndex] = new DataType(*a_rVecArray1D.m_VecData[nIndex] );
}

template <typename DataType>
VecArray1D<DataType>::~VecArray1D()
{
	unsigned int nIndex = 0;
	for(nIndex = 0; nIndex < m_nSize; nIndex++)
		delete m_VecData[nIndex];
}


template <typename DataType>
void VecArray1D<DataType>::SetSize(unsigned int a_nSize)
{
	unsigned int nOldSize = m_nSize;
	m_nSize = a_nSize;
	if(nOldSize == a_nSize )
		return;	// do noting
	else if(m_nSize < a_nSize )	// Size가 줄어두는 경우
	{
		unsigned int nIndex = 0;
		for(nIndex = a_nSize; nIndex < nOldSize; nIndex++)
		{
			delete m_VecData[nIndex];
			m_VecData[nIndex] = NULL;
		}
		m_VecData.resize(m_nSize);
		return;
	}

	// Size 가 늘어나는 경우, 늘어나는 부분을  0으로 추기화
	m_VecData.resize(m_nSize);
	unsigned int nIndex = 0;
	for(nIndex = nOldSize; nIndex < m_nSize; nIndex++)
		m_VecData[nIndex] = NULL;
	return;

}


template <typename DataType>
void VecArray1D<DataType>::SetData(unsigned int a_nIndex, DataType data)
{
	assert(m_nSize >= a_nIndex);
	delete m_VecData[a_nIndex];
	m_VecData[a_nIndex] = new DataType(data);
}

template <typename DataType>
DataType VecArray1D<DataType>::GetData(unsigned int a_nIndex )
{
	assert(m_nSize >= a_nIndex);
	return *m_VecData[a_nIndex];
}

template <typename DataType>
void VecArray1D<DataType>::Append(unsigned int a_nCount)
{
	unsigned int nOldSize = m_nSize;
	m_nSize+= a_nCount;
	m_VecData.resize(m_nSize);
	unsigned int nIndex = 0;
	for( nIndex = nOldSize ; nIndex < m_nSize ; nIndex++)
		m_VecData[nIndex] = NULL;
}

template <typename DataType>
void VecArray1D<DataType>::Append(DataType data, unsigned int a_nCount)
{

	unsigned int nOldSize = m_nSize;
	m_nSize+= a_nCount;
	m_VecData.resize(m_nSize);
	unsigned int nIndex = 0;
	for( nIndex = nOldSize ; nIndex < m_nSize ; nIndex++)
		m_VecData[nIndex] = new DataType(data);
}

template <typename DataType>
void VecArray1D<DataType>::Insert(unsigned int a_nIndex, unsigned int a_nCount )
{
	m_nSize+= a_nCount;
	m_VecData.insert(m_VecData.begin() + a_nIndex, a_nCount, NULL);
}

template <typename DataType>
void VecArray1D<DataType>::Insert(unsigned int a_nIndex, DataType data, unsigned int a_nCount)
{
	unsigned int nOldSize = m_nSize;
	m_nSize+= a_nCount;
	m_VecData.insert(m_VecData.begin() + a_nIndex, a_nCount, NULL);
	unsigned int nIndex = 0;
	for( nIndex = nOldSize ; nIndex < m_nSize ; nIndex++)
		m_VecData[nIndex] = new DataType(data);
}

template <typename DataType>
void VecArray1D<DataType>::Remove(unsigned int a_nIndex, unsigned int a_nCount)
{
	if(a_nIndex + a_nCount > m_nSize)
	{
		assert(0);
		return;
	}
	m_nSize-= a_nCount;
	unsigned int nEndIndex = a_nIndex + a_nCount; // STL 특성상 하나 지나치게 가르켜야 한다.
	unsigned int nIndex = 0;
	for( nIndex = a_nIndex ; nIndex < nEndIndex ; nIndex++)
	{
		delete m_VecData[nIndex];
		m_VecData[nIndex] = NULL;
	}

	m_VecData.erase(m_VecData.begin() + a_nIndex , m_VecData.begin() + nEndIndex);

}

template <typename DataType>
void VecArray1D<DataType>::ClearData(unsigned int a_nInex)
{
	assert(m_nSize >= a_nInex);
	delete m_VecData[a_nInex];
	m_VecData[a_nInex] = NULL;
}



template <typename DataType>
void VecArray1D<DataType>::ClearAll()
{
	unsigned int  nIndex = 0;
	for(nIndex = 0; nIndex < m_nSize; nIndex++)
	{
		delete m_VecData[nIndex];
		m_VecData[nIndex] = NULL;
	}

	m_nSize = 0;
}





#endif // __VECARRARY1D_H__
