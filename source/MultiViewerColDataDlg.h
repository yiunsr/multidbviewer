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
#ifndef __MultiViewerColDataDlg__
#define __MultiViewerColDataDlg__

/**
@file
Subclass of ColDataDlg, which is generated by wxFormBuilder.
*/
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

#include "MainFrame.h"

/** Implementing ColDataDlg */
class MultiViewerColDataDlg : public ColDataDlg
{
public:
	/** Constructor */
	MultiViewerColDataDlg( wxWindow* parent );
	MultiViewerColDataDlg( wxWindow* parent, wxWindowID id , const wxString& title = wxT("Edit Column Info") );

	virtual void OnCancelButtonClick( wxCommandEvent& event );
	virtual void OnOKButtonClick( wxCommandEvent& event );

	wxString GetName(){	return m_pNameTextCtrl->GetValue();	}
	wxString GetType(){	return m_pTypeComboBox->GetValue();	}

	void SetName(wxString a_wstrName){	m_pNameTextCtrl->SetValue(a_wstrName);	}
	void SetType(wxString a_wstrType){	m_pTypeComboBox->SetValue(a_wstrType);	}


};

#endif // __MultiViewerColDataDlg__
