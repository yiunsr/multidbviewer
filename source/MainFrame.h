///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MainFrame__
#define __MainFrame__

#include <wx/treectrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/grid.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/gbsizer.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			wxID_FILE_NEW = 1000,
			wxID_FILE_OPEN,
			wxID_FILE_CONNECT,
			wxID_FILE_SAVE,
			wxID_FILE_EXIT,
			wxID_VIEW_LOGVIEW,
			wxID_TOOLBAR_NEW,
			wxID_TOOLBAR_FILE_OPEN,
			wxID_TOOLBAR_FILE_CONNECT,
			wxID_TOOLBAR_FILE_SAVE,
			wxID_TOOLBAR_UNDO,
			wxID_TOOLBAR_TABLE_ADD,
			wxID_TOOLBAR_TABLE_DELETE,
			wxID_TOOLBAR_TABLE_MODIFY,
		};
		
		wxNotebook* m_pMainNotebook;
		wxPanel* mDatabasePanel;
		wxTreeCtrl* m_pTableInfoTreeCtrl;
		wxPanel* m_pTablePanel;
		wxPanel* m_panel5;
		wxStaticText* m_staticText2;
		wxChoice* m_pTableNameChoice;
		wxButton* m_pTableSelectButton;
		wxButton* m_pAddRowtButton;
		wxPanel* m_panel6;
		wxGrid* m_pTableDBDataGrid;
		wxPanel* mGridScrollPanel;
		wxButton* m_pTableDBStartButton;
		wxSlider* mTableDBSlider;
		wxButton* m_pTableDBEndButton;
		wxTextCtrl* m_pCurrentRowTextCtrl;
		wxStaticText* m_pTotalStaticText;
		wxPanel* mExePanel;
		wxComboBox* m_pHistoryCombo;
		wxButton* m_pLoadButton;
		wxTextCtrl* m_pQueryTextCtrl;
		wxButton* m_pQueryButton;
		wxGrid* m_pQueryGrid;
		wxPanel* m_pDebugPanel;
		wxTextCtrl* m_pLOGTextCtrl;
		wxMenuBar* mMenubar;
		wxMenu* m_pFileMenu;
		wxMenu* m_pViewMenu;
		wxMenu* m_pHelpMenu;
		wxStatusBar* m_pSatusBar;
		wxToolBar* m_pFileSaveTool;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTableSelectButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddRowButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableDBGridCellChange( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableDBGridLeftClick( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableDBGridLabelRightClick( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableDBStartButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableDBSliderDown( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnTableDBSliderUp( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnTableDBSliderRelease( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnTableDBEndButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCurrentRowTextCtrlKeyUp( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnHistoryQueryLoad( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQueryButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUIFileNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUIFileOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUIFileConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUIFileSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUIFileExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUILogView( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUIHelpAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUndo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableModify( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MultiViewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 660,640 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ColDataDlg
///////////////////////////////////////////////////////////////////////////////
class ColDataDlg : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText7;
		wxTextCtrl* m_pNameTextCtrl;
		wxStaticText* m_staticText8;
		wxComboBox* m_pTypeComboBox;
		wxButton* m_pCancelButton;
		wxButton* m_pOKButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ColDataDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Edit Column Info"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 394,179 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ColDataDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TableNameDlg
///////////////////////////////////////////////////////////////////////////////
class TableNameDlg : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticTextModifyTable;
		wxChoice* m_pChoiceModifyTable;
		wxStaticText* m_pSTTableName;
		wxTextCtrl* m_pTableNameTextCtrl;
		wxGrid* m_pCreateGrid;
		wxGrid* m_pEditGrid;
		wxButton* m_pUpBtn;
		wxButton* m_pDownBtn;
		wxButton* m_pDeleteBtn;
		wxButton* m_pRecallBtn;
		wxButton* m_pAddBtn;
		wxButton* m_pCancelButton;
		wxButton* m_pOKButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnTableModifyChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGridLabelLeftClick( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridSelectCell( wxGridEvent& event ) { event.Skip(); }
		virtual void OnUpButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDownButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteBtnClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRecallBtnClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddBtnClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TableNameDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Create New Table "), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 658,373 ), long style = wxDEFAULT_DIALOG_STYLE );
		~TableNameDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TableNameSelectDlg
///////////////////////////////////////////////////////////////////////////////
class TableNameSelectDlg : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText6;
		wxChoice* m_pTableChoice;
		wxButton* m_pCancelButton;
		wxButton* m_pOKButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TableNameSelectDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Select Delete Table"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 430,140 ), long style = wxDEFAULT_DIALOG_STYLE );
		~TableNameSelectDlg();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ConnectDlg
///////////////////////////////////////////////////////////////////////////////
class ConnectDlg : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText8;
		wxTextCtrl* m_pConnectName;
		wxPanel* m_panel8;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_pConnectHost;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_pConnectPort;
		wxPanel* m_panel81;
		wxStaticText* m_staticText131;
		wxTextCtrl* m_pDBName;
		wxPanel* m_panel812;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_pConnectID;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_pConnectPassword;
		wxPanel* m_panel811;
		wxStaticText* m_staticText14;
		wxChoice* m_pConnectType;
		wxButton* m_pCancel;
		wxButton* m_pOK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ConnectDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 512,384 ), long style = wxDEFAULT_DIALOG_STYLE );
		~ConnectDlg();
	
};

#endif //__MainFrame__
