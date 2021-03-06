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
#ifndef __MultiViewerConnectDlg__
#define __MultiViewerConnectDlg__

/**
@file
Subclass of ConnectDlg, which is generated by wxFormBuilder.
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

/** Implementing ConnectDlg */
class MultiViewerConnectDlg : public ConnectDlg
{
protected:
	// Handlers for ConnectDlg events.
	void OnCancelButtonClick( wxCommandEvent& event );
	void OnOKButtonClick( wxCommandEvent& event );
	
public:
	/** Constructor */
	MultiViewerConnectDlg( wxWindow* parent );

public:
	void SetData(const char* a_pHost, const char* a_pPort, const char* a_pDBName, const char* a_pID, const char* a_pPassword);
	void AddConnectType(const char* a_strConnectType);
	

	wxString GetName();
	wxString GetHost();
	wxString GetPort();
	wxString GetDBName();
	wxString GetID();
	wxString GetPassword();
	wxString GetType();
};

#endif // __MultiViewerConnectDlg__
