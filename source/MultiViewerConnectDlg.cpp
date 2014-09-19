#include "MultiViewerConnectDlg.h"
#include "SQLUtil.h"

MultiViewerConnectDlg::MultiViewerConnectDlg( wxWindow* parent )
:
ConnectDlg( parent )
{
	
}

void MultiViewerConnectDlg::OnCancelButtonClick( wxCommandEvent& event )
{
	EndModal(wxID_CANCEL);
}

void MultiViewerConnectDlg::OnOKButtonClick( wxCommandEvent& event )
{
	wxString wxstrHost = GetHost();
	if(wxstrHost.IsEmpty())
	{
		SQLUtil::AlertDlg(_T("No Host"));
		return;
	}

	//wxString wxstrPort = GetPort();
	//if(wxstrPort.IsEmpty())
	//{
	//	SQLUtil::AlertDlg(_T("No Port"));
	//	return;
	//}

	//wxString wxstrName = GetName();
	//if(wxstrName.IsEmpty())
	//{
	//	SQLUtil::AlertDlg(_T("No ID"));
	//	return;
	//}

	//wxString wxstrPassword = GetPassword();
	//if(wxstrPassword.IsEmpty())
	//{
	//	SQLUtil::AlertDlg(_T("No Password"));
	//	return;
	//}

	EndModal(wxID_OK);
}


void MultiViewerConnectDlg::SetData(const char* a_pHost, const char* a_pPort,  const char* a_pDBName, const char* a_pID, const char* a_pPassword)
{
	if(a_pHost)
		m_pConnectHost->SetValue(SQLUtil::str2wxstr(a_pHost));

	if(a_pPort)
		m_pConnectPort->SetValue(SQLUtil::str2wxstr(a_pPort));

	if(a_pDBName)
		m_pDBName->SetValue(SQLUtil::str2wxstr(a_pDBName));

	if(a_pID)
		m_pConnectID->SetValue(SQLUtil::str2wxstr(a_pID));

	if(a_pPassword)
		m_pConnectPassword->SetValue(SQLUtil::str2wxstr(a_pPassword));
}

void MultiViewerConnectDlg::AddConnectType(const char* a_strConnectType)
{
	m_pConnectType->Append(SQLUtil::str2wxstr(a_strConnectType) );
	m_pConnectType->Select(0);
}

wxString MultiViewerConnectDlg::GetName()
{
	return m_pConnectName->GetValue();
}

wxString MultiViewerConnectDlg::GetHost()
{
	return m_pConnectHost->GetValue();
}

wxString MultiViewerConnectDlg::GetPort()
{
	return m_pConnectPort->GetValue();
}

wxString MultiViewerConnectDlg::GetDBName()
{
	return m_pDBName->GetValue();
}

wxString MultiViewerConnectDlg::GetID()
{
	return m_pConnectID->GetValue();
}

wxString MultiViewerConnectDlg::GetPassword()
{
	return m_pConnectPassword->GetValue();
}

wxString MultiViewerConnectDlg::GetType()
{
	int nSelect = m_pConnectType->GetCurrentSelection();
	return m_pConnectType->GetString(nSelect);
}
