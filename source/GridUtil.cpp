#include "GridUtil.h"
#include <wx/renderer.h>
#include <wx/settings.h>
#include <wx/colour.h>

//////
////// base code from
////// http://forums.wxwidgets.org/viewtopic.php?t=14403
//////

void
ButtonRenderer::Draw( wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
                      const wxRect& rect, int row, int col, bool isSelected)
{
	// fill the background
	dc.SetBrush(wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE)));
	dc.DrawRectangle( rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());

	// draw a shaded rectangle to emulate a button
	// (taken from src/generic/renderg.cpp)
	//
	// it's not perfect but it works
	int strength = 1;
	wxPen pen1(*wxWHITE, strength);
	dc.SetPen(pen1);
	dc.DrawLine(rect.GetLeft()+strength-1, rect.GetTop()+strength-1,
			  rect.GetLeft()+strength-1, rect.GetBottom()-strength+1);
	dc.DrawLine(rect.GetLeft()+strength-1, rect.GetTop()+strength-1,
			  rect.GetRight()-strength, rect.GetTop()+strength-1);
	wxPen pen2(*wxBLACK, strength);
	dc.SetPen(pen2);
	dc.DrawLine(rect.GetRight()-strength, rect.GetTop(),
			  rect.GetRight()-strength, rect.GetBottom());
	dc.DrawLine(rect.GetLeft(), rect.GetBottom(),
			  rect.GetRight() - strength, rect.GetBottom());
 
 
	// another drawing routine
	// (taken from src/generic/renderg.cpp)
	/*
	const wxCoord x = rect.x,
				y = rect.y,
				w = rect.width,
				h = rect.height;

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	wxPen pen(*wxBLACK, 1);

	dc.SetPen(pen);
	dc.DrawLine( x+w, y, x+w, y+h );            // right (outer)
	dc.DrawRectangle( x, y+h, w+1, 1 );         // bottom (outer)

	pen.SetColour(wxColour(wxT("DARK GREY")));
	dc.SetPen(pen);
	dc.DrawLine( x+w-1, y, x+w-1, y+h );        // right (inner)
	dc.DrawRectangle( x+1, y+h-1, w-2, 1 );     // bottom (inner)

	pen.SetColour(*wxWHITE);
	dc.SetPen(pen);
	dc.DrawRectangle( x, y, w, 1 );             // top (outer)
	dc.DrawRectangle( x, y, 1, h );             // left (outer)
	dc.DrawLine( x, y+h-1, x+1, y+h-1 );
	dc.DrawLine( x+w-1, y, x+w-1, y+1 );
	*/
 
	// draw the button-label
	dc.SetBackgroundMode( wxTRANSPARENT );
	dc.SetTextForeground( attr.GetTextColour() );
	dc.SetFont( attr.GetFont() );
	dc.DrawLabel( m_strLabel, rect,
				wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL); 
}


void CancelCellRender::Draw(wxGrid& grid,
                              wxGridCellAttr& attr,
                              wxDC& dc,
                              const wxRect& rect,
                              int row, int col,
                              bool isSelected)
{
    wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

    dc.SetPen(*wxRED_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
	int nY1 = rect.GetY() + rect.GetHeight() / 3;
	int nY2 = rect.GetY() + rect.GetHeight() * 2 / 3;
	dc.DrawLine(rect.GetLeft(), nY1 , rect.GetRight(), nY1);
	dc.DrawLine(rect.GetLeft(), nY2 , rect.GetRight(), nY2);
   // dc.DrawEllipse(rect);
}


//bool UserDataSaveTableBase::InsertRows(size_t pos /* = 0 */ , size_t numRows /* = 1 */)
//{
//	wxGridTableBase::InsertRows(pos, numRows);
//	return true;
//}
//
//bool UserDataSaveTableBase::AppendRows(size_t numRows /* = 1 */)
//{
//	wxGridTableBase::AppendRows(numRows);
//	return true;
//}
//
//bool UserDataSaveTableBase::DeleteRows(size_t pos /* = 0 */ , size_t numRows /* = 1 */)
//{
//	wxGridTableBase::DeleteRows(pos, numRows);
//	return true;
//}