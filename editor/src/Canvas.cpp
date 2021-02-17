#include "../headers/Canvas.h"
#include <fstream>


wxBEGIN_EVENT_TABLE(Canvas, wxHVScrolledWindow)
EVT_PAINT(Canvas::OnPaint)
EVT_LEFT_DOWN(Canvas::OnMouseLeftDown)
EVT_LEFT_UP(Canvas::OnMouseLeftUp)
EVT_MOTION(Canvas::OnMouseMoved)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(800,600))
{
    SetRowColumnCount(MAP_ROWS,MAP_COLUMNS);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    //создание массива карты
    delete[] _map;
    _map = new unsigned char*[MAP_ROWS];
    for(int i = 0; i < MAP_ROWS; i++)
        _map[i] = new unsigned char[MAP_COLUMNS];
    
    for(int i = 0; i < MAP_ROWS; i++)
        for(int j = 0; j < MAP_COLUMNS; j++)
            _map[i][j] = '0';
}

Canvas::~Canvas(){

}

void Canvas::SetTile(char id)
{
    _tileId = id;
}

void Canvas::SetPixelSize(int n)
{
    _pixelSize = n;
    wxVarHScrollHelper::RefreshAll();
    wxVarVScrollHelper::RefreshAll();
    Refresh();
}

wxCoord Canvas::OnGetRowHeight(size_t row) const
{
    return wxCoord(_pixelSize);
}

wxCoord Canvas::OnGetColumnWidth(size_t col) const
{
    return wxCoord(_pixelSize);
}

void Canvas::OnDraw(wxBufferedPaintDC &dc)
{
    dc.Clear();

    wxBrush brush = dc.GetBrush();
    wxPen pen = dc.GetPen();

    wxPosition begin = GetVisibleBegin();
    wxPosition end = GetVisibleEnd();

    pen.SetStyle(wxPENSTYLE_LONG_DASH);
    pen.SetColour(wxColour(200, 200, 200));
    dc.SetPen(pen);
    for (int y = begin.GetRow(); y < end.GetRow(); y++)
    {
        for (int x = begin.GetCol(); x < end.GetCol(); x++)
        {
            char tile = _map[y][x];

            if (tile >= '0' && tile <= '4')
            {
                int i = tile - '0';
                wxPoint topLeft(TILE_IMAGE_SIZE * i, 0);
                wxPoint bottomRight(TILE_IMAGE_SIZE * i + TILE_IMAGE_SIZE-1, TILE_IMAGE_SIZE-1);
                wxRect rect(topLeft, bottomRight);
                wxBitmap bmp = this->tileBitmap.GetSubBitmap(rect);

                wxImage image = bmp.ConvertToImage();
                bmp = wxBitmap(image.Scale(TILE_SIZE, TILE_SIZE));

                _selectedBitmap = bmp;
                dc.DrawBitmap(_selectedBitmap, x * _pixelSize, y * _pixelSize);
            }
            else
            {
                dc.SetBrush(brush);
                dc.DrawRectangle(x * _pixelSize, y * _pixelSize, _pixelSize, _pixelSize);
            }
        }
    }
}

void Canvas::WireteMap()
{
    std::fstream of("../core/assets/tilemaps/forest.map", std::ios::out | std::ios::out);
    if (of.is_open())
    {
        for (int i = 0; i < MAP_ROWS; ++i)
        {
            for (int j = 0; j < MAP_COLUMNS; ++j)
            {
                of << "0" << _map[i][j];
                if (j != MAP_COLUMNS - 1)
                    of << ",";
            }
            of << "\n";
        }
        of.close();
    }
}

void Canvas::OnPaint(wxPaintEvent& evt)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    this->OnDraw(dc);
}

void Canvas::OnMouseLeftDown(wxMouseEvent& evt)
{
    wxPosition s = GetVisibleBegin();
    int row = (evt.GetY() / _pixelSize + s.GetRow());
    int column = (evt.GetX() / _pixelSize + s.GetCol());
    if(row >= MAP_ROWS || row < 0 || column >= MAP_COLUMNS || column < 0)
    {
        evt.Skip();
        return;
    }
    std::cout << "Row:" << row << std::endl;
    std::cout << "Column: " << column << std::endl;
    _map[(evt.GetY() / _pixelSize + s.GetRow())][(evt.GetX() / _pixelSize + s.GetCol())] = _tileId;

    this->Refresh(false);
    isKeyPressed = true;
    evt.Skip();
}

void Canvas::OnMouseLeftUp(wxMouseEvent& evt)
{
    isKeyPressed = false;
    evt.Skip();
}

void Canvas::OnMouseMoved(wxMouseEvent& evt){
    if(isKeyPressed)
    {
        wxPosition s = GetVisibleBegin();
        int row = (evt.GetY() / _pixelSize + s.GetRow());
        int column = (evt.GetX() / _pixelSize + s.GetCol());
        if((row >= MAP_ROWS || row < 0) || (column >= MAP_COLUMNS || column < 0))
        {
            evt.Skip();
            return;
        }
        std::cout << "Row:" << row << std::endl;
        std::cout << "Column: " << column << std::endl;
        _map[(evt.GetY() / _pixelSize + s.GetRow())][(evt.GetX() / _pixelSize + s.GetCol())] = _tileId;

        this->Refresh(false);
    }
    evt.Skip();
}