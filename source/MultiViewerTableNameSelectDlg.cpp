#include "MultiViewerTableNameSelectDlg.h"

MultiViewerTableNameSelectDlg::MultiViewerTableNameSelectDlg( wxWindow* parent )
:
TableNameSelectDlg( parent )
{

}

void MultiViewerTableNameSelectDlg::OnCancelButtonClick( wxCommandEvent&  /* event */ )
{
	EndModal(wxID_CANCEL);
}

void MultiViewerTableNameSelectDlg::OnOKButtonClick( wxCommandEvent&  /* event */)
{
	EndModal(wxID_OK);
}

void MultiViewerTableNameSelectDlg::AddTableName(wxString a_wxStrTableName)
{
	m_pTableChoice->Append(a_wxStrTableName);
}

void MultiViewerTableNameSelectDlg::SetDefault()
{
	m_pTableChoice->SetSelection(0);
}

int MultiViewerTableNameSelectDlg::GetSelectTableNumber()
{
	return m_pTableChoice->GetCurrentSelection();
}
