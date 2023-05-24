void ClearScreen(HDC hdc, HWND hWnd, PAINTSTRUCT ps){
    InvalidateRect(hWnd, NULL, TRUE);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hdc, &ps.rcPaint, hBrush);
}

void arrow(float fi, int px, int py, HDC hdc){
    int lx, ly, rx, ry;
    lx = px - 15 * cos(fi + 0.3);
    rx = px - 15 * cos(fi - 0.3);
    ly = py - 15 * sin(fi + 0.3);
    ry = py - 15 * sin(fi - 0.3);
    MoveToEx(hdc, px, py, NULL);
    LineTo(hdc, lx, ly);
    MoveToEx(hdc, px, py, NULL);
    LineTo(hdc, rx, ry);
}

void ColorPeaks(HWND hWnd, HDC hdc, int peak, int N, int type){
    HPEN Pen;
    switch (type)
    {
        case 0:
            Pen = CreatePen(PS_SOLID, 3, RGB(255, 20, 105));
        break;
        case 1:
            Pen = CreatePen(PS_SOLID, 3, RGB(20, 255, 105));
        break;
        default:
        return;
    }
    int** Acoords = graphCoords(300, N);
    SelectObject(hdc, Pen);
    if(peak == -1){
        for(int i = 0; i < N; i++){
            Ellipse(hdc, Acoords[i][0]-sradius, Acoords[i][1]-sradius, Acoords[i][0]+sradius, Acoords[i][1]+sradius);
        }
        return;
    }
    Ellipse(hdc, Acoords[peak][0]-sradius, Acoords[peak][1]-sradius, Acoords[peak][0]+sradius, Acoords[peak][1]+sradius);
}

void NamePeaks(HWND hWnd, HDC hdc, int N){
    char** Anames = getNames(N);
    int** Acoords = graphCoords(300, N);
    for(int l = 0; l < N; l++){
        MoveToEx(hdc, Acoords[l][0], Acoords[l][1], NULL);
        TextOut(hdc, Acoords[l][0]-8, Acoords[l][1]-sradius/2, Anames[l], 2);
    }
    free(Acoords);
    free(Anames);
}

void DrawLined(HWND hWnd, HDC hdc, float** A, int N, int begin, int end){
    int** Acoords = graphCoords(300, MATRIX_MAX);
    float val = 92* M_PI /180;
    HPEN RPen = CreatePen(PS_SOLID, 4, RGB(250, 0, 150));
    SelectObject(hdc, RPen);
    val = (atan2((Acoords[end][1]-Acoords[begin][1]), (Acoords[end][0]-Acoords[begin][0])));
    MoveToEx(hdc, Acoords[begin][0], Acoords[begin][1], NULL);
    LineTo(hdc, (int)(Acoords[end][0]-sradius*cos(val)), (int)(Acoords[end][1]-sradius*sin(val)));
    arrow(val, (int)(Acoords[end][0]-sradius*cos(val)), (int)(Acoords[end][1]-sradius*sin(val)), hdc);
    val = 92*M_PI/180;
    free(Acoords);
}

void DrawGraphGR(HWND hWnd, HDC hdc, Graph gr, int dir){
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    float val = 92* M_PI /180;
    int dtx = 8;
    Node* list = gr.list;
    int N = gr.nodes;
    for(int l = 0; l < N; l++){
        for(int f = 0; f < N; f++){
            if(list[l].links[f] == 1){
                SelectObject(hdc, KPen);
                if(l == f){
                    MoveToEx(hdc, list[0].x, list[0].y, NULL);
                    Arc(hdc, list[l].x, list[l].y-sradius*2, list[l].x+sradius*2, list[f].y, list[f].x, list[f].y, list[l].x, list[l].y);                
                }else{
                    if(dir == 1){
                        if(list[f].links[l] == 1 && l < f){
                            MoveToEx(hdc, list[l].x, list[l].y, NULL);
                            LineTo(hdc, (list[f].x+list[l].x)/2-sradius, (list[f].y+list[l].y)/2-sradius);
                            LineTo(hdc, list[f].x, list[f].y);
                            val = (atan2((list[f].y-((list[f].y+list[l].y)/2-sradius)), (list[f].x-((list[f].x+list[l].x)/2-sradius))));
                        }else{
                            MoveToEx(hdc, list[l].x, list[l].y, NULL);
                            LineTo(hdc, list[f].x, list[f].y);
                            val = (atan2((list[f].y-list[l].y), (list[f].x-list[l].x)));
                        }
                    }else if(dir == 0){
                        MoveToEx(hdc, list[l].x, list[l].y, NULL);
                        LineTo(hdc, list[f].x, list[f].y);
                    }
                }
                if(dir == 1){
                    SelectObject(hdc, BPen);
                    arrow(val, (int)(list[f].x-sradius*cos(val)), (int)(list[f].y-sradius*sin(val)), hdc);
                    val = 92*M_PI/180;
                }
            }
        }
    }

    SelectObject(hdc, BPen);
    for(int l = 0; l < N; l++){
        MoveToEx(hdc, list[l].x, list[l].y, NULL);
        Ellipse(hdc, list[l].x-sradius, list[l].y-sradius, list[l].x+sradius, list[l].y+sradius);
        TextOut(hdc, list[l].x-dtx, list[l].y-sradius/2, list[l].name, 2);
    }
    free(list);
}