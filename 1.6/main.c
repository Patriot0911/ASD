#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "./global.c"
#include "utils/matrix.c"
#include "utils/draw.c"

void DrawMainGraph(HWND hWnd, HDC hdc, int print)
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.005 - 0.05);
    int** A = createMatrixPreset(k, MATRIX_MAX);
    int** W = CountW(A, MATRIX_MAX);
    A = symMatrix(A, MATRIX_MAX);

    Node* list = createListBasedOn(A, W, MATRIX_MAX);
    list = addCoordsToList(list, MATRIX_MAX, 400);
    Graph gr = { MATRIX_MAX, list };

    printMatrix(W, MATRIX_MAX);
    printf("\n");
    printMatrix(A, MATRIX_MAX);

    DrawGraphGR(hWnd, hdc, gr, 0);

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
    static int graph = -1;
    switch(messg){
        case WM_CREATE:
            visited = (int*)malloc(MATRIX_MAX * sizeof(int));
            stack = (int*)malloc(MATRIX_MAX * sizeof(int));

            Button_matrix = CreateWindow("BUTTON", "Main Graph",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 20, 150, 30,
                                  hWnd, (HMENU) 1, NULL, NULL);
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
                    graph = 0;
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