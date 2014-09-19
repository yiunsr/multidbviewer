#include "MultiViewerColDataDlg.h"

MultiViewerColDataDlg::MultiViewerColDataDlg( wxWindow* parent )
:
ColDataDlg( parent )
{

}

MultiViewerColDataDlg::MultiViewerColDataDlg( wxWindow* parent, wxWindowID id , const wxString& title )
:
ColDataDlg( parent, id, title )
{

}

void MultiViewerColDataDlg::OnCancelButtonClick( wxCommandEvent&  /* event */ )
{
	EndModal(wxID_CANCEL);
}

void MultiViewerColDataDlg::OnOKButtonClick( wxCommandEvent&  /* event */)
{
	EndModal(wxID_OK);
}
