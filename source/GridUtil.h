#ifndef __GRID_RENDER_H__
#define __GRID_RENDER_H__

//////
////// base code from
////// http://forums.wxwidgets.org/viewtopic.php?t=14403
//////


#ifndef WX_PRECOMP
   #include <wx/wx.h>
#else
   #include <wx/wxprec.h>
#endif

#include <wx/grid.h>

class ButtonRenderer : public wxGridCellRenderer
{
public:

	ButtonRenderer(wxString strButtonLabel) : m_strLabel(strButtonLabel) {};

	virtual ~ButtonRenderer() { };

	virtual wxGridCellRenderer*
	Clone() const {return new ButtonRenderer(m_strLabel);};

	virtual void
	Draw( wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect,
	  int row, int col, bool isSelected);

	virtual wxSize
	GetBestSize(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, int row, int col)
		{return wxSize(75,25);};

private:
	wxString m_strLabel;

   
};

class CancelCellRender : public wxGridCellStringRenderer

{
public:
	CancelCellRender()	{	};
	virtual ~CancelCellRender() {	};
    virtual void Draw(wxGrid& grid,
                      wxGridCellAttr& attr,
                      wxDC& dc,
                      const wxRect& rect,
                      int row, int col,
                      bool isSelected);

};

//class UserDataSaveTableBase : public wxGridTableBase
//{
//private:
//	vector<wxString > m_nUserDataVector;
//
//public:
//	int GetNumberRows();
//	int GetNumberCols();
//	wxString GetValue( int row, int col );
//	void SetValue( int row, int col, const wxString& s );
//	bool IsEmptyCell( int row, int col );
//
//public:
//	bool InsertRows(size_t pos = 0, size_t numRows = 1);
//	bool AppendRows(size_t numRows = 1);
//	bool DeleteRows(size_t pos = 0, size_t numRows = 1);
//}

#endif