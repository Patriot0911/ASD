#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "./global.c"
#include "utils/matrix.c"
#include "utils/draw.c"
#include "utils/fs.c"

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


int* BFS(int begin, int* visited, float** A, int N) {

}
int BFSGraph(HWND hWnd, HDC hdc, int begin, int* visited, int* stack){
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.15);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);
    printf("DFS:\n");
    // int next = BFS(begin, visited, stack, A, MATRIX_MAX, hWnd, hdc);

    free(A);
    return next;
}

int DFSGraph(HWND hWnd, HDC hdc, int begin, int* visited, int* stack){
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.15);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);
    printf("DFS:\n");
    int next = DFS(begin, visited, stack, A, MATRIX_MAX, hWnd, hdc);

    free(A);
    return next;
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
                                  180, 60, 150, 30,
                                  hWnd, (HMENU) 3, NULL, NULL);
            Button_bfs_graph  = CreateWindow("BUTTON", "BFS Graph",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 100, 150, 30,
                                  hWnd, (HMENU) 4, NULL, NULL);
            Button_bfs_graph_next  = CreateWindow("BUTTON", "BFS Next",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  180, 100, 150, 30,
                                  hWnd, (HMENU) 5, NULL, NULL);
        break;
        case WM_PAINT:
            UpdateWindow(hWnd);
        break;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case 1:
                    system("cls");
                    hdc = BeginPaint(hWnd, &ps);
                    ClearScreen(hdc, hWnd, ps);
                    DrawMainGraph(hWnd, hdc, 1);
                    EndPaint(hWnd, &ps);
                    point = -1;
                break;
                case 2:
                    for(int i = 0; i < MATRIX_MAX; i++){
                        visited[i] = 0;
                        stack[i] = -1;
                    }
                    stack[0] = 0;
                    system("cls");
                    hdc = BeginPaint(hWnd, &ps);
                    ClearScreen(hdc, hWnd, ps);
                    DrawMainGraph(hWnd, hdc, 0);
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
                    InvalidateRect(hWnd, NULL, TRUE);
                    hdc = BeginPaint(hWnd, &ps);
                    point = DFSGraph(hWnd, hdc, point, visited, stack);
                    EndPaint(hWnd, &ps);
                    if(point == -1){
                        printf("Cannot continue DFS\n");
                    }
                    PrintSingleMatrix(stack);
                break;

                /* BFS */
                case 4:
                    for(int i = 0; i < MATRIX_MAX; i++){
                        visited[i] = 0;
                        stack[i] = -1;
                    }
                    stack[0] = 0;
                    system("cls");
                    hdc = BeginPaint(hWnd, &ps);
                    ClearScreen(hdc, hWnd, ps);
                    DrawMainGraph(hWnd, hdc, 0);
                    point = BFSGraph(hWnd, hdc, 0, visited, stack);
                    EndPaint(hWnd, &ps);
                    PrintSingleMatrix(stack);
                break;
                default:
                break;
            }
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