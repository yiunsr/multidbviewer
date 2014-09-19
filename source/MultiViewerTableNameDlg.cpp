#include "MultiViewerTableNameDlg.h"
#include "MultiViewerColDataDlg.h"
#include "SQLUtil.h"
#include "Config.h"


#define COL_NAME_INDEX 0
#define COL_TYPE_INDEX 1

#define COL_OLD_NAME_INDEX 0
#define COL_OLD_TYPE_INDEX 1
#define COL_NEW_NAME_INDEX 2
#define COL_NEW_TYPE_INDEX 3

//#define DISABLE_BG_COLOR (*wxLIGHT_GREY)
#define DISABLE_BG_COLOR ( wxColour(0xC0, 0xC0, 0xC0) )
#define ENABLE_BG_COLOR ( wxColour(0xFF, 0xFF, 0xFF) )


const wxString TYPE_CHOICES[] =
{
    _T("INTEGER"),
    _T("REAL"),
    _T("BLOB"),
	_T("INTEGER PRIMARY KEY"),
};

MultiViewerTableNameDlg::MultiViewerTableNameDlg( wxWindow* parent, SQLReaderBase* pSQLReader, bool bCreateMode /* = true*/ )
:TableNameDlg( parent )
{
	m_bGridRangeSelect = false;
	m_bCreateMode = bCreateMode;
	m_pSQLReader = pSQLReader;
	m_nOldSelect = -1;
	//m_pCancelRender = new CancelCellRender();
	if(bCreateMode){
		m_pGrid = m_pCreateGrid;
		m_staticTextModifyTable->Show(false);
		m_pChoiceModifyTable->Show(false);
		m_pCreateGrid->Show(true);
		m_pEditGrid->Show(false);
		m_pSTTableName->SetLabel(_T(TABLE_NAME_DLG_ST_TABLE_NAME));
	}
	else{
		m_pGrid = m_pEditGrid;
		m_staticTextModifyTable->Show(true);
		m_pChoiceModifyTable->Show(true);
		m_pCreateGrid->Show(false);
		m_pEditGrid->Show(true);
		m_pRecallBtn->Show(true);
		m_pRecallBtn->Enable(false);

		vector<string> vecTableNames = m_pSQLReader->GetTableNames();
		unsigned  int nTableIndex = 0,  nCount = vecTableNames.size();

		for(nTableIndex = 0 ; nTableIndex < nCount ; nTableIndex++)
		{
    		std::string strTableName = vecTableNames[nTableIndex];
			wxString wxstrTableName = SQLUtil::str2wxstr(strTableName);
			m_pChoiceModifyTable->Append(wxstrTableName);
		}
		m_pSTTableName->SetLabel(_T(TABLE_NAME_DLG_ST_NEW_TABLE_NAME));

	}
}

MultiViewerTableNameDlg::~MultiViewerTableNameDlg()
{
	//delete m_pCancelRender;
}

void MultiViewerTableNameDlg::OnCancelButtonClick( wxCommandEvent&  /* event */ )
{
	EndModal(wxID_CANCEL);
}

void MultiViewerTableNameDlg::OnOKButtonClick( wxCommandEvent&  /* event */)
{
	wxString wxstrTableName = GetTableName();
	if(wxstrTableName.IsEmpty())
	{
		SQLUtil::AlertDlg(_T("No Table Name"));
		return;
	}

	//int nColCount = m_pGrid->GetNumberCols();
	//int nColIndex = 0;
	int nRowCount = m_pGrid->GetNumberRows();
	int nRowIndex = 0;
	for( nRowIndex = 0; nRowIndex < nRowCount ; nRowIndex++)
	{
		 wxString wxstrValue;
		 wxstrValue = m_pGrid->GetCellValue(nRowIndex, COL_NAME_INDEX);
		 if (wxstrValue.length() == 0 )
		 {
			 SQLUtil::AlertDlg(_T("Empty column Name"));
			return;
		 }
		 wxstrValue = m_pGrid->GetCellValue(nRowIndex, COL_TYPE_INDEX);
		 if (wxstrValue.length() == 0 )
		 {
			 SQLUtil::AlertDlg(_T("Empty column Type"));
			return;
		 }
		 
	}

	EndModal(wxID_OK);
}

wxString MultiViewerTableNameDlg::GetTableName()
{
	return m_pTableNameTextCtrl->GetValue();
}

ST_TableInfo MultiViewerTableNameDlg::GetColList()
{
	ST_TableInfo stTableInfo;
	int nRowCount = m_pGrid->GetNumberRows();
	if( nRowCount == 0 )
		return stTableInfo;

	stTableInfo.nTotalCol = nRowCount;
	stTableInfo.strTableName = SQLUtil::wxstr2str(m_pTableNameTextCtrl->GetValue());
	int nIndex = 0;
	for( nIndex = 0; nIndex < nRowCount ; nIndex++)
	{
		ST_ColInfo stColInfo;
		stColInfo.strColName = SQLUtil::wxstr2str(m_pGrid->GetCellValue(nIndex, COL_NAME_INDEX));
		stColInfo.strColDataType = SQLUtil::wxstr2str(m_pGrid->GetCellValue(nIndex, COL_TYPE_INDEX));
		stTableInfo.arrColInfo.push_back(stColInfo);
	}
	return stTableInfo;

}




void MultiViewerTableNameDlg::OnDeleteBtnClick( wxCommandEvent& )
{
	wxArrayInt wxArrIntSelectRow = m_pGrid->GetSelectedRows();
	size_t nCount = wxArrIntSelectRow.Count();
	if(nCount ==0)
		return;
	wxArrIntSelectRow.Sort(ReverseCmpFunc);
	size_t nIndex = 0;
	if(m_bCreateMode){
		for( nIndex = 0 ; nIndex < nCount ; nIndex++)
		{
			int nRowIndex = wxArrIntSelectRow.Item(nIndex);
			m_pGrid->DeleteRows(nRowIndex);
		}
		return;
	}
	
	int nRowIndex = wxArrIntSelectRow.Item(0);
	if(m_pGrid->GetCellBackgroundColour(nRowIndex, COL_OLD_NAME_INDEX) == DISABLE_BG_COLOR)
		return; 


	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_OLD_NAME_INDEX, DISABLE_BG_COLOR);
	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_OLD_TYPE_INDEX, DISABLE_BG_COLOR);
	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_NEW_NAME_INDEX, DISABLE_BG_COLOR);
	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_NEW_TYPE_INDEX, DISABLE_BG_COLOR);

	m_pGrid->SetReadOnly(nRowIndex, COL_NEW_NAME_INDEX, true);
	m_pGrid->SetReadOnly(nRowIndex, COL_NEW_TYPE_INDEX, true);

	m_pGrid->Refresh();

	m_pDeleteBtn->Enable(false);
	m_pRecallBtn->Enable(true);
}

void MultiViewerTableNameDlg::OnAddBtnClick( wxCommandEvent& )
{
	MultiViewerColDataDlg oColDataDlg(this, wxID_ANY, _T("Add Column"));

	if( wxID_OK != oColDataDlg.ShowModal() )
		return;

	wxString wxStrName = oColDataDlg.GetName();
	wxString wxStrType = oColDataDlg.GetType();

	m_pGrid->AppendRows();
	int nLastRowIndex = m_pGrid->GetNumberRows() - 1;

	m_pGrid->SetCellValue(nLastRowIndex, COL_NAME_INDEX, wxStrName);
	m_pGrid->SetCellValue(nLastRowIndex, COL_TYPE_INDEX, wxStrType);

    m_pGrid->SetCellEditor(nLastRowIndex, COL_TYPE_INDEX, new wxGridCellChoiceEditor(WXSIZEOF(TYPE_CHOICES), TYPE_CHOICES, true));

}

void MultiViewerTableNameDlg::OnRecallBtnClick( wxCommandEvent& event )
{
	wxArrayInt wxArrIntSelectRow = m_pGrid->GetSelectedRows();
	size_t nCount = wxArrIntSelectRow.Count();
	if(nCount ==0)
		return;
	wxArrIntSelectRow.Sort(ReverseCmpFunc);
	size_t nIndex = 0;
	if(m_bCreateMode)
		return;
	
	int nRowIndex = wxArrIntSelectRow.Item(0);
	// already disable check
	if(m_pGrid->GetCellBackgroundColour(nRowIndex, COL_OLD_NAME_INDEX) != DISABLE_BG_COLOR)
		return; 

	m_pGrid->SetReadOnly(nRowIndex, COL_NEW_NAME_INDEX, false);
	m_pGrid->SetReadOnly(nRowIndex, COL_NEW_TYPE_INDEX, false);

	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_OLD_NAME_INDEX, ENABLE_BG_COLOR);
	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_OLD_TYPE_INDEX, ENABLE_BG_COLOR);
	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_NEW_NAME_INDEX, ENABLE_BG_COLOR);
	m_pGrid->SetCellBackgroundColour(nRowIndex, COL_NEW_TYPE_INDEX, ENABLE_BG_COLOR);

	m_pGrid->Refresh();

	m_pDeleteBtn->Enable(true);
	m_pRecallBtn->Enable(false);
}

void MultiViewerTableNameDlg::OnUpButtonClick( wxCommandEvent& )
{
	wxArrayInt arrSelectRow = m_pGrid->GetSelectedRows();
	if(arrSelectRow.Count() != 1)
		return;
	int selectRow = arrSelectRow.front();
	if(selectRow == 0 )
		return;
	int nIndex = 0;
	for(nIndex = 0 ; nIndex < m_pGrid->GetNumberCols() ; nIndex++)
	{
		wxString wxstrSelectValue = m_pGrid->GetCellValue(selectRow, nIndex);
		wxString wxstrUpRowValue = m_pGrid->GetCellValue(selectRow - 1, nIndex);
		m_pGrid->SetCellValue(selectRow - 1, nIndex , wxstrSelectValue);
		m_pGrid->SetCellValue(selectRow , nIndex , wxstrUpRowValue);

		wxColour selectBGColor = m_pGrid->GetCellBackgroundColour(selectRow, nIndex);
		wxColour upRowBGColor = m_pGrid->GetCellBackgroundColour(selectRow - 1, nIndex);
		m_pGrid->SetCellBackgroundColour(selectRow - 1, nIndex , selectBGColor);
		m_pGrid->SetCellBackgroundColour(selectRow , nIndex , upRowBGColor);

		bool bSelectReadOnly = m_pGrid->IsReadOnly(selectRow, nIndex);
		bool bUpReadOnly = m_pGrid->IsReadOnly(selectRow - 1, nIndex);
		m_pGrid->SetReadOnly(selectRow - 1, nIndex, bSelectReadOnly);
		m_pGrid->SetReadOnly(selectRow, nIndex, bUpReadOnly);


	}
	m_pGrid->SelectRow(selectRow - 1,false);


}

void MultiViewerTableNameDlg::OnDownButtonClick( wxCommandEvent&  )
{
	wxArrayInt arrSelectRow = m_pGrid->GetSelectedRows();
	if(arrSelectRow.Count() != 1)
		return;
	int selectRow = arrSelectRow.front();
	if(selectRow == m_pGrid->GetNumberRows() - 1)
		return;
	int nIndex = 0;
	for(nIndex = 0 ; nIndex < m_pGrid->GetNumberCols() ; nIndex++)
	{
		wxString wxstrSelectValue = m_pGrid->GetCellValue(selectRow, nIndex);
		wxString wxstrDownRowValue = m_pGrid->GetCellValue(selectRow + 1, nIndex);
		m_pGrid->SetCellValue(selectRow + 1, nIndex , wxstrSelectValue);
		m_pGrid->SetCellValue(selectRow , nIndex , wxstrDownRowValue);

		wxColour selectBGClor = m_pGrid->GetCellBackgroundColour(selectRow, nIndex);
		wxColour downRowBGColor = m_pGrid->GetCellBackgroundColour(selectRow + 1, nIndex);
		m_pGrid->SetCellBackgroundColour(selectRow + 1, nIndex , selectBGClor);
		m_pGrid->SetCellBackgroundColour(selectRow , nIndex , downRowBGColor);

		bool bSelectReadOnly = m_pGrid->IsReadOnly(selectRow, nIndex);
		bool bDownReadOnly = m_pGrid->IsReadOnly(selectRow + 1, nIndex);
		m_pGrid->SetReadOnly(selectRow + 1, nIndex, bSelectReadOnly);
		m_pGrid->SetReadOnly(selectRow, nIndex, bDownReadOnly);
	}
	m_pGrid->SelectRow(selectRow + 1,false);
}


void MultiViewerTableNameDlg::OnGridCmdRangeSelect( wxGridRangeSelectEvent& event )
{
	//if(!event.Selecting())
	//	return;

	//// grid 에 대한 SelectRow 동작시 OnGridRangeSelect 이벤트가 들어온다. 
	//// 순환 호출하는 것에 대한 동작을 방지해야 한다. 
	//if(m_bGridRangeSelect)
	//	return;
	//m_bGridRangeSelect = true;
	////int nTopRow = event.GetTopRow();
	//int nBotton = event.GetBottomRow();
	////int nIndex = 0;

	//m_pGrid->ClearSelection();
	//m_pGrid->SelectRow(nBotton, true);

	//// enable up, down button
	//if(m_pGrid->GetRows() >= 2 ){
	//	m_pUpBtn->Enable();
	//	m_pDownBtn->Enable();
	//}
	//else{
	//	m_pUpBtn->Enable(false);
	//	m_pDownBtn->Enable(false);
	//}

	//m_bGridRangeSelect = false;

}

void MultiViewerTableNameDlg::OnGridSelectCell( wxGridEvent& event )
{
	m_pUpBtn->Enable(false);
	m_pDownBtn->Enable(false);
	//TableNameDlg::OnGridSelectCell(event);
	event.Skip();
}

void MultiViewerTableNameDlg::OnGridLabelLeftClick( wxGridEvent& event )
{
	m_pGrid->ClearSelection();
	int nRow = event.GetRow();
	int nCol = event.GetCol();
	if(nRow == -1 || nCol != -1){
		m_pUpBtn->Enable(false);
		m_pDownBtn->Enable(false);
		return;
	}
	m_pGrid->SelectRow(nRow);
	m_pUpBtn->Enable();
	m_pDownBtn->Enable();


	//if( m_pGrid->GetCellRenderer(nRow, COL_OLD_NAME_INDEX) == m_pCancelRender){
	if(m_pGrid->GetCellBackgroundColour(nRow, COL_OLD_NAME_INDEX) == DISABLE_BG_COLOR){
		m_pDeleteBtn->Enable(false);
		m_pRecallBtn->Enable(true);
	}
	else{
		m_pDeleteBtn->Enable(true);
		m_pRecallBtn->Enable(false);

	}
}

void MultiViewerTableNameDlg::OnTableModifyChoice( wxCommandEvent& )
{
	int nSelect = m_pChoiceModifyTable->GetCurrentSelection();
	if(m_nOldSelect == nSelect)
		return;
	m_nOldSelect = nSelect;

	vector<ST_ColInfo> vecColInfo = m_pSQLReader->GetTableInfo(nSelect, true);
	unsigned int nColIndex = 0;
	
	m_pTableNameTextCtrl->SetLabel( m_pChoiceModifyTable->GetString(nSelect));
	if(m_pGrid->GetNumberRows() >0)
		m_pGrid->DeleteRows(0, m_pGrid->GetNumberRows());
	m_pGrid->AppendRows(vecColInfo.size());
	for(nColIndex = 0; nColIndex < vecColInfo.size(); nColIndex++)
	{
		std::string strColDataType =  vecColInfo[nColIndex].strColDataType;
		wxString wxstrColName = SQLUtil::str2wxstr( vecColInfo[nColIndex].strColName );
		if(vecColInfo[nColIndex].bPrimaryKey)
			strColDataType += " PRIMARY KEY";
		wxString wxstrColType = SQLUtil::str2wxstr(strColDataType);
		m_pGrid->SetCellValue(nColIndex , COL_OLD_NAME_INDEX , wxstrColName);
		m_pGrid->SetReadOnly(nColIndex , COL_OLD_NAME_INDEX);
		m_pGrid->SetCellValue(nColIndex , COL_OLD_TYPE_INDEX , wxstrColType);
		m_pGrid->SetReadOnly(nColIndex , COL_OLD_TYPE_INDEX);
		m_pGrid->SetCellEditor(nColIndex, COL_NEW_TYPE_INDEX, new wxGridCellChoiceEditor(WXSIZEOF(TYPE_CHOICES), TYPE_CHOICES, true));
	}

}