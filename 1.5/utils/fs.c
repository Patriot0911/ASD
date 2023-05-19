int DFS(int begin, int* visited, int* stack, float** A, int N, HWND hWnd, HDC hdc){
    if(visited[begin]){
        int reslt = -1;
        for(int i = 0; i < N; i++){
            if(i == N-1 && stack[i] == begin){
                reslt = 0;
                break;
            }
            if(stack[i] == begin && stack[i+1] == -1){
                reslt = 1;
                break;
            }
        }
        switch (reslt)
        {
            case 0:
                for(int i = 0; i < N; i++){
                    for(int l = 0; l < N; l++){
                        if(A[stack[i]][l] && !visited[l]){
                            printf("\n%d -> %d\n", stack[i], l);
                            DrawLined(hWnd, hdc, A, N, stack[i], l);
                            ColorPeaks(hWnd, hdc, stack[i], N, 0);
                            ColorPeaks(hWnd, hdc, l, N, 1);
                            visited[l] = 1;
                            PutToEnd(stack, N, l);
                            return l;
                        }
                    }
                }
            break;
            case 1:
                for(int l = 0; l < N; l++){
                    if(A[begin][l] && !visited[l]){
                        printf("\n%d -> %d\n", begin, l);
                        DrawLined(hWnd, hdc, A, N, begin, l);
                        ColorPeaks(hWnd, hdc, begin, N, 0);
                        ColorPeaks(hWnd, hdc, l, N, 1);
                        visited[l] = 1;
                        PutToEnd(stack, N, l);
                        return l;
                    }
                }
                for(int i = 0; i < N; i++){
                    if(stack[i] == -1) return -1;
                    if(stack[i] != begin){
                        for(int l = 0; l < N; l++){
                            if(A[stack[i]][l] && !visited[l]){
                                printf("\n%d -> %d\n", stack[i], l);
                                DrawLined(hWnd, hdc, A, N, stack[i], l);
                                ColorPeaks(hWnd, hdc, begin, N, 0);
                                ColorPeaks(hWnd, hdc, stack[i], N, 0);
                                ColorPeaks(hWnd, hdc, l, N, 1);
                                visited[l] = 1;
                                PutToEnd(stack, N, l);
                                return l;
                            }
                        }
                    }
                }
            break;
            default:
            return -1;
        }
    }else{
        visited[begin] = 1;
        for(int i = 0; i < N; i++){
            if(A[begin][i] && !visited[i]){
                printf("\n%d -> %d\n", begin, i);
                DrawLined(hWnd, hdc, A, N, begin, i);
                visited[i] = 1;
                PutToEnd(stack, N, i);
                ColorPeaks(hWnd, hdc, begin, N, 0);
                ColorPeaks(hWnd, hdc, i, N, 1);
                return i;
            }
        }
    }
    return -1;
}

int BFS(int begin, int* visited, int* stack, float** A, int N, HWND hWnd, HDC hdc) {
    if(visited[begin]){
        for(int i = 0; i < N; i++){
            if(A[begin][i] && !visited[i]){
                printf("\n%d -> %d\n", begin, i);
                DrawLined(hWnd, hdc, A, N, begin, i);
                ColorPeaks(hWnd, hdc, begin, N, 1);
                ColorPeaks(hWnd, hdc, i, N, 0);
                visited[i] = 1;
                PutToEnd(stack, N, i);
                return begin;
            }
        }
        for(int i = 0; i < N; i++){
            if(i == begin || !visited[i]) continue;
            for(int l = 0; l < N; l++){
                if(A[i][l] && !visited[l]){
                    printf("\n%d -> %d\n", i, l);
                    DrawLined(hWnd, hdc, A, N, i, l);
                    ColorPeaks(hWnd, hdc, begin, N, 0);
                    ColorPeaks(hWnd, hdc, i, N, 1);
                    ColorPeaks(hWnd, hdc, l, N, 0);
                    visited[l] = 1;
                    PutToEnd(stack, N, i);
                    return i;
                }
            }
        }
        for(int i = 0; i < N; i++){
            if(visited[i] || i == begin) continue;
            for(int l = 0; l < N; l++){
                if(A[i][l] && !visited[l]){
                    printf("\n%d -> %d\n222", i, l);
                    DrawLined(hWnd, hdc, A, N, i, l);
                    ColorPeaks(hWnd, hdc, i, N, 1);
                    ColorPeaks(hWnd, hdc, l, N, 0);
                    visited[l] = 1;
                    PutToEnd(stack, N, i);
                    return i;
                }
            }
            for(int k = 0; k < N; k++){
                if(A[k][i]){
                    break;
                }
            }
            printf("\n%d -> %d\n", i, i);
            ColorPeaks(hWnd, hdc, i, N, 0);
            PutToEnd(stack, N, i);
            return i;
        }
    }else{
        visited[begin] = 1;
        for(int l = 0; l < MATRIX_MAX; l++){
            if(A[begin][l] && !visited[l]){
                printf("\n%d -> %d\n", begin, l);
                ColorPeaks(hWnd, hdc, begin, N, 1);
                ColorPeaks(hWnd, hdc, l, N, 0);
                DrawLined(hWnd, hdc, A, N, begin, l);
                visited[l] = 1;
                PutToEnd(stack, N, l);
                return begin;
            }
        }
    }
    return -1;
}