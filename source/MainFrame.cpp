///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../source/MainFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );
	
	wxBoxSizer* mMainFrameSizer;
	mMainFrameSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pMainNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_pMainNotebook->SetMinSize( wxSize( -1,400 ) );
	
	mDatabasePanel = new wxPanel( m_pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pTableInfoTreeCtrl = new wxTreeCtrl( mDatabasePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT|wxTR_SINGLE );
	bSizer3->Add( m_pTableInfoTreeCtrl, 1, wxALL|wxEXPAND, 5 );
	
	mDatabasePanel->SetSizer( bSizer3 );
	mDatabasePanel->Layout();
	bSizer3->Fit( mDatabasePanel );
	m_pMainNotebook->AddPage( mDatabasePanel, wxT("Database"), true );
	m_pTablePanel = new wxPanel( m_pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_panel5 = new wxPanel( m_pTablePanel, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	m_panel5->SetMinSize( wxSize( -1,25 ) );
	m_panel5->SetMaxSize( wxSize( -1,25 ) );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( m_panel5, wxID_ANY, wxT("Table : "), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText2->Wrap( -1 );
	bSizer5->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );
	
	wxArrayString m_pTableNameChoiceChoices;
	m_pTableNameChoice = new wxChoice( m_panel5, wxID_ANY, wxDefaultPosition, wxSize( 140,-1 ), m_pTableNameChoiceChoices, 0 );
	m_pTableNameChoice->SetSelection( 0 );
	bSizer5->Add( m_pTableNameChoice, 1, wxALIGN_CENTER_VERTICAL|wxALL, 4 );
	
	m_pTableSelectButton = new wxButton( m_panel5, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_pTableSelectButton, 0, wxALIGN_CENTER|wxALIGN_LEFT|wxALIGN_RIGHT|wxRIGHT|wxLEFT, 20 );
	
	m_pAddRowtButton = new wxButton( m_panel5, wxID_ANY, wxT("Add Row"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_pAddRowtButton, 0, wxALIGN_CENTER|wxLEFT, 100 );
	
	m_panel5->SetSizer( bSizer5 );
	m_panel5->Layout();
	bSizer5->Fit( m_panel5 );
	bSizer4->Add( m_panel5, 0, wxALL|wxEXPAND, 5 );
	
	m_panel6 = new wxPanel( m_pTablePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pTableDBDataGrid = new wxGrid( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pTableDBDataGrid->CreateGrid( 0, 0 );
	m_pTableDBDataGrid->EnableEditing( true );
	m_pTableDBDataGrid->EnableGridLines( true );
	m_pTableDBDataGrid->EnableDragGridSize( false );
	m_pTableDBDataGrid->SetMargins( 0, 0 );
	
	// Columns
	m_pTableDBDataGrid->EnableDragColMove( false );
	m_pTableDBDataGrid->EnableDragColSize( true );
	m_pTableDBDataGrid->SetColLabelSize( 30 );
	m_pTableDBDataGrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pTableDBDataGrid->EnableDragRowSize( true );
	m_pTableDBDataGrid->SetRowLabelSize( 80 );
	m_pTableDBDataGrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pTableDBDataGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_pTableDBDataGrid->SetMinSize( wxSize( 300,270 ) );
	
	bSizer6->Add( m_pTableDBDataGrid, 5, wxALL|wxEXPAND, 5 );
	
	m_panel6->SetSizer( bSizer6 );
	m_panel6->Layout();
	bSizer6->Fit( m_panel6 );
	bSizer4->Add( m_panel6, 5, wxALL|wxEXPAND, 5 );
	
	mGridScrollPanel = new wxPanel( m_pTablePanel, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	mGridScrollPanel->SetMinSize( wxSize( -1,25 ) );
	mGridScrollPanel->SetMaxSize( wxSize( -1,25 ) );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pTableDBStartButton = new wxButton( mGridScrollPanel, wxID_ANY, wxT("<<"), wxDefaultPosition, wxSize( 30,22 ), 0 );
	m_pTableDBStartButton->SetMaxSize( wxSize( -1,22 ) );
	
	bSizer7->Add( m_pTableDBStartButton, 0, wxALIGN_CENTER_VERTICAL, 0 );
	
	mTableDBSlider = new wxSlider( mGridScrollPanel, wxID_ANY, 0, 0, 1, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer7->Add( mTableDBSlider, 2, wxALIGN_CENTER_VERTICAL, 5 );
	
	m_pTableDBEndButton = new wxButton( mGridScrollPanel, wxID_ANY, wxT(">>"), wxDefaultPosition, wxSize( 30,22 ), 0 );
	m_pTableDBEndButton->SetMaxSize( wxSize( -1,22 ) );
	
	bSizer7->Add( m_pTableDBEndButton, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 20 );
	
	m_pCurrentRowTextCtrl = new wxTextCtrl( mGridScrollPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_pCurrentRowTextCtrl->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer7->Add( m_pCurrentRowTextCtrl, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_pTotalStaticText = new wxStaticText( mGridScrollPanel, wxID_ANY, wxT(" / Total"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pTotalStaticText->Wrap( -1 );
	bSizer7->Add( m_pTotalStaticText, 0, wxALIGN_CENTER|wxRIGHT, 10 );
	
	mGridScrollPanel->SetSizer( bSizer7 );
	mGridScrollPanel->Layout();
	bSizer7->Fit( mGridScrollPanel );
	bSizer4->Add( mGridScrollPanel, 0, wxALIGN_LEFT|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	m_pTablePanel->SetSizer( bSizer4 );
	m_pTablePanel->Layout();
	bSizer4->Fit( m_pTablePanel );
	m_pMainNotebook->AddPage( m_pTablePanel, wxT("Table"), false );
	mExePanel = new wxPanel( m_pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* gbSizer6;
	gbSizer6 = new wxGridBagSizer( 5, 5 );
	gbSizer6->SetFlexibleDirection( wxBOTH );
	gbSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_pHistoryCombo = new wxComboBox( mExePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	m_pHistoryCombo->SetMinSize( wxSize( 520,-1 ) );
	
	gbSizer6->Add( m_pHistoryCombo, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_pLoadButton = new wxButton( mExePanel, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer6->Add( m_pLoadButton, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_RIGHT, 5 );
	
	m_pQueryTextCtrl = new wxTextCtrl( mExePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_pQueryTextCtrl->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	m_pQueryTextCtrl->SetMinSize( wxSize( 520,80 ) );
	
	gbSizer6->Add( m_pQueryTextCtrl, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_pQueryButton = new wxButton( mExePanel, wxID_ANY, wxT("Query"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer6->Add( m_pQueryButton, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND|wxALIGN_RIGHT, 5 );
	
	bSizer8->Add( gbSizer6, 0, wxEXPAND, 5 );
	
	m_pQueryGrid = new wxGrid( mExePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pQueryGrid->CreateGrid( 0, 0 );
	m_pQueryGrid->EnableEditing( true );
	m_pQueryGrid->EnableGridLines( true );
	m_pQueryGrid->EnableDragGridSize( false );
	m_pQueryGrid->SetMargins( 0, 0 );
	
	// Columns
	m_pQueryGrid->EnableDragColMove( false );
	m_pQueryGrid->EnableDragColSize( true );
	m_pQueryGrid->SetColLabelSize( 30 );
	m_pQueryGrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pQueryGrid->EnableDragRowSize( true );
	m_pQueryGrid->SetRowLabelSize( 80 );
	m_pQueryGrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pQueryGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer8->Add( m_pQueryGrid, 1, wxALL|wxEXPAND, 5 );
	
	mExePanel->SetSizer( bSizer8 );
	mExePanel->Layout();
	bSizer8->Fit( mExePanel );
	m_pMainNotebook->AddPage( mExePanel, wxT("Exe"), false );
	
	mMainFrameSizer->Add( m_pMainNotebook, 3, wxEXPAND | wxALL, 5 );
	
	m_pDebugPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pLOGTextCtrl = new wxTextCtrl( m_pDebugPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,128 ), wxTE_MULTILINE );
	bSizer2->Add( m_pLOGTextCtrl, 1, wxALL|wxEXPAND, 5 );
	
	m_pDebugPanel->SetSizer( bSizer2 );
	m_pDebugPanel->Layout();
	bSizer2->Fit( m_pDebugPanel );
	mMainFrameSizer->Add( m_pDebugPanel, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( mMainFrameSizer );
	this->Layout();
	mMenubar = new wxMenuBar( 0 );
	m_pFileMenu = new wxMenu();
	wxMenuItem* m_pFineNewMenuItem;
	m_pFineNewMenuItem = new wxMenuItem( m_pFileMenu, wxID_FILE_NEW, wxString( wxT("&New..") ) , wxEmptyString, wxITEM_NORMAL );
	m_pFileMenu->Append( m_pFineNewMenuItem );
	
	wxMenuItem* m_pFileOpenMenuItem;
	m_pFileOpenMenuItem = new wxMenuItem( m_pFileMenu, wxID_FILE_OPEN, wxString( wxT("&Open...") ) , wxEmptyString, wxITEM_NORMAL );
	m_pFileMenu->Append( m_pFileOpenMenuItem );
	
	wxMenuItem* m_pFileConnectMenuItem;
	m_pFileConnectMenuItem = new wxMenuItem( m_pFileMenu, wxID_FILE_CONNECT, wxString( wxT("&Connect...") ) , wxEmptyString, wxITEM_NORMAL );
	m_pFileMenu->Append( m_pFileConnectMenuItem );
	
	wxMenuItem* m_pFileSaveMenuItem;
	m_pFileSaveMenuItem = new wxMenuItem( m_pFileMenu, wxID_FILE_SAVE, wxString( wxT("&Save...") ) , wxEmptyString, wxITEM_NORMAL );
	m_pFileMenu->Append( m_pFileSaveMenuItem );
	
	wxMenuItem* m_pFileExitMenuItem;
	m_pFileExitMenuItem = new wxMenuItem( m_pFileMenu, wxID_FILE_EXIT, wxString( wxT("E&xit") ) , wxEmptyString, wxITEM_NORMAL );
	m_pFileMenu->Append( m_pFileExitMenuItem );
	
	mMenubar->Append( m_pFileMenu, wxT("&File") ); 
	
	m_pViewMenu = new wxMenu();
	wxMenuItem* m_pViewLogViewMenuItem;
	m_pViewLogViewMenuItem = new wxMenuItem( m_pViewMenu, wxID_VIEW_LOGVIEW, wxString( wxT("LogView") ) , wxEmptyString, wxITEM_CHECK );
	m_pViewMenu->Append( m_pViewLogViewMenuItem );
	m_pViewLogViewMenuItem->Check( true );
	
	mMenubar->Append( m_pViewMenu, wxT("&View") ); 
	
	m_pHelpMenu = new wxMenu();
	wxMenuItem* m_pHelpAboutmenuItem;
	m_pHelpAboutmenuItem = new wxMenuItem( m_pHelpMenu, wxID_ANY, wxString( wxT("&About...") ) , wxEmptyString, wxITEM_NORMAL );
	m_pHelpMenu->Append( m_pHelpAboutmenuItem );
	
	mMenubar->Append( m_pHelpMenu, wxT("&Help") ); 
	
	this->SetMenuBar( mMenubar );
	
	m_pSatusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_pFileSaveTool = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_NEW, wxT("New"), wxBitmap( wxT("res/document-new.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_FILE_OPEN, wxT("Open"), wxBitmap( wxT("res/document-open.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("File Open"), wxEmptyString ); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_FILE_CONNECT, wxT("tool"), wxBitmap( wxT("res/network-transmit.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Connect"), wxEmptyString ); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_FILE_SAVE, wxT("Save"), wxBitmap( wxT("res/document-save.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("File Save"), wxEmptyString ); 
	m_pFileSaveTool->AddSeparator(); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_UNDO, wxT("tool"), wxBitmap( wxT("res/edit-undo.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_pFileSaveTool->AddSeparator(); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_TABLE_ADD, wxT("tool"), wxBitmap( wxT("res/table_add.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_TABLE_DELETE, wxT("tool"), wxBitmap( wxT("res/table_remove.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_pFileSaveTool->AddTool( wxID_TOOLBAR_TABLE_MODIFY, wxT("tool"), wxBitmap( wxT("res/table_modify.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString ); 
	m_pFileSaveTool->Realize();
	
	
	// Connect Events
	m_pTableSelectButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTableSelectButtonClick ), NULL, this );
	m_pAddRowtButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddRowButtonClick ), NULL, this );
	m_pTableDBDataGrid->Connect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( MainFrame::OnTableDBGridCellChange ), NULL, this );
	m_pTableDBDataGrid->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( MainFrame::OnTableDBGridLeftClick ), NULL, this );
	m_pTableDBDataGrid->Connect( wxEVT_GRID_LABEL_RIGHT_CLICK, wxGridEventHandler( MainFrame::OnTableDBGridLabelRightClick ), NULL, this );
	m_pTableDBStartButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTableDBStartButtonClick ), NULL, this );
	mTableDBSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::OnTableDBSliderDown ), NULL, this );
	mTableDBSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::OnTableDBSliderUp ), NULL, this );
	mTableDBSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::OnTableDBSliderDown ), NULL, this );
	mTableDBSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::OnTableDBSliderUp ), NULL, this );
	mTableDBSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::OnTableDBSliderRelease ), NULL, this );
	m_pTableDBEndButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTableDBEndButtonClick ), NULL, this );
	m_pCurrentRowTextCtrl->Connect( wxEVT_KEY_UP, wxKeyEventHandler( MainFrame::OnCurrentRowTextCtrlKeyUp ), NULL, this );
	m_pLoadButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnHistoryQueryLoad ), NULL, this );
	m_pQueryButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnQueryButtonClick ), NULL, this );
	this->Connect( m_pFineNewMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileNew ) );
	this->Connect( m_pFileOpenMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileOpen ) );
	this->Connect( m_pFileConnectMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileConnect ) );
	this->Connect( m_pFileSaveMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileSave ) );
	this->Connect( m_pFileExitMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileExit ) );
	this->Connect( m_pViewLogViewMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUILogView ) );
	this->Connect( m_pHelpAboutmenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIHelpAbout ) );
	this->Connect( wxID_TOOLBAR_NEW, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileNew ) );
	this->Connect( wxID_TOOLBAR_FILE_OPEN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileOpen ) );
	this->Connect( wxID_TOOLBAR_FILE_CONNECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileConnect ) );
	this->Connect( wxID_TOOLBAR_FILE_SAVE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileSave ) );
	this->Connect( wxID_TOOLBAR_UNDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUndo ) );
	this->Connect( wxID_TOOLBAR_TABLE_ADD, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnTableAdd ) );
	this->Connect( wxID_TOOLBAR_TABLE_DELETE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnTableDelete ) );
	this->Connect( wxID_TOOLBAR_TABLE_MODIFY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnTableModify ) );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_pTableSelectButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTableSelectButtonClick ), NULL, this );
	m_pAddRowtButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddRowButtonClick ), NULL, this );
	m_pTableDBDataGrid->Disconnect( wxEVT_GRID_CELL_CHANGE, wxGridEventHandler( MainFrame::OnTableDBGridCellChange ), NULL, this );
	m_pTableDBDataGrid->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( MainFrame::OnTableDBGridLeftClick ), NULL, this );
	m_pTableDBDataGrid->Disconnect( wxEVT_GRID_LABEL_RIGHT_CLICK, wxGridEventHandler( MainFrame::OnTableDBGridLabelRightClick ), NULL, this );
	m_pTableDBStartButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTableDBStartButtonClick ), NULL, this );
	mTableDBSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::OnTableDBSliderDown ), NULL, this );
	mTableDBSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::OnTableDBSliderUp ), NULL, this );
	mTableDBSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::OnTableDBSliderDown ), NULL, this );
	mTableDBSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::OnTableDBSliderUp ), NULL, this );
	mTableDBSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::OnTableDBSliderRelease ), NULL, this );
	m_pTableDBEndButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTableDBEndButtonClick ), NULL, this );
	m_pCurrentRowTextCtrl->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( MainFrame::OnCurrentRowTextCtrlKeyUp ), NULL, this );
	m_pLoadButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnHistoryQueryLoad ), NULL, this );
	m_pQueryButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnQueryButtonClick ), NULL, this );
	this->Disconnect( wxID_FILE_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileNew ) );
	this->Disconnect( wxID_FILE_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileOpen ) );
	this->Disconnect( wxID_FILE_CONNECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileConnect ) );
	this->Disconnect( wxID_FILE_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileSave ) );
	this->Disconnect( wxID_FILE_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIFileExit ) );
	this->Disconnect( wxID_VIEW_LOGVIEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUILogView ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnUIHelpAbout ) );
	this->Disconnect( wxID_TOOLBAR_NEW, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileNew ) );
	this->Disconnect( wxID_TOOLBAR_FILE_OPEN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileOpen ) );
	this->Disconnect( wxID_TOOLBAR_FILE_CONNECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileConnect ) );
	this->Disconnect( wxID_TOOLBAR_FILE_SAVE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUIFileSave ) );
	this->Disconnect( wxID_TOOLBAR_UNDO, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnUndo ) );
	this->Disconnect( wxID_TOOLBAR_TABLE_ADD, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnTableAdd ) );
	this->Disconnect( wxID_TOOLBAR_TABLE_DELETE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnTableDelete ) );
	this->Disconnect( wxID_TOOLBAR_TABLE_MODIFY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrame::OnTableModify ) );
	
}

ColDataDlg::ColDataDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 3, 1, 5, 10 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 3 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_NONE );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Name : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer10->Add( m_staticText7, 0, 0, 5 );
	
	m_pNameTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	bSizer10->Add( m_pNameTextCtrl, 0, 0, 5 );
	
	fgSizer3->Add( bSizer10, 1, wxALL|wxEXPAND, 10 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Type : "), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_staticText8->Wrap( -1 );
	bSizer11->Add( m_staticText8, 0, 0, 0 );
	
	m_pTypeComboBox = new wxComboBox( this, wxID_ANY, wxEmptyString, wxPoint( -1,-1 ), wxSize( 300,-1 ), 0, NULL, 0 );
	m_pTypeComboBox->Append( wxT("INTEGER") );
	m_pTypeComboBox->Append( wxT("REAL") );
	m_pTypeComboBox->Append( wxT("TEXT") );
	m_pTypeComboBox->Append( wxT("BLOB") );
	m_pTypeComboBox->Append( wxT("INTEGER PRIMARY KEY") );
	bSizer11->Add( m_pTypeComboBox, 0, 0, 5 );
	
	fgSizer3->Add( bSizer11, 1, wxALL|wxEXPAND, 10 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pCancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_pCancelButton, 0, wxALL, 5 );
	
	m_pOKButton = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_pOKButton, 0, wxALL, 5 );
	
	fgSizer3->Add( bSizer12, 1, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( fgSizer3 );
	this->Layout();
	
	// Connect Events
	m_pCancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColDataDlg::OnCancelButtonClick ), NULL, this );
	m_pOKButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColDataDlg::OnOKButtonClick ), NULL, this );
}

ColDataDlg::~ColDataDlg()
{
	// Disconnect Events
	m_pCancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColDataDlg::OnCancelButtonClick ), NULL, this );
	m_pOKButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColDataDlg::OnOKButtonClick ), NULL, this );
	
}

TableNameDlg::TableNameDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticTextModifyTable = new wxStaticText( this, wxID_ANY, wxT("modify Table : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextModifyTable->Wrap( -1 );
	bSizer27->Add( m_staticTextModifyTable, 0, wxALL, 5 );
	
	wxArrayString m_pChoiceModifyTableChoices;
	m_pChoiceModifyTable = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_pChoiceModifyTableChoices, 0 );
	m_pChoiceModifyTable->SetSelection( 0 );
	m_pChoiceModifyTable->SetMinSize( wxSize( 300,-1 ) );
	
	bSizer27->Add( m_pChoiceModifyTable, 0, wxALL, 5 );
	
	fgSizer3->Add( bSizer27, 1, wxALIGN_CENTER|wxBOTTOM|wxTOP, 8 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pSTTableName = new wxStaticText( this, wxID_ANY, wxT("Table Name : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_pSTTableName->Wrap( -1 );
	bSizer12->Add( m_pSTTableName, 0, wxALIGN_CENTER|wxALIGN_LEFT|wxLEFT, 10 );
	
	m_pTableNameTextCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_pTableNameTextCtrl->SetMinSize( wxSize( 300,-1 ) );
	
	bSizer12->Add( m_pTableNameTextCtrl, 0, wxALIGN_CENTER|wxLEFT|wxRIGHT, 10 );
	
	fgSizer3->Add( bSizer12, 1, wxALIGN_CENTER|wxBOTTOM|wxTOP, 8 );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pCreateGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pCreateGrid->CreateGrid( 0, 2 );
	m_pCreateGrid->EnableEditing( true );
	m_pCreateGrid->EnableGridLines( true );
	m_pCreateGrid->EnableDragGridSize( true );
	m_pCreateGrid->SetMargins( 2, 2 );
	
	// Columns
	m_pCreateGrid->SetColSize( 0, 160 );
	m_pCreateGrid->SetColSize( 1, 270 );
	m_pCreateGrid->EnableDragColMove( false );
	m_pCreateGrid->EnableDragColSize( true );
	m_pCreateGrid->SetColLabelSize( 30 );
	m_pCreateGrid->SetColLabelValue( 0, wxT("name") );
	m_pCreateGrid->SetColLabelValue( 1, wxT("data type") );
	m_pCreateGrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pCreateGrid->AutoSizeRows();
	m_pCreateGrid->EnableDragRowSize( true );
	m_pCreateGrid->SetRowLabelSize( 60 );
	m_pCreateGrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pCreateGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_pCreateGrid->Hide();
	m_pCreateGrid->SetMinSize( wxSize( -1,160 ) );
	
	bSizer18->Add( m_pCreateGrid, 0, wxALL|wxEXPAND, 10 );
	
	m_pEditGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_pEditGrid->CreateGrid( 0, 4 );
	m_pEditGrid->EnableEditing( true );
	m_pEditGrid->EnableGridLines( true );
	m_pEditGrid->EnableDragGridSize( false );
	m_pEditGrid->SetMargins( 0, 0 );
	
	// Columns
	m_pEditGrid->SetColSize( 0, 100 );
	m_pEditGrid->SetColSize( 1, 160 );
	m_pEditGrid->SetColSize( 2, 100 );
	m_pEditGrid->SetColSize( 3, 160 );
	m_pEditGrid->EnableDragColMove( false );
	m_pEditGrid->EnableDragColSize( true );
	m_pEditGrid->SetColLabelSize( 30 );
	m_pEditGrid->SetColLabelValue( 0, wxT("old name") );
	m_pEditGrid->SetColLabelValue( 1, wxT("old data type") );
	m_pEditGrid->SetColLabelValue( 2, wxT("new name") );
	m_pEditGrid->SetColLabelValue( 3, wxT("new dada type") );
	m_pEditGrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_pEditGrid->AutoSizeRows();
	m_pEditGrid->EnableDragRowSize( true );
	m_pEditGrid->SetRowLabelSize( 40 );
	m_pEditGrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_pEditGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_pEditGrid->SetMinSize( wxSize( -1,160 ) );
	
	bSizer18->Add( m_pEditGrid, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	m_pUpBtn = new wxButton( this, wxID_ANY, wxT("up"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pUpBtn->Enable( false );
	m_pUpBtn->SetMinSize( wxSize( 40,-1 ) );
	
	bSizer26->Add( m_pUpBtn, 0, wxALIGN_TOP|wxBOTTOM|wxLEFT|wxTOP, 10 );
	
	m_pDownBtn = new wxButton( this, wxID_ANY, wxT("down"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pDownBtn->Enable( false );
	m_pDownBtn->SetMinSize( wxSize( 40,-1 ) );
	
	bSizer26->Add( m_pDownBtn, 0, wxBOTTOM|wxLEFT|wxTOP, 10 );
	
	bSizer18->Add( bSizer26, 0, wxALIGN_CENTER, 5 );
	
	fgSizer3->Add( bSizer18, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pDeleteBtn = new wxButton( this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_pDeleteBtn, 0, wxLEFT|wxRIGHT, 10 );
	
	m_pRecallBtn = new wxButton( this, wxID_ANY, wxT("Recall"), wxDefaultPosition, wxDefaultSize, 0 );
	m_pRecallBtn->Hide();
	
	bSizer19->Add( m_pRecallBtn, 0, wxLEFT|wxRIGHT, 10 );
	
	m_pAddBtn = new wxButton( this, wxID_ANY, wxT("Add..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_pAddBtn, 0, wxLEFT|wxRIGHT, 10 );
	
	fgSizer3->Add( bSizer19, 1, wxALIGN_RIGHT|wxBOTTOM|wxTOP, 8 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pCancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_pCancelButton, 0, wxLEFT|wxRIGHT, 10 );
	
	m_pOKButton = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_pOKButton, 0, wxLEFT|wxRIGHT, 10 );
	
	fgSizer3->Add( bSizer13, 1, wxALIGN_RIGHT|wxBOTTOM|wxTOP, 8 );
	
	this->SetSizer( fgSizer3 );
	this->Layout();
	
	// Connect Events
	m_pChoiceModifyTable->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TableNameDlg::OnTableModifyChoice ), NULL, this );
	m_pCreateGrid->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( TableNameDlg::OnGridLabelLeftClick ), NULL, this );
	m_pEditGrid->Connect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( TableNameDlg::OnGridLabelLeftClick ), NULL, this );
	m_pEditGrid->Connect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( TableNameDlg::OnGridSelectCell ), NULL, this );
	m_pUpBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnUpButtonClick ), NULL, this );
	m_pDownBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnDownButtonClick ), NULL, this );
	m_pDeleteBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnDeleteBtnClick ), NULL, this );
	m_pRecallBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnRecallBtnClick ), NULL, this );
	m_pAddBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnAddBtnClick ), NULL, this );
	m_pCancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnCancelButtonClick ), NULL, this );
	m_pOKButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnOKButtonClick ), NULL, this );
}

TableNameDlg::~TableNameDlg()
{
	// Disconnect Events
	m_pChoiceModifyTable->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TableNameDlg::OnTableModifyChoice ), NULL, this );
	m_pCreateGrid->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( TableNameDlg::OnGridLabelLeftClick ), NULL, this );
	m_pEditGrid->Disconnect( wxEVT_GRID_LABEL_LEFT_CLICK, wxGridEventHandler( TableNameDlg::OnGridLabelLeftClick ), NULL, this );
	m_pEditGrid->Disconnect( wxEVT_GRID_SELECT_CELL, wxGridEventHandler( TableNameDlg::OnGridSelectCell ), NULL, this );
	m_pUpBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnUpButtonClick ), NULL, this );
	m_pDownBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnDownButtonClick ), NULL, this );
	m_pDeleteBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnDeleteBtnClick ), NULL, this );
	m_pRecallBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnRecallBtnClick ), NULL, this );
	m_pAddBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnAddBtnClick ), NULL, this );
	m_pCancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnCancelButtonClick ), NULL, this );
	m_pOKButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameDlg::OnOKButtonClick ), NULL, this );
	
}

TableNameSelectDlg::TableNameSelectDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 1, 1, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Select Table : "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer14->Add( m_staticText6, 0, wxALIGN_CENTER|wxALIGN_LEFT|wxLEFT, 10 );
	
	wxArrayString m_pTableChoiceChoices;
	m_pTableChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), m_pTableChoiceChoices, 0 );
	m_pTableChoice->SetSelection( 0 );
	bSizer14->Add( m_pTableChoice, 0, wxLEFT|wxRIGHT, 10 );
	
	fgSizer3->Add( bSizer14, 1, wxALIGN_CENTER|wxBOTTOM|wxTOP, 16 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_pCancelButton = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_pCancelButton, 0, wxLEFT|wxRIGHT, 10 );
	
	m_pOKButton = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer19->Add( m_pOKButton, 0, wxLEFT|wxRIGHT, 10 );
	
	fgSizer3->Add( bSizer19, 1, wxALIGN_RIGHT|wxBOTTOM|wxTOP, 16 );
	
	this->SetSizer( fgSizer3 );
	this->Layout();
	
	// Connect Events
	m_pCancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameSelectDlg::OnCancelButtonClick ), NULL, this );
	m_pOKButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameSelectDlg::OnOKButtonClick ), NULL, this );
}

TableNameSelectDlg::~TableNameSelectDlg()
{
	// Disconnect Events
	m_pCancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameSelectDlg::OnCancelButtonClick ), NULL, this );
	m_pOKButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TableNameSelectDlg::OnOKButtonClick ), NULL, this );
	
}

ConnectDlg::ConnectDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Connect Name"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText8->Wrap( -1 );
	bSizer18->Add( m_staticText8, 0, wxALL, 5 );
	
	m_pConnectName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	bSizer18->Add( m_pConnectName, 0, wxALL, 5 );
	
	fgSizer6->Add( bSizer18, 1, wxEXPAND, 5 );
	
	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,5 ), wxTAB_TRAVERSAL );
	fgSizer6->Add( m_panel8, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("Connect Host"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText10->Wrap( -1 );
	bSizer19->Add( m_staticText10, 0, wxALL, 5 );
	
	m_pConnectHost = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	bSizer19->Add( m_pConnectHost, 0, wxALL, 5 );
	
	fgSizer6->Add( bSizer19, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Port"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText11->Wrap( -1 );
	bSizer21->Add( m_staticText11, 0, wxALL, 5 );
	
	m_pConnectPort = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	bSizer21->Add( m_pConnectPort, 0, wxALL, 5 );
	
	fgSizer6->Add( bSizer21, 1, wxALIGN_TOP, 5 );
	
	m_panel81 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,5 ), wxTAB_TRAVERSAL );
	fgSizer6->Add( m_panel81, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer251;
	bSizer251 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText131 = new wxStaticText( this, wxID_ANY, wxT("DB Name"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText131->Wrap( -1 );
	bSizer251->Add( m_staticText131, 0, wxALL, 5 );
	
	m_pDBName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	bSizer251->Add( m_pDBName, 0, wxALL, 5 );
	
	fgSizer6->Add( bSizer251, 1, wxEXPAND, 5 );
	
	m_panel812 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,5 ), wxTAB_TRAVERSAL );
	fgSizer6->Add( m_panel812, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("ID"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText12->Wrap( -1 );
	bSizer23->Add( m_staticText12, 0, wxALL, 5 );
	
	m_pConnectID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	bSizer23->Add( m_pConnectID, 0, wxALL, 5 );
	
	fgSizer6->Add( bSizer23, 1, 0, 10 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("Password"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText13->Wrap( -1 );
	bSizer24->Add( m_staticText13, 0, wxALL, 5 );
	
	m_pConnectPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_PASSWORD );
	bSizer24->Add( m_pConnectPassword, 0, wxALL, 5 );
	
	fgSizer6->Add( bSizer24, 1, wxEXPAND, 5 );
	
	m_panel811 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,5 ), wxTAB_TRAVERSAL );
	fgSizer6->Add( m_panel811, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Connection Type"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText14->Wrap( -1 );
	bSizer25->Add( m_staticText14, 0, wxALL, 5 );
	
	wxArrayString m_pConnectTypeChoices;
	m_pConnectType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), m_pConnectTypeChoices, 0 );
	m_pConnectType->SetSelection( 0 );
	bSizer25->Add( m_pConnectType, 0, wxALL, 5 );
	
	fgSizer6->Add( bSizer25, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer26->SetMinSize( wxSize( -1,50 ) ); 
	m_pCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( m_pCancel, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	m_pOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( m_pOK, 0, wxALIGN_BOTTOM|wxALL, 5 );
	
	fgSizer6->Add( bSizer26, 1, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( fgSizer6 );
	this->Layout();
	
	// Connect Events
	m_pCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConnectDlg::OnCancelButtonClick ), NULL, this );
	m_pOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConnectDlg::OnOKButtonClick ), NULL, this );
}

ConnectDlg::~ConnectDlg()
{
	// Disconnect Events
	m_pCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConnectDlg::OnCancelButtonClick ), NULL, this );
	m_pOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConnectDlg::OnOKButtonClick ), NULL, this );
	
}
