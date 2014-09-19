#include "SQLReaderBase.h"
#include "SQLData.h"
#include <stdio.h>

#define BUFFER_SIZE 200

SQLReaderBase::SQLReaderBase()
{

}

SQLReaderBase::~SQLReaderBase()
{
	Finalize();
}

void SQLReaderBase::Finalize()
{

}


void SQLReaderBase::SQLTrace(void* a_pUserData,const char* a_szTrace)
{
	SQLReaderBase* pThis = (SQLReaderBase *)a_pUserData;
	if(!pThis)
		return;

	pThis->Trace(emTraceSQLQuery, a_szTrace);

}

void SQLReaderBase::Trace(TraceType_t a_eTraceType, const char* a_pszeMessage)
{
	MidInter* pMid = MidInter::GetInstance();
	if(pMid)
		pMid->Trace(a_eTraceType, a_pszeMessage);
}

void SQLReaderBase::Trace(TraceType_t a_eTraceType, string a_strMessage)
{
	MidInter* pMid = MidInter::GetInstance();
	if(pMid)
		pMid->Trace(a_eTraceType, a_strMessage.c_str());
}


/////////////////////////////////////////////
//
//ST_DBReaderErr  SQLReaderBase::FileOpen(const char* a_pFileName)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//
//}
//
//
//ST_DBReaderErr  SQLReaderBase::FileNew(const char* a_pFileName)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//ST_DBReaderErr  SQLReaderBase::FileSave()
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//ST_DBReaderErr  SQLReaderBase::Close()
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//
//ST_DBReaderErr SQLReaderBase::ExecQuery(const char* a_szQuery,  bool a_bDirty)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//ST_DBReaderErr  SQLReaderBase::GetMainTable()
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//
//}
//
//
//vector<string> SQLReaderBase::GetColName()
//{
//
//	vector<string> vecCols;
//	return vecCols;
//
//}
//
//
//
//
//vector<ST_TableInfo>  SQLReaderBase::GetTableInfo(bool a_bReload)
//{
//	vector<ST_TableInfo> vecCols;
//	return vecCols;
//
//}
//
//
//vector<ST_ColInfo> SQLReaderBase::GetTableInfo(int a_nTableIndex, bool a_bReload)
//{
//	vector<ST_ColInfo> vecCols;
//	return vecCols;
//}
//
//
//
//ST_DBReaderErr SQLReaderBase::GetTable(const char* a_szSql, char*** a_pszResult, int* a_pnRow, int* a_pnColum )
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//
//
//void SQLReaderBase::GetAllRow(int a_nTableIndex, DBCallback_t a_pFunCallback  , void *a_pUserData)
//{
//
//}
//
//
//void SQLReaderBase::GetAllRow(int a_nTableIndex, ITableData* a_pITableData)
//{
//
//}
//
//
//bool SQLReaderBase::GetTableWithQuery(string a_strQuery, ITableData* a_pITableData)
//{
//	return true;
//}
//
//
//ST_DBReaderErr SQLReaderBase::AddRow(int a_nTableIndex)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//ST_DBReaderErr SQLReaderBase::AddRow(int a_nTableIndex, Array2D<string> *a_pStringValue2D)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//ST_DBReaderErr SQLReaderBase::DeleteRow(int a_nTableIndex, const char *a_szRowID)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//ST_DBReaderErr SQLReaderBase::DeleteRow(int a_nTableIndex, vector<string> a_vecIDList)
//{
//
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//
//
//ST_DBReaderErr SQLReaderBase::GetLastInsertRow(int a_nTableIndex, ITableData* a_pITableData)
//{
//
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//
//eDBReaderErr_t SQLReaderBase:: ModifyRow(int a_nTableIndex, const char *a_szRowID, int a_nCol, const char *a_szData)
//{
//
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//eDBReaderErr_t SQLReaderBase::ModifyCol(int a_nTableIndex, int a_nCol, const char *a_szName, const char *a_szType)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//
//eDBReaderErr_t SQLReaderBase::AddCol(int a_nTableIndex,  const char *a_szName, const char *a_szType)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//eDBReaderErr_t SQLReaderBase::DeleteCol(int a_nTableIndex, int a_nCol)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//
//eDBReaderErr_t SQLReaderBase::AddTable(ST_TableInfo* a_pTableInfo)
//{
//
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//eDBReaderErr_t SQLReaderBase::DeleteTable(int a_nTableNum)
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//eDBReaderErr_t SQLReaderBase::Undo()
//{
//	return ST_DBReaderErr(eDBReaderNotSupport);
//}
//
//int SQLReaderBase::SQLCommitHook(void *a_pUser)
//{
//	return 0;
//}
//
//bool SQLReaderBase::SetDirty()
//{
//	return false;
//}
//
//string SQLReaderBase::GetColNameString(unsigned int a_eColInfoType, unsigned int a_nTableIndex,
//			unsigned int a_nChangeCol, const char* a_pszName, const char* a_pszzType, bool a_bPrimary)
//{
//
//	return NULL;
//}

