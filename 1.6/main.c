#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "./global.c"
#include "utils/matrix.c"
#include "utils/nodes.c"
#include "utils/draw.c"
#include "utils/prima.c"

void DrawMainGraph(HWND hWnd, HDC hdc, int print)
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.05);
    int** A = createMatrixPreset(k, MATRIX_MAX);
    int** W = CountW(A, MATRIX_MAX);
    A = symMatrix(A, MATRIX_MAX);

    Node* fnode = createLinkedNodesBasedOn(A, W, MATRIX_MAX, 0);
    fnode = addCoordsToNodes(fnode, MATRIX_MAX, 400);
    printNodes(fnode, MATRIX_MAX);

    Graph gr = { MATRIX_MAX, fnode };

    printMatrix(W, MATRIX_MAX);
    printf("\n");
    printMatrix(A, MATRIX_MAX);

    DrawGraphGR(hWnd, hdc, gr);

    free(A);
    free(W);
    free(fnode);
}
void StartPrimaGraph(HWND hWnd, HDC hdc, int* visited, int* stack)
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.05);
    int** A = createMatrixPreset(k, MATRIX_MAX);
    int** W = CountW(A, MATRIX_MAX);
    A = symMatrix(A, MATRIX_MAX);
    
    for(int i = 0; i < MATRIX_MAX; i++){
        visited[i] = 0;
        stack[i] = -1;
    }
    visited[0] = 1;
    stack[0] = 0;

    Node* fnode = createLinkedNodesBasedOn(A, W, MATRIX_MAX, 0);
    fnode = addCoordsToNodes(fnode, MATRIX_MAX, 400);
    printNodes(fnode, MATRIX_MAX);

    Graph gr = { MATRIX_MAX, fnode };

    printf("\n");
    DrawGraphGR(hWnd, hdc, gr);
    Prima(visited, stack, gr, hdc);
    printf("\n\n");
    printMatrix(W, MATRIX_MAX);

    free(A);
    free(W);
}

void PrimaNext(HWND hWnd, HDC hdc, int* visited, int* stack)
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.05);
    int** A = createMatrixPreset(k, MATRIX_MAX);
    int** W = CountW(A, MATRIX_MAX);
    A = symMatrix(A, MATRIX_MAX);

    Node* fnode = createLinkedNodesBasedOn(A, W, MATRIX_MAX, 0);
    fnode = addCoordsToNodes(fnode, MATRIX_MAX, 400);

    Graph gr = { MATRIX_MAX, fnode };

    printNodes(fnode, MATRIX_MAX);
    printf("\n\n");
    printMatrix(W, MATRIX_MAX);
    printf("\n\n");
    Prima(visited, stack, gr, hdc);
    printf("\n");
    PrintSingleMatrix(stack, MATRIX_MAX, 1);
    printf("\n\n");
    PrintSingleMatrix(visited, MATRIX_MAX, 0);

    free(A);
    free(W);
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

    hWnd = CreateWindow(ProgName, "Lab 6. by Alexandr Potaskalov", 
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
    static int graph = -1;
    switch(messg){
        case WM_CREATE:
            visited = (int*)malloc(MATRIX_MAX * sizeof(int));
            stack = (int*)malloc(MATRIX_MAX * sizeof(int));

            Button_matrix = CreateWindow("BUTTON", "Main Graph",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 20, 150, 30,
                                  hWnd, (HMENU) 1, NULL, NULL);
            Button_matrix_Prima_start = CreateWindow("BUTTON", "Prima Start",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 60, 150, 30,
                                  hWnd, (HMENU) 2, NULL, NULL);
            Button_matrix_Prima = CreateWindow("BUTTON", "Prima Next",
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
                    system("cls");
                    hdc = BeginPaint(hWnd, &ps);
                    ClearScreen(hdc, hWnd, ps);
                    DrawMainGraph(hWnd, hdc, 1);
                    EndPaint(hWnd, &ps);
                    graph = 0;
                break;
                case 2:
                    system("cls");
                    hdc = BeginPaint(hWnd, &ps);
                    ClearScreen(hdc, hWnd, ps);
                    StartPrimaGraph(hWnd, hdc, visited, stack);
                    EndPaint(hWnd, &ps);
                    graph = 1;
                break;
                case 3:
                    if(graph != 1) break;
                    system("cls");
                    InvalidateRect(hWnd, NULL, TRUE);
                    hdc = BeginPaint(hWnd, &ps);
                    PrimaNext(hWnd, hdc, visited, stack);
                    EndPaint(hWnd, &ps);
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