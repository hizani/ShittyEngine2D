#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#   include <wx/wx.h>
#endif

#ifndef APP_H
#define APP_H

#include "./Globals.h"
#include "./MainFrame.h"

class App : public wxApp
{
public:
	virtual bool OnInit();
};


wxDECLARE_APP(App);

#endif