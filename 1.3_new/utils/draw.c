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

void DrawGraph(HWND hWnd, HDC hdc, float** A, int** Acoords, int N, int dir, char** Anames){
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    float val = 92* M_PI /180;
    int r = 30, dtx = 8;
    for(int l = 0; l < N; l++){
        for(int f = 0; f < N; f++){
            if(A[l][f] == 1){
                SelectObject(hdc, KPen);
                if(l == f){
                    MoveToEx(hdc, Acoords[0][0], Acoords[0][1], NULL);
                    Arc(hdc, Acoords[l][0], Acoords[l][1]-r*2, Acoords[l][0]+r*2, Acoords[f][1], Acoords[f][0], Acoords[f][1], Acoords[l][0], Acoords[l][1]);
                }else{
                    if(dir == 1){
                        if((A[f][l] == 1 && l < f)){
                            MoveToEx(hdc, Acoords[l][0], Acoords[l][1], NULL);
                            LineTo(hdc, (Acoords[f][0]+Acoords[l][0])/2-r, (Acoords[f][1]+Acoords[l][1])/2-r);
                            LineTo(hdc, Acoords[f][0], Acoords[f][1]);
                            val = (atan2((Acoords[f][1]-((Acoords[f][1]+Acoords[l][1])/2-r)), (Acoords[f][0]-((Acoords[f][0]+Acoords[l][0])/2-r))));
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
                    arrow(val, (int)(Acoords[f][0]-r*cos(val)), (int)(Acoords[f][1]-r*sin(val)), hdc);                    
                    val = 92*M_PI/180;
                }
            }
        }
    }

    SelectObject(hdc, BPen);
    for(int l = 0; l < N; l++){
        MoveToEx(hdc, Acoords[l][0], Acoords[l][1], NULL);
        Ellipse(hdc, Acoords[l][0]-r, Acoords[l][1]-r, Acoords[l][0]+r, Acoords[l][1]+r);
        TextOut(hdc, Acoords[l][0]-dtx, Acoords[l][1]-r/2, Anames[l], 2);
    }
    free(Anames);
}