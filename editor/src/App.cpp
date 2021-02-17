#include "../headers/App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit(){
    MainFrame* MainWin = new MainFrame(nullptr, MAINWINDOW, "Editor", wxDefaultPosition, wxSize(800, 600));
    MainWin->Show();
    SetTopWindow(MainWin);
    return true;
}

