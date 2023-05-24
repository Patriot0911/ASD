void ColorPath(int from, int to, Graph gr, HDC hdc){
    HPEN BPen = CreatePen(PS_SOLID, 3, RGB(50, 255, 55));
    SelectObject(hdc, BPen);
    int dtx = 8;
    Node* fnode = getNode(gr.node, gr.nodes, from);
    Node* tnode = getNode(gr.node, gr.nodes, to);
    if(from != to){
        MoveToEx(hdc, fnode->x, fnode->y, NULL);
        LineTo(hdc, tnode->x, tnode->y);
        Ellipse(hdc, tnode->x-sradius, tnode->y-sradius, tnode->x+sradius, tnode->y+sradius);
    }
    Ellipse(hdc, fnode->x-sradius, fnode->y-sradius, fnode->x+sradius, fnode->y+sradius);
    TextOut(hdc, fnode->x-dtx, fnode->y-sradius/2, fnode->name, 2);
    TextOut(hdc, tnode->x-dtx, tnode->y-sradius/2, tnode->name, 2);
}

void NameW(Graph gr, HDC hdc){
    int N = gr.nodes;
    Node* fnode = gr.node;
    Node* tnode = NULL;
    char str[3];
    HPEN BPen = CreatePen(PS_SOLID, 3, RGB(50, 255, 55));
    SelectObject(hdc, BPen);
    for(int i = 0; i < N; i++){
        for(int l = 0; l < N; l++){
            if(fnode->links[l]){
                tnode = getNode(gr.node, N, l);
                if(fnode->ws[l] < 10){
                    sprintf(str, "00%d", fnode->ws[l]);
                }else{
                    if(fnode->ws[l] < 100){
                        sprintf(str, "0%d", fnode->ws[l]);
                    }else{
                        sprintf(str, "%d", fnode->ws[l]);
                    }
                }
                TextOut(hdc, (int)((fnode->x+tnode->x)/2), (int)((fnode->y+tnode->y)/2), str, 3);
            }
        }
        fnode = fnode->next;
    }
}

void Prima(int* visited, int* stack, Graph gr, HDC hdc){
    int N = gr.nodes;
    Node* fnode = getNode(gr.node, N, 0);
    int w = -1;
    int nd[2] = {-1, -1};
    for(int i = 0; i < N; i++){
        if(visited[i]){
            for(int l = 0; l < N; l++){
                if(fnode->links[l] && !visited[l]){
                    if(fnode->ws[l] < w || nd[0] == -1){
                        w = fnode->ws[l];
                        nd[0] = fnode->key;
                        nd[1] = l;
                    }
                }
            }
        }
        fnode = fnode->next;
    }
    if(nd[0] == -1 || nd[1] == -1){
        if(stack[N-1] == -1){
            for(int i = 0; i < N; i++){
                if(!visited[i]){
                    visited[i] = 1;
                    PutToEnd(stack, N, i);
                    printf("\n%d->%d", i+1, i+1);
                    ColorPath(i, i, gr, hdc);
                    return;
                }
            }
        }
        printf("Cannt go futher");
        NameW(gr, hdc);
        return;
    }
    visited[nd[1]] = 1;
    PutToEnd(stack, N, nd[1]);
    printf("\n%d->%d", nd[0]+1, nd[1]+1);
    ColorPath(nd[0], nd[1], gr, hdc);
}