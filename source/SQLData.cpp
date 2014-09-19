#include "SQLData.h"

#include "Config.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


ST_ColInfo::ST_ColInfo()
{
	strColName.clear();
	strColDataType.clear();
	strDefault.clear();
	bPrimaryKey = false;
	bNotNull = false;
}

ST_TableInfo::ST_TableInfo()
{
	nTotalCol = 0;
}

void ST_TableInfo::Clear()
{
	strTableName.clear();
	nTotalCol = 0;
	arrColInfo.clear();
}

TABLEDBInfo::TABLEDBInfo()
{
	m_nPagePerRow = 100;
	Config *pConfig = Config::GetInstance();
	if(pConfig)
		m_nPagePerRow = pConfig->GetRecordPerTable();

	m_nTotal = 0;
	m_nCurrentStart = 0;
	m_nCurrentEnd = 0;
	m_nCurrentPage = 0;
	m_nTotalPage = 0;
}

void TABLEDBInfo::SetCurrentPage(unsigned int a_nPage)
{
	m_nCurrentPage = MAX(a_nPage, 1);
	CalCurrentRow();
}


void TABLEDBInfo::SetTotal(unsigned int a_nTotal)
{
	m_nTotal = a_nTotal;
	m_nTotalPage = m_nTotal/m_nPagePerRow +  (m_nTotal%m_nPagePerRow ==0 ? 0:1);
}


int TABLEDBInfo::PageMove(int a_nPageDistance)
{
	int nNewpage = m_nCurrentPage + a_nPageDistance;
	nNewpage = MIN(nNewpage, m_nTotalPage);
	nNewpage = MAX(nNewpage, 1);
	SetCurrentPage(nNewpage);
	return m_nCurrentPage;
}


void	TABLEDBInfo::CalCurrentRow()
{
	m_nCurrentStart = (m_nCurrentPage-1)*m_nPagePerRow + 1;
	m_nCurrentEnd = MIN(m_nCurrentPage*m_nPagePerRow, m_nTotal) ;
}

bool	TABLEDBInfo::RemoveRow(unsigned int a_nRemoveCount)
{
	if(m_nTotal - a_nRemoveCount <0)
		return false;
	m_nTotal -= a_nRemoveCount;
	return true;
}

bool	TABLEDBInfo::AddRow(unsigned int a_nAddCount)
{
	m_nTotal += a_nAddCount;
	return true;
}


