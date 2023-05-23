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

void DrawGraph(HWND hWnd, HDC hdc, int** A, int** Acoords, int N, int dir, char** Anames){
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    float val = 92* M_PI /180;
    int dtx = 8;
    for(int l = 0; l < N; l++){
        for(int f = 0; f < N; f++){
            if(A[l][f] == 1){
                SelectObject(hdc, KPen);
                if(l == f){
                    MoveToEx(hdc, Acoords[0][0], Acoords[0][1], NULL);
                    Arc(hdc, Acoords[l][0], Acoords[l][1]-sradius*2, Acoords[l][0]+sradius*2, Acoords[f][1], Acoords[f][0], Acoords[f][1], Acoords[l][0], Acoords[l][1]);
                }else{
                    if(dir == 1){
                        if((A[f][l] == 1 && l < f)){
                            MoveToEx(hdc, Acoords[l][0], Acoords[l][1], NULL);
                            LineTo(hdc, (Acoords[f][0]+Acoords[l][0])/2-sradius, (Acoords[f][1]+Acoords[l][1])/2-sradius);
                            LineTo(hdc, Acoords[f][0], Acoords[f][1]);
                            val = (atan2((Acoords[f][1]-((Acoords[f][1]+Acoords[l][1])/2-sradius)), (Acoords[f][0]-((Acoords[f][0]+Acoords[l][0])/2-sradius))));
                        }else{
                            MoveToEx(hdc, Acoords[l][0], Acoords[l][1], NULL);
                            LineTo(hdc, Acoords[f][0], Acoords[f][1]);
                            val = (atan2((Acoords[f][1]-Acoords[l][1]), (Acoords[f][0]-Acoords[l][0])));
                        }
                    }else if(dir == 0){
                        MoveToEx(hdc, Acoords[l][0], Acoords[l][1], NULL);
                        LineTo(hdc, Acoords[f][0], Acoords[f][1]);
                    }
                }
                if(dir == 1){
                    SelectObject(hdc, BPen);
                    arrow(val, (int)(Acoords[f][0]-sradius*cos(val)), (int)(Acoords[f][1]-sradius*sin(val)), hdc);
                    val = 92*M_PI/180;
                }
            }
        }
    }

    SelectObject(hdc, BPen);
    for(int l = 0; l < N; l++){
        MoveToEx(hdc, Acoords[l][0], Acoords[l][1], NULL);
        Ellipse(hdc, Acoords[l][0]-sradius, Acoords[l][1]-sradius, Acoords[l][0]+sradius, Acoords[l][1]+sradius);
        TextOut(hdc, Acoords[l][0]-dtx, Acoords[l][1]-sradius/2, Anames[l], 2);
    }
}