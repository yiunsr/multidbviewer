#include "SqliteReader.h"
#include "SQLData.h"
#include <stdio.h>

#define BUFFER_SIZE 200

SqliteReader::SqliteReader()
{
	m_DB = NULL;
	m_nTotalTable = 0;
	m_nCurrentTable = 0;
	m_pStringArray2D = NULL;
	m_nDirty = 0;
}

SqliteReader::~SqliteReader()
{
	Finalize();
}

void SqliteReader::Finalize()
{
	if(m_DB)
	{

		ExecQuery("ROLLBACK", false);
		sqlite3_close(m_DB);
		m_DB = NULL;
	}

}


ST_DBReaderErr  SqliteReader::FileOpen(const char* a_pFileName)
{

	//int rc = sqlite3_open("k_word.db", &m_DB);

	int rc = sqlite3_open(a_pFileName, &m_DB);
	if(rc != SQLITE_OK)
	{
		sqlite3_close(m_DB);
		m_DB = NULL;
		Trace(emTraceExcetion, "Could not open Mydb");
		return ErrTrans(rc);
	}

	ExecQuery("BEGIN", false);


	sqlite3_commit_hook(m_DB, SQLCommitHook,this);
	sqlite3_trace(m_DB, SqliteReader::SQLTrace, this);
	Trace(emTraceProgramProcess, "[SQLReader] File Open : pFileName");
	return ErrTrans(rc);

}


ST_DBReaderErr  SqliteReader::FileNew(const char* a_pFileName)
{

	//int rc = sqlite3_open("k_word.db", &m_DB);

	int rc = sqlite3_open(a_pFileName, &m_DB);
	if(rc != SQLITE_OK)
	{
		sqlite3_close(m_DB);
		m_DB = NULL;
		Trace(emTraceExcetion, "Could not open Mydb");
		return ErrTrans(rc);
	}

	ExecQuery("BEGIN", false);


	sqlite3_commit_hook(m_DB, SQLCommitHook,this);
	sqlite3_trace(m_DB, SqliteReader::SQLTrace, this);
	Trace(emTraceProgramProcess, "[SQLReader] File Open : pFileName");
	return ErrTrans(rc);

}

ST_DBReaderErr  SqliteReader::FileSave()
{
	m_nDirty = 0;
	return ExecQuery("COMMIT", false);

}

ST_DBReaderErr SqliteReader::Close()
{
	int rc = sqlite3_close(m_DB);
	return ErrTrans(rc);

}

ST_DBReaderErr SqliteReader::ExecQuery(const char* a_szQuery,  bool a_bDirty)
{
	int rc = SQLITE_OK;

	if(a_bDirty)
		SetDirty();

	Trace(emTraceProgramProcess, "[SQLReader] ExecQuery");
	//Trace(emTraceSQLQuery, a_szQuery);


	char	*szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, a_szQuery, NULL, this, &szErrMsg);
	return ErrTrans(rc);
}

void SqliteReader::SQLTrace(void* a_pUserData,const char* a_szTrace)
{
	SqliteReader* pThis = (SqliteReader *)a_pUserData;
	if(!pThis)
		return;

	pThis->Trace(emTraceSQLQuery, a_szTrace);

}

ST_DBReaderErr  SqliteReader::GetMainTable()
{
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	Trace(emTraceProgramProcess, "[SQLReader] Find Main Table");

	m_vecTableName.clear();

	int rc = SQLITE_OK;

	sqlite3_stmt* pStmt = NULL;
	rc = sqlite3_prepare(m_DB, "SELECT name, sql FROM sqlite_master WHERE type='table' ORDER BY name", -1, &pStmt, 0);
	if(rc != SQLITE_OK)
		return ErrTrans(rc);
	//Trace(emTraceSQLQuery, "SELECT name, sql FROM sqlite_master WHERE type='table' ORDER BY name");

	while(sqlite3_step(pStmt) == SQLITE_ROW)
	{
		const unsigned char* pszTableName = sqlite3_column_text(pStmt, 0);
		string strTemp( (char*)pszTableName);
		m_vecTableName.push_back(strTemp);

	}

	sqlite3_reset(pStmt);
	sqlite3_finalize(pStmt);


	return ErrTrans(rc);

}


vector<string> SqliteReader::GetColName()
{

	vector<string> vecCols;
	if(m_vecTableName.size() == 0  || !m_DB)
		return vecCols;


	Trace(emTraceProgramProcess, "[SQLReader] Read Cols Info");

	int rc = SQLITE_OK;

	sqlite3_stmt* pStmt = NULL;
	rc = sqlite3_prepare(m_DB, "SELECT name, sql FROM sqlite_master WHERE type='table' ORDER BY name", -1, &pStmt, 0);
	if(rc != SQLITE_OK)
		return vecCols;

	while(sqlite3_step(pStmt) == SQLITE_ROW)
	{
		const unsigned char* pszTableName = sqlite3_column_text(pStmt, 0);
		string strTemp( (char*)pszTableName);
		m_vecTableName.push_back(strTemp);

	}

	sqlite3_reset(pStmt);
	sqlite3_finalize(pStmt);
	return vecCols;

}




vector<ST_TableInfo>  SqliteReader::GetTableInfo(bool a_bReload)
{

	if(a_bReload)
		m_vecTableInfo.clear();
	unsigned int nIndex = 0;
	for( nIndex = 0 ; nIndex < m_vecTableName.size() ; nIndex ++)
	{
		ST_TableInfo stTableInfo;
		stTableInfo.strTableName = m_vecTableName[nIndex];
		stTableInfo.arrColInfo = GetTableInfo(nIndex, a_bReload);
		m_vecTableInfo.push_back(stTableInfo);
	}

	return m_vecTableInfo;

}


vector<ST_ColInfo> SqliteReader::GetTableInfo(int a_nTableIndex, bool a_bReload)
{
	vector<ST_ColInfo> vecCols;
	if(!CheckTableIndex(a_nTableIndex) || !m_DB)
		return vecCols;

	if(m_vecTableInfo.size()  < static_cast<unsigned int>(a_nTableIndex + 1) )
	{
		m_vecTableInfo.resize(m_vecTableName.size());
	}

	if(false == a_bReload)
		return m_vecTableInfo[a_nTableIndex].arrColInfo;

	m_vecTableInfo[a_nTableIndex].Clear();


	string strTraceMsg =   "[SQLReader] Get Table Info [";
	strTraceMsg += m_vecTableName[a_nTableIndex].c_str();
	strTraceMsg += "]";
	Trace(emTraceProgramProcess, strTraceMsg);

	int rc = SQLITE_OK;

	sqlite3_stmt* pStmt = NULL;
	string strQuery;
	strQuery = "PRAGMA TABLE_INFO(";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += ")";

	rc = sqlite3_prepare(m_DB, strQuery.c_str(), -1, &pStmt, 0);
	if(rc != SQLITE_OK)
		return vecCols;

	//Trace(emTraceSQLQuery, strQuery);


	while(sqlite3_step(pStmt) == SQLITE_ROW)
	{

		// 아래 숫자들 매크로가 필요할 듯..
		if( 6 > sqlite3_column_count(pStmt) )
			break;

		ST_ColInfo stColinfo;

		const unsigned char* pszColName = sqlite3_column_text(pStmt, 1);
		string strColName;
		if(pszColName)
			strColName.append((char*)pszColName);
		stColinfo.strColName = strColName;

		const unsigned char* pszDataType = sqlite3_column_text(pStmt, 2);
		string strDataType;
		if(pszDataType)
			strDataType.append((char*)pszDataType);
		stColinfo.strColDataType = strDataType;

		const unsigned char* pszNull = sqlite3_column_text(pStmt, 3);
		if( pszNull != NULL && pszNull[0] == '1')
			stColinfo.bNotNull = true;


		const unsigned char* pszDefault = sqlite3_column_text(pStmt, 4);
		string strDefault;
		if(pszDefault)
			strDefault.append((char*)pszDefault);
		stColinfo.strDefault = strDefault;

		const int nPrimary = sqlite3_column_int(pStmt, 5);
		if(nPrimary)
			stColinfo.bPrimaryKey = true;
		else
			stColinfo.bPrimaryKey = false;

		m_vecTableInfo[a_nTableIndex].arrColInfo.push_back(stColinfo);



	}

	sqlite3_reset(pStmt);
	sqlite3_finalize(pStmt);
	return m_vecTableInfo[a_nTableIndex].arrColInfo;

	//nTableIndex


}



ST_DBReaderErr SqliteReader::GetTable(const char* a_szSql, char*** a_pszResult, int* a_pnRow, int* a_pnColum )
{
	int rc = SQLITE_OK;
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	char *pszErrMsg;
	rc = sqlite3_get_table(m_DB, a_szSql, a_pszResult, a_pnRow, a_pnColum, &pszErrMsg);

	sqlite3_free_table(*a_pszResult);

	return ErrTrans(rc);
}



void SqliteReader::GetAllRow(int a_nTableIndex, DBCallback_t a_pFunCallback  , void *a_pUserData)
{

	int rc = SQLITE_OK;

	if(!CheckTableIndex(a_nTableIndex) || !m_DB)
		return;


	Trace(emTraceProgramProcess, "[SQLReader] Get Rows");


	// Query 문에 적합한 cols

	string strColsList;
	bool bFirstList = true;
	vector<ST_ColInfo>::iterator it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	for ( ; it !=m_vecTableInfo[a_nTableIndex].arrColInfo.end(); ++it)
	{
		if(!bFirstList)
			strColsList += ",";
		bFirstList = false;
		strColsList +=  it->strColName;
	}

	string strQuery;
	strQuery += "SELECT *  FROM ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += " ORDER BY rowid ";

	//Trace(emTraceSQLQuery, (const char*) strQuery.c_str());


	char	*szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), a_pFunCallback, a_pUserData, &szErrMsg);

}


void SqliteReader::GetAllRow(int a_nTableIndex, ITableData* a_pITableData)
{

	int rc = SQLITE_OK;
	if(!CheckTableIndex(a_nTableIndex)|| !m_DB)
		return;

	Trace(emTraceProgramProcess, "[SQLReader] Get Rows");


	// Query 문에 적합한 cols


	string strQuery;
	strQuery += "SELECT rowid, *  FROM ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += " ORDER BY rowid ";

	//Trace(emTraceSQLQuery, (const char*) strQuery.c_str());

	sqlite3_stmt* pStmt = NULL;

	rc = sqlite3_prepare(m_DB, strQuery.c_str(), -1, &pStmt, 0);
	if(rc != SQLITE_OK)
		return;

	//Trace(emTraceSQLQuery, strQuery);

	int nCol = 0;
	const char *szColName = NULL;
	int nColumnCount =  sqlite3_column_count(pStmt);

	// 첫번째 column 은 ID 이므로 하나를 뺀다.
	a_pITableData->SetColNum(nColumnCount - 1);


	for(nCol = 1; nCol < nColumnCount ; nCol++)
	{
		szColName = sqlite3_column_name(pStmt, nCol);
		a_pITableData->SetColName(nCol-1,szColName);

	}

	const unsigned char *szColData = NULL;
	int nRow = 0;
	while(sqlite3_step(pStmt) == SQLITE_ROW)
	{
		a_pITableData->AddRow();
		const unsigned char* szRowID = sqlite3_column_text(pStmt, 0);
		a_pITableData->SetRowID(nRow, reinterpret_cast<const char *>(szRowID));
		for(nCol = 1; nCol < nColumnCount ; nCol++)
		{
			szColData = sqlite3_column_text(pStmt, nCol);
			// column은 0부터 시작하므로 1을 빼준다.
			a_pITableData->SetData(nRow, nCol - 1, reinterpret_cast<const char *>(szColData));
		}
		nRow++;
	}


	sqlite3_reset(pStmt);
	sqlite3_finalize(pStmt);

}


bool SqliteReader::GetTableWithQuery(string a_strQuery, ITableData* a_pITableData)
{
	int rc = SQLITE_OK;
	if(!m_DB)
		return false;

	Trace(emTraceProgramProcess, "[SQLReader] Get Rows");
	//Trace(emTraceSQLQuery, (const char*) a_strQuery.c_str());

	sqlite3_stmt* pStmt = NULL;

	rc = sqlite3_prepare(m_DB, a_strQuery.c_str(), -1, &pStmt, 0);
	if(rc != SQLITE_OK)
		return false;

	//Trace(emTraceSQLQuery, a_strQuery);

	int nCol = 0;
	const char *szColName = NULL;
	int nColumnCount =  sqlite3_column_count(pStmt);

	a_pITableData->SetColNum(nColumnCount );


	for(nCol = 0; nCol < nColumnCount ; nCol++)
	{
		szColName = sqlite3_column_name(pStmt, nCol);
		a_pITableData->SetColName(nCol,szColName);

	}

	const unsigned char *szColData = NULL;
	int nRow = 0;
	while(sqlite3_step(pStmt) == SQLITE_ROW)
	{
		a_pITableData->AddRow();
		for(nCol = 0; nCol < nColumnCount ; nCol++)
		{
			szColData = sqlite3_column_text(pStmt, nCol);
			a_pITableData->SetData(nRow, nCol, reinterpret_cast<const char *>(szColData));
		}
		nRow++;
	}


	sqlite3_reset(pStmt);
	sqlite3_finalize(pStmt);
	return true;
}


ST_DBReaderErr SqliteReader::AddRow(int a_nTableIndex)
{
	int rc = SQLITE_OK;

	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);
	if(!CheckTableIndex(a_nTableIndex))
		return ErrTrans(eDBReaderInvalidTableIndex);

	vector<ST_ColInfo>::iterator it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	if(m_vecTableInfo[a_nTableIndex].arrColInfo.empty())
		return ErrTrans(eDBReaderUnknownFail);

	Trace(emTraceProgramProcess, "[SQLReader] Add Row");

	// "INSERT INTO Test(ID) VALUES(NULL);"
	string strQuery;
	strQuery += "INSERT INTO ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += "(";
	strQuery += it->strColName + ") VALUES(NULL);";


	SetDirty();
	char	*szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	return ErrTrans(rc);
}

ST_DBReaderErr SqliteReader::AddRow(int a_nTableIndex, Array2D<string> *a_pStringValue2D)
{
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ErrTrans(eDBReaderInvalidTableIndex);

	if(m_vecTableInfo[a_nTableIndex].arrColInfo.empty())
		return ErrTrans(eDBReaderUnknownFail);

	Trace(emTraceProgramProcess, "[SQLReader] Add Row with a_vecValueList2D");

	int nRowSize = a_pStringValue2D->GetRowSize();
	int rowIndex = 0;
	string strQuery;
	string colNameList = GetColNameString(eColInfoTypeName, a_nTableIndex);
	string colValueList;
	for ( rowIndex = 0 ; rowIndex < nRowSize ; rowIndex++)
	{

		colValueList = GetValueListString(a_nTableIndex, a_pStringValue2D, rowIndex);

		strQuery += "INSERT INTO ";
		strQuery += m_vecTableName[a_nTableIndex].c_str();
		strQuery += "(";
		strQuery += colNameList;
		strQuery += ") values(";
		strQuery += colValueList;
		strQuery += ");";
	}

	return ExecQuery(strQuery);
}



ST_DBReaderErr SqliteReader::DeleteRow(int a_nTableIndex, const char *a_szRowID)
{
	int rc = SQLITE_OK;

	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ErrTrans(eDBReaderInvalidTableIndex);

	Trace(emTraceProgramProcess, "[SQLReader] Delete Row");


	string strQuery;
	strQuery += "DELETE FROM ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += " WHERE rowid =";
	strQuery += a_szRowID;

	//Trace(emTraceSQLQuery, (const char*) strQuery.c_str());

	SetDirty();
	char	*szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	return ErrTrans(rc);
}

ST_DBReaderErr SqliteReader::DeleteRow(int a_nTableIndex, vector<string> a_vecIDList)
{
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ErrTrans(eDBReaderInvalidTableIndex);

	if(a_vecIDList.empty())
		return ErrTrans(eDBReaderUnknownFail);

	int rc = SQLITE_OK;

	Trace(emTraceProgramProcess, "[SQLReader] Delete Row");

	string strRowList = "( ";

	bool bFirstList = true;
	vector<string>::iterator it;
	for(it = a_vecIDList.begin() ; it != a_vecIDList.end(); it++)
	{
		if(!bFirstList)
			strRowList += " , ";
		bFirstList = false;
		strRowList += "\'";
		strRowList += *it;
		strRowList += "\'";
	}
	strRowList += " ) ";

	string strQuery;
	strQuery += "DELETE FROM ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += " WHERE rowid IN";
	strQuery += strRowList;

	//Trace(emTraceSQLQuery, (const char*) strQuery.c_str());

	SetDirty();
	char	*szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	return ErrTrans(rc);
}



ST_DBReaderErr SqliteReader::GetLastInsertRow(int a_nTableIndex, ITableData* a_pITableData)
{

	int rc = SQLITE_OK;
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ErrTrans(eDBReaderInvalidTableIndex);

	Trace(emTraceProgramProcess, "[SQLReader] GetLastInsertRow");

	sqlite3_int64 nLastInsertRowID = sqlite3_last_insert_rowid(m_DB);
	if(nLastInsertRowID == 0 )
		return ErrTrans(eDBReaderUnknownFail);


	char szRowID[BUFFER_SIZE];
	#ifdef _WIN32
		sprintf(szRowID, "%I64d ;", nLastInsertRowID);
	#else
		sprintf(szRowID, "%lld ;", nLastInsertRowID);
	#endif

	string strQuery;
	strQuery += "SELECT rowid, *  FROM ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += " where rowid == ";
	strQuery += szRowID;

	//Trace(emTraceSQLQuery, (const char*) strQuery.c_str());

	sqlite3_stmt* pStmt = NULL;

	rc = sqlite3_prepare(m_DB, strQuery.c_str(), -1, &pStmt, 0);
	if(rc != SQLITE_OK)
		return ErrTrans(rc);

	//Trace(emTraceSQLQuery, strQuery);

	int nCol = 0;
	const char *szColName = NULL;
	int nColumnCount =  sqlite3_column_count(pStmt);

	// 첫번째 column 은 ID 이므로 하나를 뺀다.
	a_pITableData->SetColNum(nColumnCount - 1);


	for(nCol = 1; nCol < nColumnCount ; nCol++)
	{
		szColName = sqlite3_column_name(pStmt, nCol);
		a_pITableData->SetColName(nCol-1,szColName);

	}

	const unsigned char *szColData = NULL;
	int nRow = 0;
	while(sqlite3_step(pStmt) == SQLITE_ROW)
	{
		a_pITableData->AddRow();
		const unsigned char* szRowID = sqlite3_column_text(pStmt, 0);
		a_pITableData->SetRowID(nRow, reinterpret_cast<const char *>(szRowID));
		for(nCol = 1; nCol < nColumnCount ; nCol++)
		{
			szColData = sqlite3_column_text(pStmt, nCol);
			// column은 0부터 시작하므로 1을 빼준다.
			a_pITableData->SetData(nRow, nCol - 1, reinterpret_cast<const char *>(szColData));
		}
		nRow++;
	}


	sqlite3_reset(pStmt);
	sqlite3_finalize(pStmt);

	return ST_DBReaderErr(eDBReaderSuccess);
}


ST_DBReaderErr SqliteReader:: ModifyRow(int a_nTableIndex, const char *a_szRowID, int a_nCol, const char *a_szData)
{

	int rc = SQLITE_OK;

	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ST_DBReaderErr(eDBReaderInvalidTableIndex);

	Trace(emTraceProgramProcess, "[SQLReader] ModifyRow");


	// UPDATE Test SET Value=? WHERE rowid=19;
	string strQuery;
	strQuery += "UPDATE ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += " SET ";
	strQuery +=  m_vecTableInfo[a_nTableIndex].arrColInfo[a_nCol].strColName;
	strQuery += "= \"";
	strQuery +=  a_szData;
	strQuery += "\" WHERE rowid=";
	strQuery += a_szRowID;

	//Trace(emTraceSQLQuery, (const char*) strQuery.c_str());

	SetDirty();
	char	*szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	return ErrTrans(rc);
}

ST_DBReaderErr SqliteReader::ModifyCol(int a_nTableIndex, int a_nCol, const char *a_szName, const char *a_szType)
{
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ST_DBReaderErr(eDBReaderInvalidTableIndex);

	SetDirty();

	Trace(emTraceProgramProcess, "[SQLReader] Modify COl");
	///////////////////////////////////////
	// CREATE TEMPORARY TABLE TEMP_TABLE(ID INTEGER PRIMARY KEY, Value TEXT);
	string strQuery = "CREATE TEMPORARY TABLE TEMP_TABLE";

	bool bFirstList = true;
	string strColDefList = "(";

	int nColIndex = 0;
	vector<ST_ColInfo>::iterator it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	for ( ; it !=m_vecTableInfo[a_nTableIndex].arrColInfo.end() ; ++it , nColIndex++ )
	{
		if(!bFirstList)
			strColDefList += ", ";
		bFirstList = false;

		if(nColIndex == a_nCol)
			strColDefList = strColDefList + a_szName + " " + a_szType;
		else
			strColDefList = strColDefList + it->strColName + " " + it->strColDataType;

		if(it->bPrimaryKey)
			strColDefList += " PRIMARY KEY";
	}
	strColDefList += ")";

	strQuery += strColDefList + ";";


	char	*szErrMsg = NULL;
	int rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);


	////////////////////////
	// "INSERT INTO TEMP_TABLE SELECT ID, Value FROM Test;";
	strQuery = "INSERT INTO TEMP_TABLE SELECT ";
	string strNewColNameList;
	string strOldColNameList;
	bFirstList = true;

	nColIndex = 0;
	it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	for ( ; it !=m_vecTableInfo[a_nTableIndex].arrColInfo.end(); ++it , nColIndex++)
	{
		if(!bFirstList)
		{
			strNewColNameList += ", ";
			strOldColNameList +=", ";
		}
		bFirstList = false;

		if(nColIndex == a_nCol)
			strNewColNameList = strNewColNameList + a_szName;
		else
			strNewColNameList = strNewColNameList + it->strColName;

		strOldColNameList = strOldColNameList + it->strColName;
	}

	strQuery += strOldColNameList + " FROM " + m_vecTableName[a_nTableIndex] + ";";

	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	///////////////////////////////////
	// DROP TABLE Test;
	strQuery = "DROP TABLE " +  m_vecTableName[a_nTableIndex];
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	// CREATE TABLE Test (ID INTEGER PRIMARY KEY, Value TEXT);
	strQuery = "CREATE TABLE " +  m_vecTableName[a_nTableIndex] + strColDefList + ";";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	// INSERT INTO Test SELECT ID, Value FROM TEMP_TABLE;
	strQuery = "INSERT INTO "+ m_vecTableName[a_nTableIndex] + " SELECT "+ strNewColNameList +" FROM TEMP_TABLE;";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	//DROP TABLE TEMP_TABLE;
	strQuery = "DROP TABLE TEMP_TABLE;";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	return ST_DBReaderErr(eDBReaderSuccess);
}

ST_DBReaderErr SqliteReader::ModifyCol(int a_nTableIndex, ST_TableInfo* a_pTableInfo)
{

	return ST_DBReaderErr(eDBReaderSuccess);
}

ST_DBReaderErr SqliteReader::AddCol(int a_nTableIndex,  const char *a_szName, const char *a_szType)
{
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ST_DBReaderErr(eDBReaderInvalidTableIndex);

	SetDirty();
	Trace(emTraceProgramProcess, "[SQLReader] Add COl");

	string strQuery ;
	string strColDefList;

	///////////////////////////////////////
	// "CREATE TEMPORARY TABLE TEMP_TABLE(ID, Value);"
	strQuery = "CREATE TEMPORARY TABLE TEMP_TABLE";
	strColDefList =  GetColNameString(eColInfoTypeName, a_nTableIndex);
	strQuery += "("+ strColDefList +  ");";


	char	*szErrMsg = NULL;
	int rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);


	////////////////////////
	// "INSERT INTO TEMP_TABLE SELECT ID, Value FROM Test;"
	strQuery = "INSERT INTO TEMP_TABLE SELECT " + strColDefList + " FROM " + m_vecTableName[a_nTableIndex] ;
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);


	///////////////////////////////////
	// DROP TABLE Test;
	strQuery = "DROP TABLE " +  m_vecTableName[a_nTableIndex];
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	// "CREATE TABLE Test (newColName newColType, ID INTEGER PRIMARY KEY, Value TEXT);"
	strColDefList = GetColNameString(eColInfoTypeName | eColInfoTypeType | eColInfoTypePrimary , a_nTableIndex);
	strColDefList =  string(" (") + a_szName + " " + a_szType + +", " + strColDefList + ")";
	strQuery = "CREATE TABLE " +  m_vecTableName[a_nTableIndex] + strColDefList + ";";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	// "INSERT INTO Test(ID, Value) SELECT ID, Value FROM TEMP_TABLE;"
	strColDefList = GetColNameString(eColInfoTypeName , a_nTableIndex);
	strQuery = "INSERT INTO "+ m_vecTableName[a_nTableIndex] + "(" + strColDefList + ") SELECT "+ strColDefList + " FROM TEMP_TABLE;";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	//DROP TABLE TEMP_TABLE;
	strQuery = "DROP TABLE TEMP_TABLE;";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	return ST_DBReaderErr(eDBReaderSuccess);
}

ST_DBReaderErr SqliteReader::DeleteCol(int a_nTableIndex, int a_nCol)
{
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ST_DBReaderErr(eDBReaderInvalidTableIndex);

	SetDirty();
	Trace(emTraceProgramProcess, "[SQLReader] DeleteCol COl");

	///////////////////////////////////////
	// CREATE TEMPORARY TABLE TEMP_TABLE(id INTEGER PRIMARY KEY, input varchar(80));
	string strQuery = "CREATE TEMPORARY TABLE TEMP_TABLE";

	bool bFirstList = true;
	string strColDefList = "(";

	int nColIndex = 0;
	vector<ST_ColInfo>::iterator it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	for ( ; it !=m_vecTableInfo[a_nTableIndex].arrColInfo.end() ; ++it , nColIndex++ )
	{
		if(nColIndex == a_nCol)
			continue;

		if(!bFirstList)
			strColDefList += ", ";
		bFirstList = false;

		strColDefList = strColDefList + it->strColName + " " + it->strColDataType;

		if(it->bPrimaryKey)
			strColDefList += " PRIMARY KEY";
	}
	strColDefList += ")";

	strQuery += strColDefList + ";";


	char	*szErrMsg = NULL;
	int rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	////////////////////////
	// "INSERT INTO TEMP_TABLE SELECT id, input FROM Suggest;"
	strQuery = "INSERT INTO TEMP_TABLE SELECT ";
	string strNewColNameList;
	bFirstList = true;

	nColIndex = 0;
	it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	for ( ; it !=m_vecTableInfo[a_nTableIndex].arrColInfo.end(); ++it , nColIndex++)
	{
		if(nColIndex == a_nCol)
			continue;

		if(!bFirstList)
			strNewColNameList += ", ";
		bFirstList = false;


		strNewColNameList = strNewColNameList + it->strColName;
	}

	strQuery += strNewColNameList + " FROM " + m_vecTableName[a_nTableIndex] + ";";

	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	///////////////////////////////////
	// DROP TABLE Suggest;
	strQuery = "DROP TABLE " +  m_vecTableName[a_nTableIndex];
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	// CREATE TABLE Suggest (id INTEGER PRIMARY KEY, input varchar(80));
	strQuery = "CREATE TABLE " +  m_vecTableName[a_nTableIndex] + strColDefList + ";";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	// INSERT INTO Suggest(id, input) SELECT id, input FROM TEMP_TABLE;
	strQuery = "INSERT INTO "+ m_vecTableName[a_nTableIndex] + "(" + strNewColNameList +")" +
				" SELECT "+ strNewColNameList +" FROM TEMP_TABLE;";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	/////////////////////////////////
	//DROP TABLE TEMP_TABLE;
	strQuery = "DROP TABLE TEMP_TABLE;";
	szErrMsg = NULL;
	rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	return ST_DBReaderErr(eDBReaderSuccess);
}


ST_DBReaderErr SqliteReader::AddTable(ST_TableInfo* a_pTableInfo)
{

	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);
	if(!a_pTableInfo)
		return ST_DBReaderErr(eDBReaderUnknownFail);

	SetDirty();
	Trace(emTraceProgramProcess, "[SQLReader] Add Table");

	///////////////////////////////////////
	// CREATE TABLE TableName (ID INTEGER PRIMARY KEY, input2 TEXT, output2 TEXT);
	string strQuery = "CREATE TABLE ";
	strQuery += a_pTableInfo->strTableName;

	bool bFirstList = true;
	string strColDefList = "(";

	int nColIndex = 0;
	vector<ST_ColInfo>::iterator it =  a_pTableInfo->arrColInfo.begin();
	for ( ; it != a_pTableInfo->arrColInfo.end() ; ++it , nColIndex++ )
	{

		if(!bFirstList)
			strColDefList += ", ";
		bFirstList = false;

		strColDefList = strColDefList + it->strColName + " " + it->strColDataType;

		if(it->bPrimaryKey)
			strColDefList += " PRIMARY KEY";
	}
	strColDefList += ")";

	strQuery += strColDefList + ";";


	char	*szErrMsg = NULL;
	int rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	return ST_DBReaderErr(eDBReaderSuccess);
}

ST_DBReaderErr SqliteReader::DeleteTable(int a_nTableNum)
{
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	SetDirty();
	Trace(emTraceProgramProcess, "[SQLReader] Delete Table");

	///////////////////////////////////////
	// DROP TABLE TableName;
	string strQuery = "DROP TABLE ";
	strQuery += m_vecTableName[a_nTableNum];


	char	*szErrMsg = NULL;
	int rc = sqlite3_exec(m_DB, strQuery.c_str(), NULL, NULL, &szErrMsg);
	if( rc != SQLITE_OK)
		return ErrTrans(rc);

	return ST_DBReaderErr(eDBReaderSuccess);
}

ST_DBReaderErr SqliteReader::Undo()
{
	if(m_nDirty <= 0 )
		return ST_DBReaderErr(eDBReaderUnknownFail);
	char query[BUFFER_SIZE];
	sprintf(query, "ROLLBACK TO SAVEPOINT savepoint_%d;", m_nDirty);
	ExecQuery(query, false);
	m_nDirty--;
	return ST_DBReaderErr(eDBReaderSuccess);
}

int SqliteReader::SQLCommitHook(void *)
{
	return 0;
}

bool SqliteReader::SetDirty()
{
	m_nDirty++;
	//ExecQuery("BEGIN TRANSACTION RESTOREPOINT;", false);
	char query[BUFFER_SIZE];
	sprintf(query, "SAVEPOINT savepoint_%d;", m_nDirty);
	ExecQuery(query, false);
	return true;
}

string SqliteReader::GetColNameString(unsigned int a_eColInfoType, unsigned int a_nTableIndex,
			unsigned int a_nChangeCol, const char* a_pszName, const char* a_pszzType, bool a_bPrimary)
{

	string strColsList;

	if(!CheckTableIndex(a_nTableIndex)|| !m_DB)
		return strColsList;

	bool bFirstList = true;
	unsigned int nIndex = 0;
	vector<ST_ColInfo>::iterator it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	for ( ; it !=m_vecTableInfo[a_nTableIndex].arrColInfo.end(); ++it, ++nIndex)
	{
		if(!bFirstList)
			strColsList += ",";
		bFirstList = false;


		if( a_eColInfoType & eColInfoTypeName )
		{
			if( a_nChangeCol == nIndex && a_pszName)
				strColsList += a_pszName;
			else
				strColsList += it->strColName;
		}

		if(a_eColInfoType & eColInfoTypeType)
		{
			if( a_nChangeCol == nIndex && a_pszzType)
				strColsList = strColsList + " " + a_pszzType;
			else
				strColsList = strColsList + " " + it->strColDataType;
		}

		if( a_eColInfoType & eColInfoTypePrimary)
		{
			if( a_nChangeCol == nIndex && a_bPrimary)
				strColsList += " PRIMARY KEY";
			else if(it->bPrimaryKey)
				strColsList += " PRIMARY KEY";
		}

		if(a_nChangeCol == nIndex && a_pszName)
			strColsList +=  it->strColName;
	}

	return strColsList;
}

string SqliteReader::GetValueListString(unsigned int a_nTableIndex, Array2D<string> *a_pStringValue2D, int a_nRow)
{
	vector<ST_ColInfo>::iterator colInfoListIt =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	int nColSize = a_pStringValue2D->GetColSize();
	string valueListString;
	string value;
	bool bFirstList = true;
	for(int nIndex = 0; nIndex < nColSize && colInfoListIt !=m_vecTableInfo[a_nTableIndex].arrColInfo.end() ; nIndex++ , colInfoListIt++)
	{
		if(!bFirstList) 
			valueListString += ",";
		bFirstList = false;
		value = a_pStringValue2D->GetData(a_nRow, nIndex);
		if(value == "") {
			if( colInfoListIt->bNotNull)
				value = "";
			else
				value = "null";
		}
		else{
			value = "\"" + value + "\"";
		}
		valueListString += value;
	}
	return valueListString;
}

void SqliteReader::Trace(TraceType_t a_eTraceType, const char* a_pszeMessage)
{
	MidInter* pMid = MidInter::GetInstance();
	if(pMid)
		pMid->Trace(a_eTraceType, a_pszeMessage);
}

void SqliteReader::Trace(TraceType_t a_eTraceType, string a_strMessage)
{
	MidInter* pMid = MidInter::GetInstance();
	if(pMid)
		pMid->Trace(a_eTraceType, a_strMessage.c_str());
}


ST_DBReaderErr SqliteReader::ErrTrans(int rc)
{
	switch(rc)
	{
	case SQLITE_OK: return ST_DBReaderErr(eDBReaderSuccess);
	}

	return ST_DBReaderErr(eDBReaderInternalError, rc);
}

bool SqliteReader::CheckTableIndex(int a_nIndex)
{
	if(m_vecTableName.size() <= a_nIndex || a_nIndex < 0)
		return false;
	return true;
}