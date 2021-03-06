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
#ifndef __MultiViewerTableNameDlg__
#define __MultiViewerTableNameDlg__

/**
@file
Subclass of TableNameDlg, which is generated by wxFormBuilder.
*/

#include "MainFrame.h"
#include "SQLReaderBase.h"
#include "GridUtil.h"
#include <wx/string.h>

#include "SQLData.h"

/** Implementing TableNameDlg */
class MultiViewerTableNameDlg : public TableNameDlg
{
protected:
	// Handlers for TableNameDlg events.
	void OnCancelButtonClick( wxCommandEvent& event );
	void OnOKButtonClick( wxCommandEvent& event );

public:
	/** Constructor */
	MultiViewerTableNameDlg( wxWindow* parent, SQLReaderBase* pSQLReader, bool bCreateMode = true );

	~MultiViewerTableNameDlg();

	wxString GetTableName();
	ST_TableInfo GetColList();

	void OnDeleteBtnClick( wxCommandEvent& event );
	void OnAddBtnClick( wxCommandEvent& event );
	void OnRecallBtnClick( wxCommandEvent& event );
	void OnUpButtonClick( wxCommandEvent& event );
	void OnDownButtonClick( wxCommandEvent& event );

	void OnGridCmdRangeSelect( wxGridRangeSelectEvent& event );
	void OnTableModifyChoice( wxCommandEvent& event );
	void OnGridLabelLeftClick( wxGridEvent& event );
	void OnGridSelectCell( wxGridEvent& event );

private:
	static int ReverseCmpFunc(int *a_nFirst, int *a_nSecond)
	{
		if( *a_nFirst > *a_nSecond)
			return -1;
		else if(*a_nFirst == *a_nSecond)
			return 0;
		else
			return 1;
	}

private:
	bool m_bGridRangeSelect;
	bool m_bCreateMode;
	unsigned int m_nOldSelect;
	wxGrid *m_pGrid;
	SQLReaderBase* m_pSQLReader;
	//CancelCellRender* m_pCancelRender;
};

#endif // __MultiViewerTableNameDlg__
