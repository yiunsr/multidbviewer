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
#ifndef __SQLData__
#define __SQLData__

#include <string>
#include <vector>
using namespace std;


enum eDataType_t
{
	eDTUnknow = 0,
	eDTInt,
	eDDouble,
	eDString,

};

struct ST_ColInfo
{
	string strColName;
	string strColDataType;
	string strDefault;
	bool bPrimaryKey;
	bool bNotNull;
	//eDataType_t nColDataType;

	ST_ColInfo();

};



struct ST_TableInfo
{
	string strTableName;
	unsigned int nTotalCol;
	vector<ST_ColInfo> arrColInfo;

	ST_TableInfo();
	void Clear();
};




class TABLEDBInfo
{
public:
	TABLEDBInfo();

public:
	unsigned int		GetPagePerRow()		{	return m_nPagePerRow;	}
	unsigned int		GetTotal()			{	return m_nTotal;		}
	unsigned int		GetCurrentStart()	{	return m_nCurrentStart;	}
	unsigned int		GetCurrentEnd()		{	return m_nCurrentEnd;	}
	unsigned int		GetCurrentPage()	{	return m_nCurrentPage;	}
	unsigned int		GetTotalPage()		{	return m_nTotalPage;	}

	void	SetCurrentPage(unsigned int a_nPage);
	void	SetTotal(unsigned int a_nTotal);
	int		PageMove(int a_nPageDistance);
	bool	RemoveRow(unsigned int a_nRemoveCount = 1);
	bool	AddRow(unsigned int a_nAddCount = 1);

private:
	void	CalCurrentRow();
	

private:
	unsigned int		m_nPagePerRow;
	unsigned int		m_nTotal;
	unsigned int		m_nCurrentStart;
	unsigned int		m_nCurrentEnd;
	unsigned int		m_nCurrentPage;
	unsigned int		m_nTotalPage;
};



// Interface 만 존재하는 Calss 임. 
// 
class ITableData
{
protected:
	ITableData()	{  }	// Interface Class  이므로 Constructor를 protected 로 둔다. 
	virtual ~ITableData()	{	}

public:

	virtual void SetColNum(int )	{	}
	virtual void AddRow()	{	}

	// start with 0
	// org void SetData(int  a_nRow, int a_nCol, const char *a_szData) 
	// avoid warning no use parameter
	virtual void SetData(int  , int , const char * )	{	}

	// void SetRowID(int a_nRow, const char *a_szData)
	virtual void SetRowID(int , const char * )	{	}

	// void SetColName(int a_nCol, const char *a_szData)	{	}
	virtual void SetColName(int , const char * )	{	}

	

};

template<typename ArrType_t>
class SelectRange
{
public:
	enum SlectMode_t{
		eNone,
		eAll,
		eRow,
		eCol,
		eCell,
	};

public:
	SelectRange(){ m_eSelectMode = eNone ; }
	virtual ~SelectRange() {	}

public:
	SlectMode_t GetSelectMode(){	return m_eSelectMode;	}
	void SetSelectMode(SlectMode_t a_eSelectMode){	m_eSelectMode = a_eSelectMode; 	}

	
	ArrType_t GetSelect(){	return m_ArrSelect;	}
	void SetSelect(ArrType_t a_ArrSelect){	m_ArrSelect = a_ArrSelect;	}


private:
	SlectMode_t m_eSelectMode;
	ArrType_t m_ArrSelect;

};



#endif // __SQLData__
