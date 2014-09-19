#include "SQLUtil.h"
#include <wx/msgdlg.h>


std::string SQLUtil::wxstr2str(wxString a_wxStr)
{
	return std::string  (a_wxStr.mb_str(wxConvUTF8));
}


wxString SQLUtil::str2wxstr(std::string a_Str)
{
	return wxString(a_Str.c_str(), wxConvUTF8);
}

void SQLUtil::AlertDlg(wxString a_wxStr)
{
	wxMessageDialog msgDlg(NULL, a_wxStr);
	msgDlg.ShowModal();
}