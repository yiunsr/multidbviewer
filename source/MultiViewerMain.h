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
#ifndef __MultiViewerMain__
#define __MultiViewerMain__

/**
@file
Subclass of Main, which is generated by wxFormBuilder.
*/

#include "MainFrame.h"

#include <wx/log.h>
#include <wx/textctrl.h>
#include <wx/string.h>

#include "ml/MidInter.h"
#include "datastruct/Array2D.h"
#include "datastruct/VecArray2D.h"
#include "SQLReaderBase.h"
#include "SQLData.h"

#define BUFFER_SIZE 200

enum eProgramState{
	eStateInit = 0,
	eStateFileOpened,
	eStateTableSelected
};

enum eGridState{
	eGridCommon = 0,
	eGridAdding,
	eGridEditing,
};


/** Implementing Main */
class MultiViewerMain : public MainFrame
{
public:
	/** Constructor */
	MultiViewerMain( wxWindow* parent );
	~MultiViewerMain();


private:
	// USER Define control
	// 로그 기록을 위해
	#if wxUSE_LOG
		static wxLogTextCtrl*	mLogger;
		wxLog*			mLogOld;
		//wxStreamToTextRedirector *m_pRedirector;
	#endif // wxUSE_LOG

private:
	void Trace(TraceType_t traceType, const char* pszeMessage);
	void Trace(TraceType_t traceType, string strMessage);

	static void TraceMessage(const char* pMsg);


////// UI 와 연결되는 Callback
protected:
	void OnTableSelectButtonClick( wxCommandEvent& event );
	void OnTableDBGridCellChange( wxGridEvent& event );
	void OnTableDBGridLeftClick( wxGridEvent& event );

	//void OnTableDBGridLabelLeftClick( wxGridEvent& event );
	void OnTableDBGridLabelRightClick( wxGridEvent& event );

	void OnTableDBStartButtonClick( wxCommandEvent& event );
	void OnTableDBEndButtonClick( wxCommandEvent& event );

	void OnTableDBSliderUp( wxScrollEvent& event );
	void OnTableDBSliderDown( wxScrollEvent& event );
	void OnTableDBSliderRelease( wxScrollEvent& event );


	void OnCurrentRowTextCtrlKeyUp( wxKeyEvent& event );

	void OnQueryButtonClick( wxCommandEvent& event );
	void OnHistoryQueryLoad( wxCommandEvent& event );

	void OnUIFileNew( wxCommandEvent& event );
	void OnUIFileOpen( wxCommandEvent& event );
	void OnUIFileConnect( wxCommandEvent& event );
	void OnUIFileSave( wxCommandEvent& event );
	void OnUIFileExit( wxCommandEvent& event );
	void OnUILogView( wxCommandEvent& event );
	void OnUIHelpAbout( wxCommandEvent& event );
	void OnTableAdd( wxCommandEvent& event );
	void OnTableDelete( wxCommandEvent& event );
	void OnTableModify( wxCommandEvent& event );

	void OnAddRowButtonClick( wxCommandEvent& event );
	void OnUndo( wxCommandEvent& event );

private:
	void OnPopupClick(wxCommandEvent &event);
	void OnRowLabelRightClick( wxGridEvent& event );
	void OnColLabelRightClick( wxGridEvent& event );

private:
	void FileOpen(const char* a_strFileName );
	void Connect(const char* a_strHost, const char* a_strPort, const char* a_strDBName, const char* a_strID, const char* a_strPassword,  const char* a_strType  );
	void FileNew(const char* a_strFileName );
	void InitGrid(wxGrid* pGrid, bool a_bCleanCol = true);
	void SetColHeader(wxGrid* a_pwxGrid, vector<wxString>* a_pColName );
	void Restore(VecArray2D<wxString>* a_p2DTableData, vector<wxString>* a_pColName, wxGrid* a_pwxGrid ,int a_nStartRow, int a_nEndRow);
	void InitSQLTableInfo();
	void MoveEndGridRow(wxGrid* a_pGrid);
	

private:
	void SetCurPage(unsigned int a_nCurPage);

	bool AddTable();
	bool DeleteTable();
	bool DeleteTable(int a_nTableNum);
	bool ModifyTable();
	bool ModifyTable(int a_nTableNum);

	bool AddRow();
	bool AddSQLRow();
	bool ModifyRow(int a_nRow, int anCol, const char * a_szData);
	bool DeleteRow();
	bool DeleteRow(unsigned int a_nDelRow);

	bool ModifyCol();
	bool ModifyCol(unsigned int a_nModiCol);
	bool DeleteCol();
	bool DeleteCol(unsigned int a_nDelCol);
	bool AddCol();
	bool Undo();
	bool Reload(int a_nPage = 1);
	bool Refresh();

	
	static int CmpFunc(int *a_nFirst, int *a_nSecond)
	{
		if( *a_nFirst > *a_nSecond)
			return 1;
		else if(*a_nFirst == *a_nSecond)
			return 0;
		else
			return -1;
	}

	bool ConfirmNewDialog();
	void ErrorDialog(const char* message);

	void DoAddModeAction(int nTotalRow);

	void RefreshData(bool a_bLastInsertRowOnly);

private:
	SQLReaderBase* m_pSQLReader;
	typedef SelectRange<wxArrayInt> SelectRange_t;
	SelectRange_t mSelectRange;

private:
	VecArray2D<wxString>	m_2DtableData;
	vector<wxString>		m_vecDBRowId;
	vector<wxString>		m_vecDBColName;
	TABLEDBInfo m_DBDisplay;

private:
	VecArray2D<wxString>	m_2DQuerytableData;
	vector<wxString>	m_2DQueryDBColName;


private:	//grid event
	int m_nGridEventRow;
	int m_nGridEventCol;

private:
	bool	m_bDirty;
	eProgramState m_eProgramState;
	eGridState m_eGridState;
	int m_nSelectedTable;
	int m_nEditRow;
	int m_nEditRowCount;
	int m_nAddRow;
	int m_nCancelRow;

private:
	vector<wxString>	m_queryHistory;

};


class TableData : public ITableData
{

public:
	TableData(VecArray2D<wxString>* a_p2DtableData, vector<wxString>* a_vecDBRowId, vector<wxString>* a_vecDBColName );
	~TableData();
	void SetColNum(int a_nRowCount);
	void AddRow();
	void SetData(int  a_nRow, int a_nCol,const char *a_szData);
	void SetRowID(int a_nRow,const char *a_szData);
	void SetColName(int a_nCol,const char *a_szData);

	int GetCol(){	return m_nCol;	}
	int GetRow(){	return m_nRow;	}


private:
	int m_nCol;
	int m_nRow;
	VecArray2D<wxString>*	m_p2DTableData;
	vector<wxString>*		m_pVecDBRowId;
	vector<wxString>*		m_pVecDBColName;
};



//class SelectRange : public ISelectRange
//{
//
//public:
//	SelectRange(){}
//	~SelectRange(){}
//
//public:
//	wxArrayInt GetSelect(){	return m_wxarrSelect;	}
//	void SetSelect(wxArrayInt a_wxarrSelect){	m_wxarrSelect = a_wxarrSelect;	}
//
//private:
//	wxArrayInt m_wxarrSelect;
//
//};

#endif // __MultiViewerMain__
