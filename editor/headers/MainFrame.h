#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#   include <wx/wx.h>
#endif

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "../headers/Canvas.h"
#include "../headers/Globals.h"

class MainFrame: public wxFrame
{
    public:
        MainFrame(wxWindow *parent,
               wxWindowID id,
               const wxString& title,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxASCII_STR(wxFrameNameStr));

    private:
        wxStatusBar* _statusBar = nullptr;
        wxSlider* _slider = nullptr;
        
        Canvas* _canvas = nullptr;

        void OnMenuNew(wxCommandEvent &evt);
        void OnMenuOpen(wxCommandEvent &evt);
        void OnMenuSave(wxCommandEvent &evt);
        void OnMenuExit(wxCommandEvent &evt);

        void OnZoomChange(wxCommandEvent& evt);
        void OnSelectTile(wxCommandEvent& evt);
        wxDECLARE_EVENT_TABLE();
};


#endif