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
                return i;
            }
        }
    }
    return -1;
}