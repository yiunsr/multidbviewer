#include "MultiViewerMain.h"


#include <wx/aboutdlg.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/tooltip.h>
#include <wx/utils.h>	// ::wxGetMousePosition 함수 이용을 위해
#include <wx/msgdlg.h>

#include "Config.h"
#include "SQLUtil.h"
#include "GridUtil.h"

#include "MultiViewerColDataDlg.h"
#include "MultiViewerTableNameDlg.h"
#include "MultiViewerTableNameSelectDlg.h"
#include "MultiViewerConnectDlg.h"

#include "SqliteReader.h"
#include "CubridReader.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define GridAddingModeRowCount 2

#if wxUSE_LOG
	wxLogTextCtrl*	MultiViewerMain::mLogger = NULL;
#endif // wxUSE_LOG

const char* CURBRID_TYPENAME = "cubrid";

MultiViewerMain::MultiViewerMain( wxWindow* parent )
:MainFrame( parent )
{
	m_nGridEventRow = m_nGridEventCol = 0;
	m_eProgramState = eStateInit;
	m_eGridState = eGridCommon;
	m_bDirty = false;
	m_nSelectedTable = 0;
	m_pSQLReader = NULL;

	m_nEditRow = -1;
	m_nEditRowCount = 0;
	m_nAddRow = -1;
	m_nCancelRow = -1;

	////// Trace 를 볼 수 있게 하기 위해  Log 를 연결함
#if wxUSE_LOG
	mLogger = new wxLogTextCtrl( m_pLOGTextCtrl);

	mLogOld = wxLog::SetActiveTarget( mLogger );
	wxLog::SetTimestamp( "" );

	MidInter* pMid = NULL;
	pMid = MidInter::GetInstance();
	pMid->SetTraceCB(MultiViewerMain::TraceMessage);
#endif // wxUSE_LOG

#if	DEBUG_AUTO_FILE_LOAD
	m_pSQLReader = new SqliteReader();
	FileOpen( "..\\db\\test.db" );
#endif 
}

MultiViewerMain::~MultiViewerMain()
{
#if wxUSE_LOG
    delete wxLog::SetActiveTarget(mLogOld);

	MidInter::Finalize();
#endif // wxUSE_LOG

	if(m_pSQLReader)
		delete m_pSQLReader;
	Config::Finalize();
}

void MultiViewerMain::OnUIFileNew(wxCommandEvent& )
{

	Trace(emTraceProgramProcess, "File New");

	if(!ConfirmNewDialog())
	{
		return;
	}
	m_pSQLReader = new SqliteReader();
	
	wxString wxstrFileNmae;
    wxFileDialog fileDlg(this, SQLUtil::str2wxstr("Select Where to save"), SQLUtil::str2wxstr(""),SQLUtil::str2wxstr(""),
			SQLUtil::str2wxstr("*.db"), wxFD_SAVE  );
	if(fileDlg.ShowModal() != wxID_OK)
	{
		fileDlg.Destroy();
		return;
	}


	wxstrFileNmae = fileDlg.GetDirectory();
	wxstrFileNmae.Append(wxFileName::GetPathSeparator());
	wxstrFileNmae += fileDlg.GetFilename();
	std::string strFileName = SQLUtil::wxstr2str(wxstrFileNmae);
	FileNew( strFileName.c_str() );

}

void MultiViewerMain::FileNew(const char* a_strFileName )
{
	
	m_pSQLReader->FileNew(a_strFileName );

	m_eProgramState = eStateFileOpened;
	InitSQLTableInfo();
	InitGrid(m_pTableDBDataGrid, true);
	m_bDirty = false;

}

void MultiViewerMain::OnUIFileOpen(wxCommandEvent& )
{
    //wxMessageBox(_("Test"), _("OnMenuFileOpen"));

	Trace(emTraceProgramProcess, "File Open");

	if(!ConfirmNewDialog())
	{
		return;
	}

    wxString wxstrFileNmae;
    wxFileDialog fileDlg(this);
	if(fileDlg.ShowModal() != wxID_OK)
	{
		fileDlg.Destroy();
		return;
	}
	m_pSQLReader = new SqliteReader();


	wxstrFileNmae = fileDlg.GetDirectory();
	wxstrFileNmae.Append(wxFileName::GetPathSeparator());
	wxstrFileNmae += fileDlg.GetFilename();
	std::string strFileName = SQLUtil::wxstr2str(wxstrFileNmae);
	FileOpen( strFileName.c_str() );
	fileDlg.Destroy();

}


void MultiViewerMain::FileOpen(const char* a_strFileName )
{
	if(m_eProgramState == eStateFileOpened && m_bDirty)
	{
//		wxMessageBox(_("Test"), _("OnMenuFileOpen"));

	}
	
	m_pSQLReader->FileOpen(a_strFileName );
	m_eProgramState = eStateFileOpened;
	InitSQLTableInfo();
	InitGrid(m_pTableDBDataGrid, true);
	m_bDirty = false;
}

void MultiViewerMain::OnUIFileConnect( wxCommandEvent&  )
{
	Trace(emTraceProgramProcess, "File Connect");

	if(!ConfirmNewDialog())
	{
		return;
	}

	MultiViewerConnectDlg conectDlg(this);
	conectDlg.AddConnectType(CURBRID_TYPENAME);
	conectDlg.SetData("localhost", "30000", "myTest", "test", "test2357" );
	if( wxID_CANCEL == conectDlg.ShowModal() )
		return;
	string strHost = SQLUtil::wxstr2str( conectDlg.GetHost() );
	string strPort = SQLUtil::wxstr2str( conectDlg.GetPort() );

	string strDBName = SQLUtil::wxstr2str( conectDlg.GetDBName() );

	string strID = SQLUtil::wxstr2str( conectDlg.GetID() );
	string strPassword = SQLUtil::wxstr2str( conectDlg.GetPassword() );

	string strType = SQLUtil::wxstr2str( conectDlg.GetType() );


	Connect(strHost.c_str(), strPort.c_str(), strDBName.c_str(), strID.c_str(), strPassword.c_str(), strType.c_str() );

}

void MultiViewerMain::Connect(const char* a_strHost, const char* a_strPort, const char* a_strDBName, const char* a_strID, const char* a_strPassword, const char* a_strType)
{
#ifdef __CUBRID__SUPPORT__
	if(strncmp(a_strType, CURBRID_TYPENAME , strlen(CURBRID_TYPENAME)) == 0)
		m_pSQLReader = new CubridReader();

	else
		return;

	eDBReaderErr_t  eDBReaderErr = m_pSQLReader->Connect(a_strHost, a_strPort, a_strDBName, a_strID, a_strPassword, NULL);
	if(eDBReaderSuccess != eDBReaderErr )
	{
		ErrorDialog("Connect Error");
		return;
	}

	m_eProgramState = eStateFileOpened;
	InitSQLTableInfo();
	InitGrid(m_pTableDBDataGrid, true);
	m_bDirty = false;
#else
	ErrorDialog("This version not support this action");
	return;
#endif
}


void MultiViewerMain::OnUIFileSave(wxCommandEvent& )
{
	Trace(emTraceProgramProcess, "UI File Save");
	switch(m_eProgramState)
	{
	case 	eStateInit:
		return;
	default:
		break;
	}
	m_pSQLReader->FileSave();
	m_bDirty = false;
}

void MultiViewerMain::OnUIFileExit(wxCommandEvent& )
{
	Close();
}

void MultiViewerMain::OnUILogView(wxCommandEvent& event)
{
	bool bShow = event.IsChecked();
	m_pLOGTextCtrl->Show(bShow);
	m_pDebugPanel->Show(bShow);
	Layout();
}

void MultiViewerMain::OnUIHelpAbout( wxCommandEvent&  )
{
	wxAboutDialogInfo oInfo;
	oInfo.SetVersion(_T(__VERSION__));
	oInfo.AddDeveloper(_T("Yiun Seungryong()"));
	oInfo.SetCopyright(_T("(C) 2009 Yiunsr  <nahanmil@gmail.com>"));

	wxAboutBox( oInfo );
}

void MultiViewerMain::OnTableAdd( wxCommandEvent&  )
{
	Trace(emTraceProgramProcess, "UI Table Add");

	AddTable();
}


void MultiViewerMain::OnTableDelete( wxCommandEvent&  )
{
	Trace(emTraceProgramProcess, "UI Table Delete");

	DeleteTable();
}

void MultiViewerMain::OnTableModify( wxCommandEvent&  )
{
	Trace(emTraceProgramProcess, "UI Table Modify");

	ModifyTable();
}

void MultiViewerMain::OnAddRowButtonClick( wxCommandEvent&  )
{
	Trace(emTraceProgramProcess, "UI Row Add");
	AddRow();
}

void MultiViewerMain::OnUndo( wxCommandEvent&  )
{
	Trace(emTraceProgramProcess, "UI Undo");
	Undo();
}

void MultiViewerMain::TraceMessage(const char *pMsg)
{
	wxString xstrMsg(pMsg, wxConvUTF8);
	mLogger->OnLog(wxLogLevel(4),xstrMsg, time_t(0));
}


void MultiViewerMain::Trace(TraceType_t traceType, const char* pszeMessage)
{
	MidInter* pMid = MidInter::GetInstance();
	if(pMid)
		pMid->Trace(traceType, pszeMessage);
}

void MultiViewerMain::Trace(TraceType_t traceType, string strMessage)
{
	MidInter* pMid = MidInter::GetInstance();
	if(pMid)
		pMid->Trace(traceType, strMessage.c_str());
}



void MultiViewerMain::OnTableSelectButtonClick(wxCommandEvent& )
{

	if(m_eProgramState == eStateInit)
		return;

	int nSelect = m_pTableNameChoice->GetSelection();
	if( nSelect == -1)
		return;

	m_nSelectedTable = nSelect;
	m_eProgramState = eStateTableSelected;

	m_2DtableData.ClearAll();

	TableData oTableData(&m_2DtableData, &m_vecDBRowId, &m_vecDBColName);
	m_pSQLReader->GetAllRow(nSelect, &oTableData);

	m_pTableDBDataGrid->AppendCols(oTableData.GetCol());

	int nTotalRow = oTableData.GetRow();
	wxString wxstrTotal;
	wxstrTotal.Printf(_T("/ %d"), nTotalRow);
	m_pTotalStaticText->SetLabel(wxstrTotal);

	wxString wxstrCurrentRow;
	wxstrCurrentRow.Printf(_T("%d"), 1);
	m_pCurrentRowTextCtrl->SetValue(wxstrCurrentRow);

	m_DBDisplay.SetTotal(nTotalRow);
	mTableDBSlider->SetPageSize(1);
	mTableDBSlider->SetRange(1, m_DBDisplay.GetTotalPage());
	mTableDBSlider->SetValue(1);

	SetCurPage(1);

}


void MultiViewerMain::OnTableDBGridCellChange(wxGridEvent& event)
{
	int nRow = event.GetRow();
	int nCol = event.GetCol();

	if(eGridAdding == m_eGridState &&  m_nEditRow <= nRow)  {
		event.Skip();
		return;
	}

	wxString wxStrCellValue = m_pTableDBDataGrid->GetCellValue(nRow, nCol);
	string szStrCellVale = SQLUtil::wxstr2str(wxStrCellValue);
	ModifyRow(nRow, nCol, szStrCellVale.c_str() );
}

void MultiViewerMain::OnTableDBGridLeftClick( wxGridEvent& event )
{
	if(eGridAdding != m_eGridState) {
		event.Skip();
		return;
	}


	if(m_nAddRow == event.GetRow())
	{
		if(	AddSQLRow() == false) 
			return;
	}
	else if(m_nCancelRow == event.GetRow())
	{
		int nTotalRow = m_pTableDBDataGrid->GetNumberRows();
		m_pTableDBDataGrid->DeleteRows(m_nEditRow, m_nEditRowCount + GridAddingModeRowCount);
		m_nEditRow = -1;
		m_nAddRow = -1;
		m_nCancelRow = -1;
	}
	else
	{
		event.Skip();
		return;
	}

	m_eGridState = eGridCommon;
}

enum{
	eUserEventStart = 2000,
	eSelectAllOnPage,
	eDeleteAll,
	eAddRow,
	eDeleteCurrentRow,
	eModifyCurrentCol,
	eDeleteCurrentCol,
	eAddCol,
}eUserEvent_t;


void MultiViewerMain::OnPopupClick(wxCommandEvent &evt)
{
	switch(evt.GetId()) {
	case eSelectAllOnPage:
		m_pTableDBDataGrid->SelectAll();
		break;
	case eDeleteAll:
		m_pTableDBDataGrid->SelectAll();
		break;
	case eAddRow:
		AddRow();
		break;
	case eDeleteCurrentRow:
		DeleteRow();
		break;
	case eModifyCurrentCol:
		ModifyCol();
		break;
	case eDeleteCurrentCol:
		DeleteCol();
		break;
	case eAddCol:
		AddCol();
		break;
	default:
		break;
	}

}


void MultiViewerMain::OnTableDBGridLabelRightClick( wxGridEvent& event )
{
	if(m_eProgramState == eStateInit  || m_eProgramState == eStateFileOpened)
		return;

	//wxGrid::wxGridSelectionModes eGridSelectMode = m_pTableDBDataGrid->GetSelectionMode();
	//m_nGridEventRow = event.GetRow();
	//m_nGridEventCol = event.GetCol();


	if( event.GetRow() >= 0  && event.GetCol() < 0 )
		return OnRowLabelRightClick(event);

	if( event.GetCol() >= 0  && event.GetRow() < 0 )
		return OnColLabelRightClick(event);

	if( event.GetRow() > 0 && event.GetCol() > 0 )
		return;

	wxMenu oMenu;
	oMenu.Append(eSelectAllOnPage, 	_T("Select All On Page"));
	oMenu.Append(eDeleteAll, _T("Select All "));
	oMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&MultiViewerMain::OnPopupClick, NULL, this);
	m_pTableDBDataGrid->PopupMenu(&oMenu);

}

void MultiViewerMain::OnRowLabelRightClick( wxGridEvent& event )
{
	bool bSelectAll = false;

	wxArrayInt wxarrSelectRows = m_pTableDBDataGrid->GetSelectedRows();
	if( static_cast<int>(wxarrSelectRows.Count()) == m_pTableDBDataGrid->GetNumberRows())
		bSelectAll = true;

	// 우선 이 기능은 구현 안 한다. 너무 어렵다. Shift 와 마우스를 사용했을 때에는 필요하겠지만...
	//wxGridCellCoordsArray wxarrCellTopLeft = m_pTableDBDataGrid->GetSelectionBlockTopLeft();
	//wxGridCellCoords *topLeft = NULL;
	//if(!wxarrCellTopLeft.IsEmpty())
	//	topLeft = &(wxarrCellTopLeft.Item(0));

	//wxGridCellCoordsArray wxarrCellBottomRight = m_pTableDBDataGrid->GetSelectionBlockBottomRight();
	//wxGridCellCoords *bottomRight = NULL;
	//if(!wxarrCellBottomRight.IsEmpty())
	//	bottomRight = &(wxarrCellBottomRight.Item(0));


	// 현재 Row 를 중심으로 Select 할 때는 다시 Select 안 함
	if(bSelectAll
		||  (wxarrSelectRows.Count() > 0 && wxNOT_FOUND != wxarrSelectRows.Index(event.GetRow())) )
		;	// do nothing
	else
	{
		m_pTableDBDataGrid->ClearSelection();
		m_pTableDBDataGrid->SelectRow(event.GetRow());
		wxarrSelectRows.Add(event.GetRow());
	}

	mSelectRange.SetSelectMode(SelectRange_t::eRow);
	mSelectRange.SetSelect(wxarrSelectRows);

	wxMenu oMenu;

	if(m_eGridState != eGridAdding){
		oMenu.Append(eAddRow, 	_T("Add New Row"));
		oMenu.Append(eDeleteCurrentRow, 	_T("Delete Current Row"));
	}
	else{
		int nTotalRow = m_pTableDBDataGrid->GetNumberRows();
		int nCurrentSelectRow = event.GetRow();
		if( m_nEditRow > nCurrentSelectRow)
			oMenu.Append(eDeleteCurrentRow, 	_T("Delete Current Row"));
	}

	oMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&MultiViewerMain::OnPopupClick, NULL, this);
	m_pTableDBDataGrid->PopupMenu(&oMenu);
	return;

}

void MultiViewerMain::OnColLabelRightClick( wxGridEvent& event )
{
	bool bSelectAll = false;

	wxArrayInt wxarrSelectCols = m_pTableDBDataGrid->GetSelectedCols();
	if( static_cast<int>(wxarrSelectCols.Count()) == m_pTableDBDataGrid->GetNumberCols())
		bSelectAll = true;

	// 우선 이 기능은 구현 안 한다. 너무 어렵다. Shift 와 마우스를 사용했을 때에는 필요하겠지만...
	//wxGridCellCoordsArray wxarrCellTopLeft = m_pTableDBDataGrid->GetSelectionBlockTopLeft();
	//wxGridCellCoords *topLeft = NULL;
	//if(!wxarrCellTopLeft.IsEmpty())
	//	topLeft = &(wxarrCellTopLeft.Item(0));

	//wxGridCellCoordsArray wxarrCellBottomRight = m_pTableDBDataGrid->GetSelectionBlockBottomRight();
	//wxGridCellCoords *bottomRight = NULL;
	//if(!wxarrCellBottomRight.IsEmpty())
	//	bottomRight = &(wxarrCellBottomRight.Item(0));


	// 현재 Row 를 중심으로 Select 할 때는 다시 Select 안 함
	if(bSelectAll
		||  (wxarrSelectCols.Count() > 0 && wxNOT_FOUND != wxarrSelectCols.Index(event.GetCol())) )
		;	// do nothing
	else
	{
		m_pTableDBDataGrid->ClearSelection();
		m_pTableDBDataGrid->SelectCol(event.GetCol());
		wxarrSelectCols.Add(event.GetCol());
	}

	mSelectRange.SetSelectMode(SelectRange_t::eCol);
	mSelectRange.SetSelect(wxarrSelectCols);

	wxMenu oMenu;
	oMenu.Append(eModifyCurrentCol, 	_T("Modify Current Col"));
	oMenu.Append(eDeleteCurrentCol, 	_T("Delete Current Col"));
	oMenu.Append(eAddCol,				_T("Add Col"));
	oMenu.Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&MultiViewerMain::OnPopupClick, NULL, this);
	m_pTableDBDataGrid->PopupMenu(&oMenu);
	return;

}


void MultiViewerMain::InitGrid(wxGrid* pGrid, bool a_bCleanCol /*= true */ )
{
	m_eGridState = eGridCommon; 
	int nCurrentNumberRow = pGrid->GetNumberRows();
	if(nCurrentNumberRow)
		pGrid->DeleteRows(0, nCurrentNumberRow);

	if(!a_bCleanCol)
		return;

	int nCurrentNumberCol = pGrid->GetNumberCols();
	if(nCurrentNumberCol)
		pGrid->DeleteCols(0, nCurrentNumberCol);
}

void MultiViewerMain::MoveEndGridRow(wxGrid* a_pGrid)
{
	int nViewX = 0, nViewY = 0;
	a_pGrid->GetViewStart(&nViewX, &nViewY);

	int nVisibleX = 0, nVisibleY = 0;
	a_pGrid->GetVirtualSize(&nVisibleX, &nVisibleY);

	a_pGrid->Scroll(nViewX ,nVisibleY );
}

void MultiViewerMain::SetCurPage(unsigned int a_nCurPage)
{
	m_DBDisplay.SetCurrentPage(a_nCurPage);
	mTableDBSlider->SetValue(m_DBDisplay.GetCurrentPage());

	wxString wxstrCurrentRow;
	wxstrCurrentRow.Printf(_T("%d - %d"), m_DBDisplay.GetCurrentStart(), m_DBDisplay.GetCurrentEnd() );
	m_pCurrentRowTextCtrl->SetValue(wxstrCurrentRow);

	Restore(&m_2DtableData, &m_vecDBColName, m_pTableDBDataGrid, m_DBDisplay.GetCurrentStart(), m_DBDisplay.GetCurrentEnd());
}

bool MultiViewerMain::AddTable()
{
	if(m_eProgramState == eStateInit)
		return false;

	MultiViewerTableNameDlg oTableNameDlg(this, m_pSQLReader, true);

	if( wxID_OK != oTableNameDlg.ShowModal() )
		return false;

	ST_TableInfo stTableInfo = oTableNameDlg.GetColList();
	if(m_pSQLReader->AddTable( &stTableInfo).IsFail())
		return false;
	InitSQLTableInfo();

	return true;
}


bool MultiViewerMain::DeleteTable()
{
	if(m_eProgramState == eStateInit)
		return false;
	
	MultiViewerTableNameSelectDlg oTableNameSelectDlg(this);
	vector<string> vecTableNames = m_pSQLReader->GetTableNames();

	unsigned  int nTableIndex = 0,  nCount = vecTableNames.size();


	for(nTableIndex = 0 ; nTableIndex < nCount ; nTableIndex++)
    {
    	std::string strTableName = vecTableNames[nTableIndex];
		wxString wxstrTableName = SQLUtil::str2wxstr(strTableName);
		oTableNameSelectDlg.AddTableName(wxstrTableName);
    }
	oTableNameSelectDlg.SetDefault();

	if( wxID_OK != oTableNameSelectDlg.ShowModal() )
		return false;

	int nSelect =  oTableNameSelectDlg.GetSelectTableNumber();
	DeleteTable(nSelect);

	return true;
}

bool MultiViewerMain::DeleteTable(int a_nTableNum)
{
	if(m_eProgramState == eStateInit)
		return false;

	if(m_pSQLReader->DeleteTable(a_nTableNum).IsFail())
		return false;
	InitSQLTableInfo();

	return true;
}

bool MultiViewerMain::ModifyTable()
{
	if(m_eProgramState == eStateInit)
		return false;

	MultiViewerTableNameDlg oTableNameDlg(this, m_pSQLReader, false);
	vector<string> vecTableNames = m_pSQLReader->GetTableNames();

	unsigned int nCount = vecTableNames.size();
	if(nCount == 0)
		return false;

	if( wxID_OK != oTableNameDlg.ShowModal() )
		return false;

	ST_TableInfo stTableInfo = oTableNameDlg.GetColList();
	if(m_pSQLReader->AddTable( &stTableInfo).IsFail())
		return false;
	InitSQLTableInfo();

	return true;
}

bool MultiViewerMain::ModifyTable(int a_nTableNum)
{
	if(m_eProgramState == eStateInit)
		return false;

	if(m_pSQLReader->DeleteTable(a_nTableNum).IsFail())
		return false;
	InitSQLTableInfo();

	return true;
}

bool MultiViewerMain::AddRow()
{
	if(m_eProgramState == eStateInit  || m_eProgramState == eStateFileOpened)
		return false;

	if(m_eGridState == eGridAdding)
		return false;

	m_eGridState = eGridAdding;


	wxArrayInt wxarrSelectRows = mSelectRange.GetSelect();
	m_nEditRowCount = MAX(wxarrSelectRows.Count() , 1 );

	m_pTableDBDataGrid->AppendRows(m_nEditRowCount + 2);  // nSelectRows for edit cell, 2 for button cell
	int nTotalRow = m_pTableDBDataGrid->GetNumberRows();
	int nTotalCol = m_pTableDBDataGrid->GetNumberCols();
	int nIndex = 0;
	wxColour oBackroundColour(255, 255, 0);
	DoAddModeAction(nTotalRow);

	wxGridCellAttr* attr = new wxGridCellAttr();
	attr->SetReadOnly(true);
	attr->SetRenderer(new ButtonRenderer(wxT("OK")));
	m_pTableDBDataGrid->SetRowAttr(nTotalRow - 2, attr);

	attr = new wxGridCellAttr();
	attr->SetReadOnly(true);
	attr->SetRenderer(new ButtonRenderer(wxT("Cancel")));
	m_pTableDBDataGrid->SetRowAttr(nTotalRow - 1, attr);  
	MoveEndGridRow(m_pTableDBDataGrid);

	return true;
}

void MultiViewerMain::DoAddModeAction(int nTotalRow)
{
	m_nEditRow = nTotalRow - m_nEditRowCount - 2;
	m_nAddRow = nTotalRow - 2;
	m_nCancelRow = nTotalRow - 1;

	int index = 0;
	for(index = 0 ; index < m_nEditRowCount ; index++)
	{
		m_pTableDBDataGrid->SetRowLabelValue(m_nEditRow + index, wxT("Edit"));
	}

	m_pTableDBDataGrid->SetRowLabelValue(nTotalRow - 3, wxT("Edit"));
	m_pTableDBDataGrid->SetRowLabelValue(nTotalRow - 2, wxT(""));
	m_pTableDBDataGrid->SetRowLabelValue(nTotalRow - 1, wxT(""));



}

bool MultiViewerMain::AddSQLRow()
{
	int nTotalCol = m_pTableDBDataGrid->GetNumberCols();
	Array2D<std::string>	stringValue2D(m_nEditRowCount, nTotalCol);


	int rowIndex = 0;
	int colIndex = 0;
	
	for(rowIndex = 0 ; rowIndex < m_nEditRowCount ; rowIndex++)
	{
		for(colIndex = 0 ; colIndex < nTotalCol ; colIndex++)
		{
			wxString wxstrValueString = m_pTableDBDataGrid->GetCellValue(m_nEditRow + rowIndex, colIndex);
			//stringValue2D.SetData(rowIndex, colIndex, "\"" + SQLUtil::wxstr2str(wxstrValueString) + "\"");
			stringValue2D.SetData(rowIndex, colIndex, SQLUtil::wxstr2str(wxstrValueString) );
		}
	}

	ST_DBReaderErr  stDBReaderErr = m_pSQLReader->AddRow(m_nSelectedTable, &stringValue2D);
	if(eDBReadereNotNullError == stDBReaderErr.GetErr()){
		ErrorDialog("table contain Not Null column");
		return false;
	}
	else if(stDBReaderErr.IsFail()){
		ErrorDialog("unknown error");
		return false;
	}

	bool bLastInsertRowOnly = true;
	if(m_nEditRowCount > 1)
		bLastInsertRowOnly = false;
	RefreshData(bLastInsertRowOnly);

//	int nTotalRow = m_pTableDBDataGrid->GetNumberRows();
//	m_pTableDBDataGrid->DeleteRows(nTotalRow - GridAddingModeRowCount, GridAddingModeRowCount + m_nEditRowCount);
	m_nEditRow = -1;
	m_nAddRow = -1;
	m_nCancelRow = -1;
	m_nEditRowCount = 0;

	
	return true;
}

void MultiViewerMain::RefreshData(bool a_bLastInsertRowOnly)
{
	VecArray2D<wxString>	o2DtableData;
	vector<wxString>		vecDBRowId;
	vector<wxString>		vecDBColName;

	if(a_bLastInsertRowOnly)
	{
		TableData oTableData(&o2DtableData, &vecDBRowId, &vecDBColName);
		if(m_pSQLReader->GetLastInsertRow( m_nSelectedTable, &oTableData).IsFail() )
			return;
		m_2DtableData.AppendRows(&o2DtableData);
		m_vecDBRowId.insert(m_vecDBRowId.end(), vecDBRowId.begin(), vecDBRowId.end());
		m_DBDisplay.AddRow();
	}
	else
	{
		Reload( m_DBDisplay.GetCurrentPage() );
	}

	int nTotalRow = m_2DtableData.GetRowSize();
	wxString wxstrTotal;
	wxstrTotal.Printf(_T("/ %d"), nTotalRow);
	m_pTotalStaticText->SetLabel(wxstrTotal);

	SetCurPage(m_DBDisplay.GetTotalPage());
	MoveEndGridRow(m_pTableDBDataGrid);
}


bool MultiViewerMain::ModifyRow(int a_nRow, int anCol, const char * a_szData)
{
	if(m_eProgramState == eStateInit)
		return false;

	string strRowID = SQLUtil::wxstr2str(m_vecDBRowId[a_nRow]);
	if(m_pSQLReader->ModifyRow(m_nSelectedTable, strRowID.c_str(), anCol, a_szData).IsFail())
		return false;
	
	m_2DtableData.SetData(a_nRow, anCol, SQLUtil::str2wxstr(a_szData));
	return true;
}

bool MultiViewerMain::DeleteRow()
{
	if(m_eProgramState == eStateInit)
		return false;

	wxArrayInt wxarrSelectRows = mSelectRange.GetSelect();
	if(wxarrSelectRows.IsEmpty())
		return false;

	unsigned int nIndex = 0;

	wxarrSelectRows.Sort(CmpFunc);
	vector<string> vecRowList;
	size_t realRowSize = m_vecDBRowId.size(); // eGridAdding 에 의해 추가된 row가 아닌 실제 데이터만 가진 row의 크기 
	for(nIndex = 0 ; nIndex < wxarrSelectRows.GetCount() ; nIndex++)
	{
		int nSelectRow = wxarrSelectRows.Item(nIndex) + m_DBDisplay.GetCurrentStart() - 1;
		
		if(nSelectRow >= realRowSize)
			continue;

		string strRowID = SQLUtil::wxstr2str(m_vecDBRowId[nSelectRow]);
		vecRowList.push_back(strRowID);
		//DeleteRow(wxarrSelectRows.Item(nIndex) - nIndex);
	}

	if(m_pSQLReader->DeleteRow( m_nSelectedTable, vecRowList).IsFail())
		return false;

	int nSkipCount = 0;
	// 삭제시 앞에 있는 Row가 사라지면 이를 고려해야 하므로 nIndex 만큼 빼주어야 한다.
	for(nIndex = 0 ; nIndex < wxarrSelectRows.GetCount() ; nIndex++)
	{
		int nSelectRowOnPage = wxarrSelectRows.Item(nIndex);

		if(nSelectRowOnPage >= realRowSize)
		{
			nSkipCount++;
			continue;
		}
		m_pTableDBDataGrid->DeleteRows(nSelectRowOnPage - nIndex );	// 테이블에서 삭제


		int nSelectRowOnTotal = wxarrSelectRows.Item(nIndex) + m_DBDisplay.GetCurrentStart() - 1;
		m_2DtableData.RemoveRows(nSelectRowOnTotal - nIndex);
		// Iterator 에서 + 를 먼저 할 경우, range를 벗어나는 부분을 가르키면서 assert 가 걸리는 현상 있음
		m_vecDBRowId.erase(m_vecDBRowId.begin() + (nSelectRowOnTotal - nIndex) );
	}

	m_DBDisplay.RemoveRow(wxarrSelectRows.GetCount() - nSkipCount);

	if(m_eGridState == eGridAdding)
	{
		int nTotalRow = m_pTableDBDataGrid->GetNumberRows();
		DoAddModeAction(nTotalRow);
	}

	//m_pTableDBDataGrid->DeleteRows(wxarrSelectRows.Item(0), wxarrSelectRows.GetCount());	// 테이블에서 삭제
	//m_vecDBRowId.erase(m_vecDBRowId.begin()+nSelectRow);
	return true;
}

bool MultiViewerMain::ModifyCol()
{
	wxArrayInt wxarrSelectRows = mSelectRange.GetSelect();
	if(1 != wxarrSelectRows.GetCount())
		return false;

	Trace(emTraceProgramProcess, "ModifyCol");


	int nSelectRow = wxarrSelectRows.Item(0);

	return ModifyCol(nSelectRow);
}
bool MultiViewerMain::ModifyCol(unsigned int a_nModiCol)
{
	if(m_eProgramState == eStateInit)
		return false;

	MultiViewerColDataDlg ColDataDlg(this, wxID_ANY, _T("Modify Column"));

	ColDataDlg.SetName(m_vecDBColName[a_nModiCol]);

	vector<ST_ColInfo> vecColInfo = m_pSQLReader->GetTableInfo(m_nSelectedTable, false);
	std::string strColDataType =  vecColInfo[a_nModiCol].strColDataType;
	if(vecColInfo[a_nModiCol].bPrimaryKey)
		strColDataType += " PRIMARY KEY";
	ColDataDlg.SetType( SQLUtil::str2wxstr(strColDataType) );

	if( wxID_OK != ColDataDlg.ShowModal() )
		return false;
	wxString wxstrName = ColDataDlg.GetName();
	std::string strName = SQLUtil::wxstr2str(wxstrName);

	wxString wxstrType = ColDataDlg.GetType();
	std::string strType = SQLUtil::wxstr2str(wxstrType);

	if(m_pSQLReader->ModifyCol(m_nSelectedTable, a_nModiCol, strName.c_str(), strType.c_str()) .IsFail())
		return false;

	m_vecDBColName[a_nModiCol] =  wxstrName;

	InitSQLTableInfo();
	//SetColHeader(a_pwxGrid, a_pColName );
	SetColHeader(m_pTableDBDataGrid, &m_vecDBColName);
	//SetColHeader(wxGrid* a_pwxGrid, vector<wxString>* a_pColName );


	return true;
}

bool MultiViewerMain::DeleteCol()
{
	wxArrayInt wxarrSelectRows = mSelectRange.GetSelect();
	if(1 != wxarrSelectRows.GetCount())
		return false;

	Trace(emTraceProgramProcess, "DeleteCol");


	int nSelectCol = wxarrSelectRows.Item(0);

	if( !DeleteCol(nSelectCol) )
		return false;
	m_2DtableData.RemoveCols(nSelectCol);
	m_pTableDBDataGrid->DeleteCols(nSelectCol);
	InitSQLTableInfo();

	return true;
}

bool MultiViewerMain::DeleteCol(unsigned int a_nDelCol)
{
	if(m_eProgramState == eStateInit)
		return false;

	m_pSQLReader->DeleteCol(m_nSelectedTable, a_nDelCol).IsSucuccess();
	return true;
}



bool MultiViewerMain::AddCol()
{
	if(m_eProgramState == eStateInit)
		return false;

	MultiViewerColDataDlg ColDataDlg(this, wxID_ANY, _T("Add Column"));

	if( wxID_OK != ColDataDlg.ShowModal() )
		return false;
	wxString wxstrName = ColDataDlg.GetName();
	std::string strName = SQLUtil::wxstr2str(wxstrName);

	wxString wxstrType = ColDataDlg.GetType();
	std::string strType = SQLUtil::wxstr2str(wxstrType);

	if(m_pSQLReader->AddCol(m_nSelectedTable, strName.c_str(), strType.c_str()) .IsFail())
		return false;

	m_2DtableData.InsertCols(0);
	m_pTableDBDataGrid->InsertCols(0);
	InitSQLTableInfo();


	return true;
}


bool MultiViewerMain::Undo()
{
	if(m_eProgramState == eStateInit)
		return false;

	if(m_pSQLReader->Undo().IsFail())
		return false;

	Reload();
	return true;
}

bool MultiViewerMain::Reload(int a_nPage)
{
	m_eProgramState = eStateTableSelected;

	m_2DtableData.ClearAll();

	TableData oTableData(&m_2DtableData, &m_vecDBRowId, &m_vecDBColName);
	m_pSQLReader->GetAllRow(m_nSelectedTable, &oTableData);

	m_pTableDBDataGrid->AppendCols(oTableData.GetCol());

	int nTotalRow = oTableData.GetRow();
	wxString wxstrTotal;
	wxstrTotal.Printf(_T("/ %d"), nTotalRow);
	m_pTotalStaticText->SetLabel(wxstrTotal);

	wxString wxstrCurrentRow;
	wxstrCurrentRow.Printf(_T("%d"), 1);
	m_pCurrentRowTextCtrl->SetValue(wxstrCurrentRow);

	m_DBDisplay.SetTotal(nTotalRow);
	mTableDBSlider->SetPageSize(1);
	mTableDBSlider->SetRange(1, m_DBDisplay.GetTotalPage());
	mTableDBSlider->SetValue(a_nPage);

	SetCurPage(1);
	return true;
}

bool MultiViewerMain::Refresh()
{
	InitSQLTableInfo();
	//mTableDBSlider->SetValue(m_DBDisplay.GetCurrentPage());
	SetCurPage(m_DBDisplay.GetCurrentPage());
	return true;
}

bool MultiViewerMain::DeleteRow(unsigned int a_nDelRow)
{
	if(m_eProgramState == eStateInit)
		return false;

	// 실제 데이터에서 삭제
	int nSelectRow = a_nDelRow + m_DBDisplay.GetCurrentStart() - 1;
	wxString wxsRowID = m_vecDBRowId[nSelectRow];
	std::string strROWID = SQLUtil::wxstr2str(wxsRowID);
	if(m_pSQLReader->DeleteRow( m_nSelectedTable, strROWID.c_str()).IsFail())
		return false;

	m_2DtableData.RemoveRows(nSelectRow);
	m_pTableDBDataGrid->DeleteRows(a_nDelRow);	// 테이블에서 삭제
 	m_vecDBRowId.erase(m_vecDBRowId.begin()+nSelectRow);

	m_DBDisplay.RemoveRow();
	return true;
}


void MultiViewerMain::OnTableDBStartButtonClick( wxCommandEvent&  )
{
	if( m_DBDisplay.GetCurrentPage() == 1 )
		return;

	SetCurPage(1);

}

void MultiViewerMain::OnTableDBEndButtonClick( wxCommandEvent&  )
{
	if( m_DBDisplay.GetCurrentPage()  ==  m_DBDisplay.GetTotalPage())
		return;

	SetCurPage(m_DBDisplay.GetTotalPage());
}



void MultiViewerMain::OnTableDBSliderUp( wxScrollEvent&  )
{
	if( m_DBDisplay.GetPagePerRow() <= 1 )
		return;

	SetCurPage(m_DBDisplay.PageMove(-1));

}

void MultiViewerMain::OnTableDBSliderDown( wxScrollEvent&  )
{
	if( m_DBDisplay.GetTotalPage() <=  m_DBDisplay.GetCurrentPage())
		return;

	SetCurPage(m_DBDisplay.PageMove(+1));


}

void MultiViewerMain::OnTableDBSliderRelease( wxScrollEvent& event )
{
	SetCurPage(mTableDBSlider->GetValue());
	event.Skip();
}


void MultiViewerMain::OnCurrentRowTextCtrlKeyUp( wxKeyEvent& event )
{
	switch(event.GetKeyCode())
	{
	case WXK_RETURN:
	case WXK_NUMPAD_ENTER:
		break;
	}

}

void MultiViewerMain::OnQueryButtonClick( wxCommandEvent&  )
{
	if(m_eProgramState == eStateInit)
		return;

	wxString wxsQuery = m_pQueryTextCtrl->GetValue();
	std::string strQuery = SQLUtil::wxstr2str(wxsQuery);
	TableData queryTableData(&m_2DQuerytableData, NULL, &m_2DQueryDBColName);;

	m_2DQuerytableData.ClearAll();
	if(!m_pSQLReader->GetTableWithQuery(strQuery, &queryTableData))
		return;
	m_pHistoryCombo->Insert(wxsQuery, 0);
	Restore(&m_2DQuerytableData,  &m_2DQueryDBColName,m_pQueryGrid, 1, m_2DQuerytableData.GetRowSize()  );
}

void MultiViewerMain::OnHistoryQueryLoad( wxCommandEvent& event )
{
	
}

void MultiViewerMain::SetColHeader(wxGrid* a_pwxGrid, vector<wxString>* a_pColName )
{
	unsigned int nCol = 0;
	for(nCol=0; nCol< a_pColName->size(); nCol++ )
	{
		a_pwxGrid->SetColLabelValue(nCol, a_pColName->at(nCol) );

	}
}

void MultiViewerMain::Restore(VecArray2D<wxString>* a_p2DTableData, vector<wxString>* a_pColName, wxGrid* a_pwxGrid ,int a_nStartRow, int a_nEndRow)
{
	int nStartRow = a_nStartRow;
	InitGrid(a_pwxGrid, true);
	unsigned int nRowTotal = a_nEndRow - a_nStartRow + 1;
	unsigned int nColTotal = a_p2DTableData->GetColSize();

	a_pwxGrid->AppendRows(nRowTotal);
	a_pwxGrid->AppendCols(nColTotal);

	SetColHeader(a_pwxGrid, a_pColName );

	unsigned int nCol = 0;

	unsigned int nRow = 0;
	for(nRow=0; nRow < nRowTotal ; nRow++ , nStartRow++)
	{

		for(nCol = 0; nCol < nColTotal ; nCol++)
		{
			wxString wstrData;
			wstrData = a_p2DTableData->GetData(nStartRow - 1, nCol);
			a_pwxGrid->SetCellValue(nRow, nCol, wstrData);
		}
		wxString wxstrRowNumber;
		wxstrRowNumber.Printf(_T("%d"), nStartRow);
    	a_pwxGrid->SetRowLabelValue(nRow , wxstrRowNumber);

	}
}


void MultiViewerMain::InitSQLTableInfo()
{
	if(m_eProgramState == eStateInit)
		return;

	m_pSQLReader->GetMainTable();
	vector<string> vecTableNames = m_pSQLReader->GetTableNames();


	////////  기존 내용들을 지우고 초기화 하는 부분
	m_pTableNameChoice->Clear();
	m_pTableInfoTreeCtrl->DeleteAllItems();

    unsigned  int nTableIndex = 0,  nCount = vecTableNames.size();
	unsigned int nColIndex = 0;



	//////// SQL Info에 따라서 Tree Item 을 추가
	wxString wxstrRootID = _T("");
	wxTreeItemId pRootItemID =  m_pTableInfoTreeCtrl->AddRoot(wxstrRootID);
	for(nTableIndex = 0 ; nTableIndex < nCount ; nTableIndex++)
    {
    	std::string strTableName = vecTableNames[nTableIndex];
		wxString wxstrTableName = SQLUtil::str2wxstr(strTableName);

		m_pTableNameChoice->AppendString(wxstrTableName);
		wxTreeItemId pItemID = m_pTableInfoTreeCtrl->AppendItem(pRootItemID, wxstrTableName);
		vector<ST_ColInfo> vecColInfo = m_pSQLReader->GetTableInfo(nTableIndex, true);

		for(nColIndex = 0; nColIndex < vecColInfo.size(); nColIndex++)
		{
			ST_ColInfo stColInfo = vecColInfo[nColIndex];
			wxString wxstrColName;
			if(stColInfo.bPrimaryKey)
				wxstrColName = SQLUtil::str2wxstr(stColInfo.strColName + " : " +"PrimearyKey " + stColInfo.strColDataType);
			else
				wxstrColName = SQLUtil::str2wxstr(stColInfo.strColName + " : " + stColInfo.strColDataType);
			
			if(stColInfo.bNotNull)
				wxstrColName += _T(" , Not NULL");

			if(stColInfo.strDefault != "")
			{
				wxstrColName +=  _T(" , default (");
				wxstrColName +=  SQLUtil::str2wxstr(stColInfo.strDefault);
				wxstrColName +=  _T(")");
			}
			m_pTableInfoTreeCtrl->AppendItem(pItemID, wxstrColName);

		}

    }
}

bool MultiViewerMain::ConfirmNewDialog()
{
	if(m_pSQLReader)
	{
		wxMessageDialog msgDialog(this, SQLUtil::str2wxstr("Are you want to close current file or connection?"), SQLUtil::str2wxstr("caption"), wxYES_NO | wxICON_QUESTION);
		if(wxID_NO == msgDialog.ShowModal())
			return false;
		delete m_pSQLReader;
	}
	m_eProgramState = eStateInit;
	return true;
}

void MultiViewerMain::ErrorDialog(const char* message)
{
	wxMessageDialog msgDialog(this, SQLUtil::str2wxstr(message), SQLUtil::str2wxstr("Err"), wxOK  | wxICON_ERROR );
	msgDialog.ShowModal();
}

TableData::TableData(VecArray2D<wxString>* a_p2DtableData, vector<wxString>* a_vecDBRowId, vector<wxString>* a_vecDBColName ) : ITableData()
{
	m_nCol = m_nRow = 0;
	m_p2DTableData = a_p2DtableData;
	m_pVecDBRowId = a_vecDBRowId;
	m_pVecDBColName = a_vecDBColName;
}

TableData::~TableData()
{

}

void TableData::SetColNum(int a_nRowCount)
{
	m_nCol = a_nRowCount;
	m_pVecDBColName->resize(a_nRowCount);
	m_p2DTableData->SetCol(a_nRowCount);
}

void TableData::AddRow()
{
	m_nRow++;
	m_p2DTableData->AppendRows();
	if(m_pVecDBRowId)
		m_pVecDBRowId->resize(m_nRow);
}

void TableData::SetData(int  a_nRow, int a_nCol, const char *a_szData)
{

	wxString wxsData(a_szData, wxConvUTF8);
	m_p2DTableData->SetData(a_nRow, a_nCol, wxsData);
}

void TableData::SetRowID(int a_nRow, const char *a_szData)
{
	if(!m_pVecDBRowId)
		return;
	wxString wxsRowID(a_szData, wxConvUTF8);
	(*m_pVecDBRowId)[a_nRow] = wxsRowID;
}

void TableData::SetColName(int a_nCol, const char *a_szData)
{
	wxString wxsColname(a_szData, wxConvUTF8);
	(*m_pVecDBColName)[a_nCol] = wxsColname;
}

