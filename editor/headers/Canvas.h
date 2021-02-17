#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#   include <wx/wx.h>
#endif

#ifndef CANVAS_H
#define CANVAS_H

#include "wx/vscroll.h"
#include <wx/dcbuffer.h>

#include "../headers/Globals.h"

class Canvas : public wxHVScrolledWindow
{
    public:
        Canvas(wxWindow *parent);
        ~Canvas();
        
        wxBitmap tileBitmap;

        void SetTile(char);
        //Установка размера тайла
        void SetPixelSize(int n);
        //Запись карты в файл
        void WireteMap();

    private:
        int _pixelSize = 32;
        wxBitmap _selectedBitmap;
        
        char _tileId;
        unsigned char** _map = nullptr;

        virtual wxCoord OnGetRowHeight(size_t row) const;
        virtual wxCoord OnGetColumnWidth(size_t col) const;


        bool isKeyPressed = false;
        void OnDraw(wxBufferedPaintDC& dc);
        void OnPaint(wxPaintEvent& evt);
        void OnMouseLeftDown(wxMouseEvent& evt);
        void OnMouseLeftUp(wxMouseEvent& evt);
        void OnMouseMoved(wxMouseEvent& evt);
        wxDECLARE_EVENT_TABLE();
};

#endif