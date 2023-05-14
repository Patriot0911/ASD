#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "./global.c"
#include "utils/matrix.c"
#include "utils/draw.c"

void DrawMainGraph(HWND hWnd, HDC hdc)
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.15);
    char** Anames = getNames(MATRIX_MAX);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);

    DrawGraph(hWnd, hdc, A, Acoords, MATRIX_MAX, 1, Anames);

    free(A);
    free(Anames);
    free(Acoords);
}

void DFS(int begin, int* visited, float** A, int N) {
    visited[begin] = 1;
    for (int i = 0; i < N; i++) {
        if (!visited[i] && A[begin][i]) {
            printf("%d -> %d\n", begin, i);
            DFS(i, visited, A, N);
        }
    }
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


void DFSGraphMain(HWND hWnd, HDC hdc){
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.15);
    char** Anames = getNames(MATRIX_MAX);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);

    int* visited = (int*)malloc(MATRIX_MAX * sizeof(int));
    for(int i = 0; i < MATRIX_MAX; i++){
        visited[i] = 0;
    }
    printf("DFS:\n");
    DFS(0, visited, A, MATRIX_MAX);

    
    free(A);
    free(Anames);
    free(visited);
    free(Acoords);
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
    switch(messg){
        case WM_CREATE:
            Button_matrix_dir = CreateWindow("BUTTON", "Directed Matrix",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 20, 150, 30,
                                  hWnd, (HMENU) 1, NULL, NULL);
            Button_dfs_graph  = CreateWindow("BUTTON", "DFS Graph",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 60, 150, 30,
                                  hWnd, (HMENU) 2, NULL, NULL);
            Button_bfs_graph  = CreateWindow("BUTTON", "BFS Graph",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 100, 150, 30,
                                  hWnd, (HMENU) 3, NULL, NULL);
        break;
        case WM_PAINT:
            UpdateWindow(hWnd);
        break;
        case WM_COMMAND:
            if(lastbutton != LOWORD(wParam)){
                switch (LOWORD(wParam))
                {
                    case 1:
                        system("cls");
                        hdc = BeginPaint(hWnd, &ps);
                        ClearScreen(hdc, hWnd, ps);
                        DrawMainGraph(hWnd, hdc);
                        EndPaint(hWnd, &ps);
                    break;
                    case 2:
                        system("cls");
                        hdc = BeginPaint(hWnd, &ps);
                        ClearScreen(hdc, hWnd, ps);
                        DFSGraphMain(hWnd, hdc);
                        EndPaint(hWnd, &ps);
                    break;
                    case 3:
                        system("cls");
                        hdc = BeginPaint(hWnd, &ps);
                        ClearScreen(hdc, hWnd, ps);
                        BFSGraphMain(hWnd, hdc);
                        EndPaint(hWnd, &ps);
                    break;
                    default:
                    break;
                }
                lastbutton = LOWORD(wParam);
            }

        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, messg, wParam, lParam);
    }
    return 0;

}