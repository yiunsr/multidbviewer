#include "CubridReader.h"

#ifdef __CUBRID__SUPPORT__
#include "SQLData.h"
#include <cstdio>
#include <cstring>

using namespace std;

extern "C" {
	#include "cas_cci.h"
	//#include "cubrid-cci-win/include/cas_cci.h"
}

#define BUFFER_SIZE 512


CubridReader::CubridReader()
{
	m_DB = 0;
	m_nTotalTable = 0;
	m_nCurrentTable = 0;
	m_pStringArray2D = NULL;
	m_nDirty = 0;

}

CubridReader::~CubridReader()
{
	Finalize();
}

void CubridReader::Finalize()
{

}


ST_DBReaderErr  CubridReader::FileOpen(const char* a_pFileName)
{
	return ST_DBReaderErr(eDBReaderNotSupport);

}


ST_DBReaderErr  CubridReader::FileNew(const char* a_pFileName)
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}

ST_DBReaderErr  CubridReader::FileSave()
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}

eDBReaderErr_t  CubridReader::Connect(const char* a_pURL, const char* a_pPort,const char* a_pDBName, const char* a_pID, const char* a_pPassword, const char* a_pUserString)
{
	char buf[BUFFER_SIZE+1];

	int nPort = atoi(a_pPort);
	char* szURL = const_cast<char*>(a_pURL);
	char* szName = const_cast<char*>(a_pDBName);
	char* szID = const_cast<char*>(a_pID);
	char* szPassword = const_cast<char*>(a_pPassword);

	//cci_connect
	if ((m_DB=cci_connect(szURL, nPort, szName, szID, szPassword))<0) {
		return eDBReaderInternalError;
	}

	int res;
	if ((res = cci_get_db_version(m_DB, buf, BUFFER_SIZE)) < 0) {
		cci_get_err_msg (res, buf, BUFFER_SIZE);
		printf("get version error : %d, %s\n", res, buf);
	} else
		printf("database version : %s\n", buf);

	return eDBReaderSuccess;
}

eDBReaderErr_t CubridReader::Close()
{
	return eDBReaderNotSupport;
}

ST_DBReaderErr CubridReader::ExecQuery(const char* a_szQuery,  bool a_bDirty)
{
	int con = 0, req = 0, col_count = 0;
	int rc = 0;
	int nErr;
	T_CCI_ERROR cci_error;
	int res;

	T_CCI_COL_INFO* col_info;
	T_CCI_SQLX_CMD cmd_type;


	//// GOTO 대신 에러 처리를 위해 do while(0) 문을 사용한다.
	do {
		char* szQuery = const_cast<char*>(a_szQuery);
		req = cci_prepare (m_DB, szQuery, 0, &cci_error);
		if (req < 0)
			break;

		col_info = cci_get_result_info (req, &cmd_type, &col_count);
		if (col_info == NULL)
			break;

		nErr = cci_execute (req, 0, 0, &cci_error);
		if (nErr < 0)
			break;

		while (1)
		{
			nErr = cci_cursor (req, 1, CCI_CURSOR_CURRENT, &cci_error);
			if (nErr == CCI_ER_NO_MORE_DATA)
			{
				nErr = 0;
				break;
			}

			if (nErr < 0)
				break;

			nErr = cci_fetch (req, &cci_error);
			if (nErr < 0)
				break;

			int i = 0;
			int ind;
			char *data;
			for (i = 1; i <= col_count; i++)
			{
				nErr = cci_get_data (req, i, CCI_A_TYPE_STR, &data, &ind);
				if (nErr < 0)
					break;

				string strTemp( (char*)data);
				m_vecTableName.push_back(strTemp);
			}
			if (nErr < 0)
				break;
		}
		if (nErr < 0)
			break;

		/////// 성공적으로 실행하나 난 후..
		cci_close_req_handle (req);

	}while(0);

	//// Error 발생에 대한 처리

	if (req > 0)
		cci_close_req_handle (req);

	return ErrTrans(rc);
}

ST_DBReaderErr  CubridReader::GetMainTable()
{
	//int nRet = cci_schema_info(int conn_handle, T_CCI_SCHEMA_TYPE type, char *class_name, char *attr_name, char flag, T_CCI_ERROR *err_buf);
	//return eDBReaderNotSupport;

	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	Trace(emTraceProgramProcess, "[SQLReader] Find Main Table");

	m_vecTableName.clear();

	int con = 0, req = 0, col_count = 0;
	int rc = 0;
	int nErr;
	T_CCI_ERROR cci_error;
	int res;

	T_CCI_COL_INFO* col_info;
	T_CCI_SQLX_CMD cmd_type;



	//// GOTO 대신 에러 처리를 위해 do while(0) 문을 사용한다.
	do {

		req = cci_prepare (m_DB, "SELECT  class_name FROM DB_CLASS where is_system_class='NO'", 0, &cci_error);
		if (req < 0)
			break;

		col_info = cci_get_result_info (req, &cmd_type, &col_count);
		if (col_info == NULL)
			break;

		nErr = cci_execute (req, 0, 0, &cci_error);
		if (nErr < 0)
			break;

		while (1)
		{
			nErr = cci_cursor (req, 1, CCI_CURSOR_CURRENT, &cci_error);
			if (nErr == CCI_ER_NO_MORE_DATA)
			{
				nErr = 0;
				break;
			}

			if (nErr < 0)
				break;

			nErr = cci_fetch (req, &cci_error);
			if (nErr < 0)
				break;

			int i = 0;
			int ind;
			char *data;
			for (i = 1; i <= col_count; i++)
			{
				nErr = cci_get_data (req, i, CCI_A_TYPE_STR, &data, &ind);
				if (nErr < 0)
					break;

				string strTemp( (char*)data);
				m_vecTableName.push_back(strTemp);
			}
			if (nErr < 0)
				break;
		}
		if (nErr < 0)
			break;

		/////// 성공적으로 실행하나 난 후..
		cci_close_req_handle (req);

	}while(0);

	//// Error 발생에 대한 처리

	if (req > 0)
		cci_close_req_handle (req);

	return ErrTrans(rc);
}


vector<string> CubridReader::GetColName()
{

	vector<string> vecCols;
	return vecCols;

}




vector<ST_TableInfo>  CubridReader::GetTableInfo(bool a_bReload)
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


vector<ST_ColInfo> CubridReader::GetTableInfo(int a_nTableIndex, bool a_bReload)
{
	//vector<ST_ColInfo> vecCols;
	//return vecCols;

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

	int con = 0, req = 0, col_count = 0;
	int rc = 0;
	int nErr;
	T_CCI_ERROR cci_error;
	int res;

	T_CCI_COL_INFO* col_info;
	T_CCI_SQLX_CMD cmd_type;


	//// GOTO 대신 에러 처리를 위해 do while(0) 문을 사용한다.
	do {

		eDBReaderErr_t eDBReaderErr = eDBReaderSuccess;
		vector<string> vecColType = GetColType(a_nTableIndex, &eDBReaderErr);
		if(eDBReaderErr != eDBReaderSuccess || vecColType.empty())
			return vecCols;

		char* szQuery = const_cast<char*>( m_vecTableName[a_nTableIndex].c_str() );
		req  = cci_schema_info(m_DB, CCI_SCH_ATTRIBUTE,  szQuery, NULL, CCI_ATTR_NAME_PATTERN_MATCH, &cci_error);
		if (req  < 0)
			break;

		col_info = cci_get_result_info (req, &cmd_type, &col_count);
		if (col_info == NULL)
			break;

		vector<string>::iterator it =  vecColType.begin();
		while (1)
		{
			nErr = cci_cursor (req, 1, CCI_CURSOR_CURRENT, &cci_error);
			if (nErr == CCI_ER_NO_MORE_DATA)
			{
				nErr = 0;
				break;
			}

			if (nErr < 0)
				break;

			nErr = cci_fetch (req, &cci_error);
			if (nErr < 0)
				break;

			int i = 0;
			int ind;
			char *szData;

			ST_ColInfo stColinfo;
			//////  Name ////////
			szData = NULL;
			nErr = cci_get_data (req, 1, CCI_A_TYPE_STR, &szData, &ind);
			if (nErr < 0)
				break;

			string strColName = szData;
			stColinfo.strColName = strColName;

			////// NON_NULL ////////
			nErr = cci_get_data (req, 6, CCI_A_TYPE_STR, &szData, &ind);
			if (nErr < 0)
				break;

			if( strncmp(szData, "1",2) == 0 )
				stColinfo.bNotNull = true;

			////// DEFAULT ////////
			szData = NULL;
			nErr = cci_get_data (req, 9, CCI_A_TYPE_STR, &szData, &ind);
			if (nErr < 0)
				break;

			if(szData)
			{
				string strDefault = szData;
				stColinfo.strDefault = szData;
			}

			////// Key ////////
			nErr = cci_get_data (req, 13, CCI_A_TYPE_STR, &szData, &ind);
			if (nErr < 0)
				break;

			if( strncmp(szData, "1", 2) == 0)
				stColinfo.bPrimaryKey = true;

			////// Type ////////
			if(it == vecColType.end())
				break;
			stColinfo.strColDataType = string(*it);
			it++;

			m_vecTableInfo[a_nTableIndex].arrColInfo.push_back(stColinfo);

		}
		if (nErr < 0)
			break;

		/////// 성공적으로 실행하나 난 후..
		cci_close_req_handle (req);

	}while(0);

	//// Error 발생에 대한 처리

	if (req > 0)
		cci_close_req_handle (req);

	return m_vecTableInfo[a_nTableIndex].arrColInfo;
}



ST_DBReaderErr CubridReader::GetTable(const char* a_szSql, char*** a_pszResult, int* a_pnRow, int* a_pnColum )
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}



void CubridReader::GetAllRow(int a_nTableIndex, DBCallback_t a_pFunCallback  , void *a_pUserData)
{


}


void CubridReader::GetAllRow(int a_nTableIndex, ITableData* a_pITableData)
{
	if(!CheckTableIndex(a_nTableIndex)|| !m_DB)
		return;

	Trace(emTraceProgramProcess, "[SQLReader] Get Rows");

	string strColDefList = GetColNameString(eColInfoTypeName , a_nTableIndex);
	string strQuery = "select " + m_vecTableName[a_nTableIndex] + ",";
	strQuery += strColDefList + " from " + m_vecTableName[a_nTableIndex] + ";";
	//strQuery += m_vecTableName[a_nTableIndex];
	//strQuery += "'  ORDER by def_order;";

	int req = 0, nColumnCount = 0;
	int nErr;
	T_CCI_ERROR cci_error;

	T_CCI_COL_INFO* col_info;
	T_CCI_SQLX_CMD cmd_type;

	//// GOTO 대신 에러 처리를 위해 do while(0) 문을 사용한다.
	do {
		char* szQuery = const_cast<char*>(strQuery.c_str());
		req = cci_prepare (m_DB,szQuery, 0, &cci_error);
		if (req < 0)
			break;

		col_info = cci_get_result_info (req, &cmd_type, &nColumnCount);
		if (col_info == NULL)
			break;

		// 첫번째 column 은 ID 이므로 하나를 뺀다.
		a_pITableData->SetColNum(nColumnCount - 1);

		int nCol = 0;
		for (nCol = 2; nCol <= nColumnCount; nCol++)
		{
			char *szColName = CCI_GET_RESULT_INFO_NAME (col_info, nCol);
			//// cubride 는 첫번째 column이 1 부터 시작하고 , 2번째 column은 oid(rowid)이므로 2를 뺀다.
			a_pITableData->SetColName(nCol-2,szColName);
		}


		nErr = cci_execute (req, 0, 0, &cci_error);
		if (nErr < 0)
			break;

		int nRow = 0;
		while (nErr >= 0)
		{
			nErr = cci_cursor (req, 1, CCI_CURSOR_CURRENT, &cci_error);
			if (nErr == CCI_ER_NO_MORE_DATA)
			{
				nErr = 0;
				break;
			}

			if (nErr < 0)
				break;

			nErr = cci_fetch (req, &cci_error);
			if (nErr < 0)
				break;

			int ind;
			char *szRowID;
			nErr = cci_get_data (req, 1, CCI_A_TYPE_STR, &szRowID, &ind);
			if (nErr < 0)
				break;

			a_pITableData->AddRow();
			a_pITableData->SetRowID(nRow, szRowID);


			char *szColData;
			for (nCol = 2; nCol <= nColumnCount; nCol++)
			{
				nErr = cci_get_data (req, nCol, CCI_A_TYPE_STR, &szColData, &ind);
				if (nErr < 0)
					break;

				//// cubride 는 첫번째 column이 1 부터 시작하고 , 2번째 column은 oid(rowid)이므로 2를 뺀다.
				a_pITableData->SetData(nRow, nCol - 2, szColData);
			}
			nRow ++;


		}
		if (nErr < 0)
			break;

		/////// 성공적으로 실행하나 난 후..
		cci_close_req_handle (req);

	}while(0);

	//// Error 발생에 대한 처리


}


bool CubridReader::GetTableWithQuery(string a_strQuery, ITableData* a_pITableData)
{
	return true;
}


ST_DBReaderErr CubridReader::AddRow(int a_nTableIndex)
{
	int rc = SQLITE_OK;
	if(!m_DB)
		return ST_DBReaderErr(eDBReaderDBNotPrepare);

	if(!CheckTableIndex(a_nTableIndex))
		return ST_DBReaderErr(eDBReaderInvalidTableIndex);

	vector<ST_ColInfo>::iterator it =  m_vecTableInfo[a_nTableIndex].arrColInfo.begin();
	if(m_vecTableInfo[a_nTableIndex].arrColInfo.empty())
		return eDBReaderUnknownFail;

	Trace(emTraceProgramProcess, "[SQLReader] Add Row");

	// "INSERT INTO Test(ID) VALUES(NULL);"
	string strQuery;
	strQuery += "INSERT INTO ";
	strQuery += m_vecTableName[a_nTableIndex].c_str();
	strQuery += "(";
	strQuery += it->strColName + ") VALUES(NULL);";


	SetDirty();
	return ExecQuery(strQuery.c_str());
}

ST_DBReaderErr CubridReader::AddSQLRow(int a_nTableIndex,vector<string> a_vecValueList)
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}

ST_DBReaderErr CubridReader::DeleteRow(int a_nTableIndex, const char *a_szRowID)
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}

ST_DBReaderErr CubridReader::DeleteRow(int a_nTableIndex, vector<string> a_vecIDList)
{

	return ST_DBReaderErr(eDBReaderNotSupport);
}



ST_DBReaderErr CubridReader::GetLastInsertRow(int a_nTableIndex, ITableData* a_pITableData)
{

	return ST_DBReaderErr(eDBReaderNotSupport);
}


ST_DBReaderErr CubridReader:: ModifyRow(int a_nTableIndex, const char *a_szRowID, int a_nCol, const char *a_szData)
{

	return ST_DBReaderErr(eDBReaderNotSupport);
}

ST_DBReaderErr CubridReader::ModifyCol(int a_nTableIndex, int a_nCol, const char *a_szName, const char *a_szType)
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}


ST_DBReaderErr CubridReader::AddCol(int a_nTableIndex,  const char *a_szName, const char *a_szType)
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}

ST_DBReaderErr CubridReader::DeleteCol(int a_nTableIndex, int a_nCol)
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}


ST_DBReaderErr CubridReader::AddTable(ST_TableInfo* a_pTableInfo)
{

	return ST_DBReaderErr(eDBReaderNotSupport);
}

ST_DBReaderErr CubridReader::DeleteTable(int a_nTableNum)
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}

ST_DBReaderErr CubridReader::Undo()
{
	return ST_DBReaderErr(eDBReaderNotSupport);
}

int CubridReader::SQLCommitHook(void *a_pUser)
{
	return 0;
}

bool CubridReader::SetDirty()
{
	m_nDirty++;
	return true;
}

string CubridReader::GetColNameString(unsigned int a_eColInfoType, unsigned int a_nTableIndex,
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

ST_DBReaderErr CubridReader::ErrTrans(int rc)
{
	switch(rc)
	{
		case 0: return ST_DBReaderErr(eDBReaderSuccess);
		case CCI_ER_CONNECT:
			return CCI_ER_CONNECT(eDBReaderInternalError, rc);
	}

	return CCI_ER_CONNECT(eDBReaderInternalError, rc);
}

vector<string> CubridReader::GetColType(int a_nTableIndex, CCI_ER_CONNECT* pstDBReaderErr)
{
	vector<string> vecColType;

	string strQuery = "select data_type from db_attribute where class_name='";
	strQuery += m_vecTableName[a_nTableIndex];
	strQuery += "'  ORDER by def_order;";

	int req = 0, col_count = 0;
	int nErr;
	T_CCI_ERROR cci_error;

	T_CCI_COL_INFO* col_info;
	T_CCI_SQLX_CMD cmd_type;

	//// GOTO 대신 에러 처리를 위해 do while(0) 문을 사용한다.
	do {
		char* szQuery = const_cast<char*>(strQuery.c_str());
		req = cci_prepare (m_DB,szQuery, 0, &cci_error);
		if (req < 0)
			break;

		col_info = cci_get_result_info (req, &cmd_type, &col_count);
		if (col_info == NULL)
			break;

		nErr = cci_execute (req, 0, 0, &cci_error);
		if (nErr < 0)
			break;

		while (1)
		{
			nErr = cci_cursor (req, 1, CCI_CURSOR_CURRENT, &cci_error);
			if (nErr == CCI_ER_NO_MORE_DATA)
			{
				nErr = 0;
				break;
			}

			if (nErr < 0)
				break;

			nErr = cci_fetch (req, &cci_error);
			if (nErr < 0)
				break;

			int ind;
			char *data;
			nErr = cci_get_data (req, 1, CCI_A_TYPE_STR, &data, &ind);
			if (nErr < 0)
				break;

			string strTemp( (char*)data);
			vecColType.push_back(strTemp);
		}
		if (nErr < 0)
			break;

		/////// 성공적으로 실행하나 난 후..
		cci_close_req_handle (req);
		return vecColType;

	}while(0);

	//// Error 발생에 대한 처리

	*pstDBReaderErr = ErrTrans(nErr) ;
	if (req > 0)
		cci_close_req_handle (req);

	vecColType.clear();
	return vecColType;

}

bool CubridReader::CheckTableIndex(int a_nIndex)
{
	if(m_vecTableName.size() <= a_nIndex || a_nIndex < 0)
		return false;
}

#endif