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
** SQL 을 읽을 수 있는 파일
*/



#ifndef __SQLITE_READER_H__
#define __SQLITE_READER_H__

#include <iostream>
#include <vector>
#include "sqlite/sqlite3.h"
#include "ml/MidInter.h"
#include "datastruct/Array2D.h"
#include "SQLData.h"
#include "SQLReaderBase.h"


using namespace std;


struct ST_TableInfo;

class SqliteReader : public SQLReaderBase{

public:
	SqliteReader();
	virtual ~SqliteReader();
	void Finalize();

public:
	typedef int (*DBCallback_t)(void *, int, char **, char **);


public:
	ST_DBReaderErr FileOpen(const char* a_pFileName);
	ST_DBReaderErr FileNew(const char* a_pFileName);
	ST_DBReaderErr FileSave();
	ST_DBReaderErr Connect(const char *,const char *,const char *, const char *,const char *,const char *)
	{
		return ST_DBReaderErr(eDBReaderNotSupport);
	}
	ST_DBReaderErr Close();
	ST_DBReaderErr GetMainTable();

	vector<string> GetTableNames(){		return m_vecTableName;		}
	vector<string> GetColName();

	vector<ST_TableInfo> GetTableInfo(bool a_bReload);
	vector<ST_ColInfo> GetTableInfo(int a_nTableIndex, bool a_bReload);
	//void GetRows(int a_nTableIndex, int a_nStart, int a_nEnd , DBCallback_t a_pFunCallback  , void* a_pUserData);
	void GetAllRow(int a_nTableIndex, DBCallback_t a_pFunCallback  , void* a_pUserData);
	void GetAllRow(int nTableIndex, ITableData* a_pITableData);
	bool GetTableWithQuery(string a_strQuery,  ITableData* a_pITableData);

	ST_DBReaderErr ExecQuery(const char* a_szQuery, bool a_bDirty = true );
	ST_DBReaderErr ExecQuery(string a_strQuery, bool a_bDirty = true)
	{
		return ExecQuery(a_strQuery.c_str(), a_bDirty);
	}

	static void SQLTrace(void* a_pUserData,const char* a_szTrace);

	ST_DBReaderErr AddRow(int a_nTableIndex);
	ST_DBReaderErr AddRow(int a_nTableIndex, Array2D<string> *a_pStringValue2D);

	ST_DBReaderErr DeleteRow(int a_nTableIndex, const char *a_szRowID);
	ST_DBReaderErr DeleteRow(int a_nTableIndex, vector<string> a_vecIDList);
	ST_DBReaderErr GetLastInsertRow(int a_nTableIndex, ITableData* a_pITableData);
	ST_DBReaderErr ModifyRow(int a_nTableIndex, const char *a_szRowID, int a_nCol, const char *a_szData);

	ST_DBReaderErr ModifyCol(int a_nTableIndex, int a_nCol, const char *a_szName, const char *a_szType);
	ST_DBReaderErr ModifyCol(int a_nTableIndex, ST_TableInfo* a_pTableInfo);

	ST_DBReaderErr AddCol(int a_nTableIndex, const char *a_szName, const char *a_szType);
	ST_DBReaderErr DeleteCol(int a_nTableIndex, int a_nCol);

	ST_DBReaderErr AddTable(ST_TableInfo* a_pTableInfo);
	ST_DBReaderErr DeleteTable(int a_nTableNum);

	ST_DBReaderErr Undo();


protected:
	ST_DBReaderErr GetTable(const char* a_szSql, char*** a_pszResult, int* a_pnRow, int* a_pnColum );
	//static int SQLCallback(void *pUser, int argc, char **argv, char **azColName);
	static int SQLCommitHook(void *a_pUser);
	bool SetDirty();

	string GetColNameString(unsigned int a_eColInfoType, unsigned int a_nTableIndex,
		unsigned int a_nChangeCol = 0, const char* a_pszName = NULL, const char* a_pszzType = NULL, bool a_bPrimary = false);

	string GetValueListString(unsigned int a_nTableIndex, Array2D<string> *a_pStringValue2D, int a_nRow);

	void Trace(TraceType_t a_eTraceType, const char* a_pszeMessage);
	void Trace(TraceType_t a_eTraceType, string a_strMessage);

private:
	ST_DBReaderErr ErrTrans(int rc);
	bool CheckTableIndex(int a_nIndex);

private:
	sqlite3 *m_DB;

	unsigned int m_nTotalTable;
	unsigned int m_nCurrentTable;
	vector<ST_TableInfo> m_vecTableInfo;
	vector<string> m_vecTableName;
	Array2D<string>* m_pStringArray2D;

	int	m_nDirty;


};

#endif // __SQLITE_READER_H__
