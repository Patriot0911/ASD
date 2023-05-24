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

void DrawGraphGR(HWND hWnd, HDC hdc, Graph gr){
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    float val = 92* M_PI /180;
    int dtx = 8;
    int N = gr.nodes;
    Node* fnode = getNode(gr.node, N, 0);
    Node* tonode = NULL;
    for(int l = 0; l < N; l++){
        for(int f = 0; f < N; f++){
            if(fnode->links[f] == 1){
                tonode = getNode(fnode, N, f);
                SelectObject(hdc, KPen);
                if(l == f){
                    MoveToEx(hdc, gr.node->x, gr.node->y, NULL);
                    Arc(hdc, fnode->x, fnode->y-sradius*2, fnode->x+sradius*2, tonode->y, tonode->x, tonode->y, fnode->x, fnode->y);          
                }else{
                    MoveToEx(hdc, fnode->x, fnode->y, NULL);
                    LineTo(hdc, tonode->x, tonode->y);
                }
            }
        }
        fnode = fnode->next;
    }

    fnode = getNode(fnode, N, 0);
    SelectObject(hdc, BPen);
    for(int l = 0; l < N; l++){
        MoveToEx(hdc, fnode->x, fnode->y, NULL);
        Ellipse(hdc, fnode->x-sradius, fnode->y-sradius, fnode->x+sradius, fnode->y+sradius);
        TextOut(hdc, fnode->x-dtx, fnode->y-sradius/2, fnode->name, 2);
        fnode = fnode->next;
    }
}