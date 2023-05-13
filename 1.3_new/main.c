#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "./global.c"
#include "utils/matrix.c"
#include "utils/draw.c"

void DrawMainGraph(HWND hWnd, HDC hdc, int dir)
{
    float k = (1.0 - (int)(num_in_group/10)*0.02 - (int)(num_in_group%10)*0.005 - 0.25);
    char** Anames = getNames(MATRIX_MAX);
    float** A = createMatrixPreset(k, MATRIX_MAX);

    if(!dir){
        A = symMatrix(A, MATRIX_MAX);
    }
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);

    DrawGraph(hWnd, hdc, A, Acoords, MATRIX_MAX, dir, Anames);

    free(A);
    free(Anames);
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

    hWnd = CreateWindow(ProgName, "Lab 3. by Alexandr Potaskalov", 
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
            Button_matrix_dir = CreateWindow("BUTTON", "Directed Matrix [1]",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 20, 150, 30,
                                  hWnd, (HMENU) 1, NULL, NULL);
            Button_matrix_undir = CreateWindow("BUTTON", "Undirected Matrix [1]",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 60, 150, 30,
                                  hWnd, (HMENU) 2, NULL, NULL);
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
                        DrawMainGraph(hWnd, hdc, 1);
                        EndPaint(hWnd, &ps);
                    break;
                    case 2:
                        system("cls");
                        hdc = BeginPaint(hWnd, &ps);
                        ClearScreen(hdc, hWnd, ps);
                        DrawMainGraph(hWnd, hdc, 0);
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