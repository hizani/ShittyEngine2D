#include "../headers/MainFrame.h"
#include <stdlib.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(10001, MainFrame::OnMenuNew)
EVT_MENU(10002, MainFrame::OnMenuOpen)
EVT_MENU(10003, MainFrame::OnMenuSave)
EVT_MENU(10004, MainFrame::OnMenuExit)
EVT_SLIDER(20001, MainFrame::OnZoomChange)
EVT_BUTTON(10020, MainFrame::OnSelectTile)
EVT_BUTTON(10021, MainFrame::OnSelectTile)
EVT_BUTTON(10022, MainFrame::OnSelectTile)
EVT_BUTTON(10023, MainFrame::OnSelectTile)
EVT_BUTTON(10024, MainFrame::OnSelectTile)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(wxWindow *parent,
               wxWindowID id,
               const wxString& title,
               const wxPoint& pos,
               const wxSize& size,
               long style,
               const wxString& name) : wxFrame(parent, id, title, pos, size ,style, name)
{
    //добавляем панели меню
    wxMenuBar* menuBar = new wxMenuBar();
    this->SetMenuBar(menuBar);
    //добавление элементов меню
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(10001, "Build");
    menuFile->Append(10003, "Save");
    menuFile->Append(10004, "Exit");
    //добавление меню к панели меню
    menuBar->Append(menuFile, "File");
    //Добавление панели состояния
    _statusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
    //Добавление слайдера
    _slider = new wxSlider(_statusBar, 20001, 8, 1, 32, wxDefaultPosition, wxDefaultSize); 
    //Настройка верстки
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL); //главный контейнер
    wxBoxSizer* leftMenuSizer = new wxBoxSizer(wxVERTICAL); //левое меню элементов
    wxGridSizer* tileMenuSizer = new wxGridSizer(4); //контейнер меню тайлов
    
    leftMenuSizer->Add(tileMenuSizer, 1, wxEXPAND); 
    mainSizer->Add(leftMenuSizer, 0);
    _canvas = new Canvas(this);
    mainSizer->Add(_canvas, 1, wxEXPAND, 0 );

    _canvas->tileBitmap.LoadFile(wxString("../core/assets/tilemaps/Grass.png"), wxBITMAP_DEFAULT_TYPE);

    for(int i = 0; i < 5; i++)
    {
        wxPoint topLeft(TILE_IMAGE_SIZE*i,0);
        wxPoint bottomRight(TILE_IMAGE_SIZE*i+TILE_IMAGE_SIZE-1,TILE_IMAGE_SIZE-1);
        wxRect rect(topLeft,bottomRight);
        wxBitmap bmp = _canvas->tileBitmap.GetSubBitmap(rect); 

        wxImage image = bmp.ConvertToImage();
        bmp = wxBitmap(image.Scale(TILE_SIZE, TILE_SIZE));
        
        wxButton* button = new wxButton(this, 10020 + i, wxEmptyString, wxDefaultPosition, wxSize(TILE_SIZE, TILE_SIZE), wxBORDER_NONE);
        button->SetBitmap(bmp);
        tileMenuSizer->Add(button);
        if(i == 0){
            _canvas->SetTile(static_cast<char>('0'+(button->GetId()-10020)));
        }
    }
    SetSizerAndFit(mainSizer);
}

void MainFrame::OnMenuNew(wxCommandEvent &evt){
   system("cd ../core && make run");
}

void MainFrame::OnMenuOpen(wxCommandEvent &evt){

}

void MainFrame::OnMenuSave(wxCommandEvent &evt)
{
    _canvas->WireteMap();
    evt.Skip();
}

void MainFrame::OnMenuExit(wxCommandEvent &evt){
    Close();
    evt.Skip();
}

void MainFrame::OnZoomChange(wxCommandEvent& evt)
{
    char str[3];
    sprintf(str, "%d", _slider->GetValue());
    _statusBar->SetStatusText(wxString(_("Zoom: ")) << wxString(_(str)), 1);
    _canvas->SetPixelSize(_slider->GetValue());
    evt.Skip();
}

void MainFrame::OnSelectTile(wxCommandEvent &evt){
    _canvas->SetTile(static_cast<char>('0'+(static_cast<wxButton*>(evt.GetEventObject())->GetId()-10020)));
    evt.Skip();
}