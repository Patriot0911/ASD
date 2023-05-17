#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "./global.c"
#include "utils/matrix.c"
#include "utils/draw.c"

void DrawMainGraph(HWND hWnd, HDC hdc, int print)
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.15);
    char** Anames = getNames(MATRIX_MAX);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    if(print){
        printMatrix(A, MATRIX_MAX);
    }
    DrawGraph(hWnd, hdc, A, Acoords, MATRIX_MAX, 1, Anames);
    free(A);
    free(Anames);
    free(Acoords);
}

int DFS(int begin, int* visited, int* stack, float** A, int N){
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
                visited[i] = 1;
                PutToEnd(stack, N, i);
                return i;
            }
        }
    }
    return -1;
}

int* BFS(int begin, int* visited, float** A, int N) {
    int* queue = (int*)malloc(N * sizeof(int)); 
    int front = -1, rear = -1,
        cur;
    visited[begin] = 1;
    queue[++rear] = begin;
    while (front < rear) {
        cur = queue[++front];
        for (int i = 0; i < N; i++) {
            if (!visited[i] && A[cur][i]) {
                printf("%d -> %d\n", cur, i);
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
    return queue;
}



int DFSGraph(HWND hWnd, HDC hdc, int begin, int* visited, int* stack){
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.15);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);
    printf("DFS:\n");
    int next = DFS(begin, visited, stack, A, MATRIX_MAX);

    free(A);
    return next;
}

void BFSGraphMain(HWND hWnd, HDC hdc){
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.15);
    char** Anames = getNames(MATRIX_MAX);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    int* visited = (int*)malloc(MATRIX_MAX * sizeof(int));
    printMatrix(A, MATRIX_MAX);

    for(int i = 0; i < MATRIX_MAX; i++){
        visited[i] = 0;
    }
    printf("BFS:\n");
    int* bfs_list = BFS(0, visited, A, MATRIX_MAX);
    for(int i = 0; i < MATRIX_MAX; i++){
        printf("%d ", bfs_list[i]);
    }
    
    free(A);
    free(Anames);
    free(visited);
    free(Acoords);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow){
    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = WHITE_BRUSH;
    w.style = CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if(!RegisterClass(&w)) return 0;

    HWND hWnd;
    MSG lpMsg;

    hWnd = CreateWindow(ProgName, "Lab 5. by Alexandr Potaskalov", 
        WS_OVERLAPPEDWINDOW, 
        100, 100, 1200, 800,
        (HWND)NULL, (HMENU)NULL, 
        (HINSTANCE)hInstance, (HINSTANCE)NULL);
    ShowWindow(hWnd, nCmdShow);
    while(GetMessage(&lpMsg, hWnd, 0, 0)){
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }

    return(lpMsg.wParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    static int* visited = NULL;
    static int* stack = NULL;
    static int point = -1;
    static int button = 0;
    switch(messg){
        case WM_CREATE:
            visited = (int*)malloc(MATRIX_MAX * sizeof(int));
            stack = (int*)malloc(MATRIX_MAX * sizeof(int));

            Button_matrix_dir = CreateWindow("BUTTON", "Directed Matrix",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 20, 150, 30,
                                  hWnd, (HMENU) 1, NULL, NULL);
            Button_dfs_graph  = CreateWindow("BUTTON", "DFS Graph",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 60, 150, 30,
                                  hWnd, (HMENU) 2, NULL, NULL);
            Button_dfs_graph_next  = CreateWindow("BUTTON", "DFS Next",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 100, 150, 30,
                                  hWnd, (HMENU) 3, NULL, NULL);
        break;
        case WM_PAINT:
            UpdateWindow(hWnd);
        break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case 1:
                    if(button == LOWORD(wParam)) break;
                    system("cls");
                    hdc = BeginPaint(hWnd, &ps);
                    ClearScreen(hdc, hWnd, ps);
                    DrawMainGraph(hWnd, hdc, 1);
                    EndPaint(hWnd, &ps);
                    point = -1;
                break;
                case 2:
                    if(button == LOWORD(wParam)) break;
                    for(int i = 0; i < MATRIX_MAX; i++){
                        visited[i] = 0;
                        stack[i] = -1;
                    }
                    stack[0] = 0;
                    system("cls");
                    hdc = BeginPaint(hWnd, &ps);
                    ClearScreen(hdc, hWnd, ps);
                    point = DFSGraph(hWnd, hdc, 0, visited, stack);
                    EndPaint(hWnd, &ps);
                    PrintSingleMatrix(stack);
                break;
                case 3:
                    system("cls");
                    if(point == -1){
                        printf("Cannot continue DFS\n");
                        break;
                    }
                    hdc = BeginPaint(hWnd, &ps);
                    point = DFSGraph(hWnd, hdc, point, visited, stack);
                    EndPaint(hWnd, &ps);
                    if(point == -1){
                        printf("Cannot continue DFS\n");
                    }                    
                    PrintSingleMatrix(stack);
                break;
                default:
                break;
            }
            button = LOWORD(wParam);
        break;
        case WM_DESTROY:
            free(stack);
            free(visited);
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hWnd, messg, wParam, lParam);
    }
    return 0;

}