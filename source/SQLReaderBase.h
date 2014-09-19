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



#ifndef __SQLReaderBase_H__
#define __SQLReaderBase_H__

#include <iostream>
#include <vector>
#include "sqlite/sqlite3.h"
#include "ml/MidInter.h"
#include "datastruct/Array2D.h"
#include "SQLData.h"


using namespace std;


struct ST_TableInfo;


enum eDBReaderErr_t{
	eDBReaderSuccess = 0,
	eDBReaderNotSupport,
	eDBReaderUnknownFail,
	eDBReaderDBNotPrepare,
	eDBReaderInvalidTableIndex,  // if table size is zero, always raise eDBReaderInvalidTableIndex 
	eDBReaderInternalError,
	eDBReadereNotNullError,
};

struct ST_DBReaderErr{
	eDBReaderErr_t eDBReaderErr;
	int errDetail;
	string strErrMsg;

	ST_DBReaderErr(eDBReaderErr_t  a_eDBReaderErr = eDBReaderSuccess, int a_errDetail = 0){
		eDBReaderErr = a_eDBReaderErr;
		errDetail = a_errDetail;
	}
	bool IsSucuccess(){  return eDBReaderErr == eDBReaderSuccess; }
	bool IsFail(){  return eDBReaderErr != eDBReaderSuccess; }

	eDBReaderErr_t GetErr(){ return eDBReaderErr; }
	int GetErrDetail(){ return errDetail; }
	string GetErrMsg(){ return strErrMsg; }
};



#define ReturnSuccess(Return)  ( Return == eDBReaderSuccess)


class SQLReaderBase{

public:
	SQLReaderBase();
	virtual ~SQLReaderBase() = 0;
	void Finalize();

public:
	enum eColInfoType_t{
	eColInfoTypeNone = 0,
	eColInfoTypeName = 1,
	eColInfoTypeType = 2,
	eColInfoTypePrimary = 4,
};

public:
	typedef int (*DBCallback_t)(void *, int, char **, char **);


public:
	virtual ST_DBReaderErr FileOpen(const char* a_pFileName) = 0;
	virtual ST_DBReaderErr FileNew(const char* a_pFileName) = 0;
	virtual ST_DBReaderErr FileSave() = 0;
	virtual ST_DBReaderErr Connect(const char* a_pURL, const char* a_pPort,const char* a_pDBName, const char* a_pID, const char* a_pPassword, const char* a_pUserString) = 0;
	virtual ST_DBReaderErr Close() = 0;
	virtual ST_DBReaderErr GetMainTable() = 0;

	virtual vector<string> GetTableNames() = 0;
	virtual vector<string> GetColName() = 0;

	virtual vector<ST_TableInfo> GetTableInfo(bool a_bReload) = 0;
	virtual vector<ST_ColInfo> GetTableInfo(int a_nTableIndex, bool a_bReload) =0 ;
	//void GetRows(int a_nTableIndex, int a_nStart, int a_nEnd , DBCallback_t a_pFunCallback  , void* a_pUserData);
	virtual void GetAllRow(int a_nTableIndex, DBCallback_t a_pFunCallback  , void* a_pUserData) =0;
	virtual void GetAllRow(int nTableIndex, ITableData* a_pITableData) = 0;
	virtual bool GetTableWithQuery(string a_strQuery,  ITableData* a_pITableData) = 0;

	virtual ST_DBReaderErr ExecQuery(const char* a_szQuery, bool a_bDirty = true ) = 0;
	virtual ST_DBReaderErr ExecQuery(string a_strQuery, bool a_bDirty = true) = 0;

	static void SQLTrace(void* a_pUserData,const char* a_szTrace);

	virtual ST_DBReaderErr AddRow(int a_nTableIndex) = 0;
	virtual ST_DBReaderErr AddRow(int a_nTableIndex, Array2D<string> * a_pStringValue2D) = 0;
	virtual ST_DBReaderErr DeleteRow(int a_nTableIndex, const char *a_szRowID) = 0;
	virtual ST_DBReaderErr DeleteRow(int a_nTableIndex, vector<string> a_vecIDList) = 0;
	virtual ST_DBReaderErr GetLastInsertRow(int a_nTableIndex, ITableData* a_pITableData) = 0;
	virtual ST_DBReaderErr ModifyRow(int a_nTableIndex, const char *a_szRowID, int a_nCol, const char *a_szData) = 0;

	virtual ST_DBReaderErr ModifyCol(int a_nTableIndex, int a_nCol, const char *a_szName, const char *a_szType) = 0;
	virtual ST_DBReaderErr ModifyCol(int a_nTableIndex, ST_TableInfo* a_pTableInfo) = 0;
	virtual ST_DBReaderErr AddCol(int a_nTableIndex, const char *a_szName, const char *a_szType) = 0;
	virtual ST_DBReaderErr DeleteCol(int a_nTableIndex, int a_nCol) = 0;

	virtual ST_DBReaderErr AddTable(ST_TableInfo* a_pTableInfo) = 0;
	virtual ST_DBReaderErr DeleteTable(int a_nTableNum) = 0;

	virtual ST_DBReaderErr Undo() = 0;


protected:
	virtual ST_DBReaderErr GetTable(const char* a_szSql, char*** a_pszResult, int* a_pnRow, int* a_pnColum ) = 0;
	//static int SQLCallback(void *pUser, int argc, char **argv, char **azColName);
	virtual bool SetDirty() = 0;

	virtual string GetColNameString(unsigned int a_eColInfoType, unsigned int a_nTableIndex, 
		unsigned int a_nChangeCol = 0, const char* a_pszName = NULL, const char* a_pszzType = NULL, bool a_bPrimary = false) = 0;

	void Trace(TraceType_t a_eTraceType, const char* a_pszeMessage);
	void Trace(TraceType_t a_eTraceType, string a_strMessage);



};

#endif // __SQLReaderBase_H__
