#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "globals.c"
#include "utils/matrix.c"
#include "utils/draw.c"


void StronglyConnectedComponents(HWND hWnd, HDC hdc){
    float k = (1.0 - (int)(num_in_group/10)*0.005 - (int)(num_in_group%10)*0.005 - 0.27);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    char** Anames = getNames(MATRIX_MAX);
    DrawGraph(hWnd, hdc, A, Acoords, MATRIX_MAX, 1, Anames);
    int count = stronglyConnected(hWnd, hdc, A, MATRIX_MAX);
    ColorPeaks(hWnd, hdc, MATRIX_MAX, Anames, Acoords, count);
    TextOut(hdc, startx-40, starty-starty/1.5, "Condensation graph", 18);
    free(A);
    free(Acoords);
    free(Anames);
    free(components);
}



void ReachMatrix( ){
    float k = (1.0 - (int)(num_in_group/10)*0.005 - (int)(num_in_group%10)*0.005 - 0.27);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    float** AAccess = CreateReachabilityMatrix(A, MATRIX_MAX);
    printMatrix(AAccess, MATRIX_MAX);

    free(AAccess);
    free(A);
}

void MainFindPaths( ){
    float k = (1.0 - (int)(num_in_group/10)*0.005 - (int)(num_in_group%10)*0.005 - 0.27);
    float** A            = createMatrixPreset(k, MATRIX_MAX);
    float** poweredA2    = powerMatrix(A, 2, MATRIX_MAX);
    float** poweredA3    = powerMatrix(A, 3, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);
    printf("\nA^2:\n");
    printMatrix(poweredA2, MATRIX_MAX);
    printf("\nPathes[2]:\n");

    for(int i = 0; i < MATRIX_MAX; i++){
        for(int l = 0; l < MATRIX_MAX; l++){
            if(poweredA2[i][l]){
                FindPath(A, MATRIX_MAX, i, l, 2);
            }
        }
        printf("\n");
    }
    printf("\nA^3:\n");
    printMatrix(poweredA3, MATRIX_MAX);
    printf("\nPathes[3]:\n");
    for(int i = 0; i < MATRIX_MAX; i++){
        for(int l = 0; l < MATRIX_MAX; l++){
            if(poweredA3[i][l]){
                FindPath(A, MATRIX_MAX, i, l, 3);
            }
        }
        printf("\n");
    }
    free(poweredA2);
    free(poweredA3);
    free(A);
}

void DrawModGraph(HWND hWnd, HDC hdc){
    float k = (1.0 - (int)(num_in_group/10)*0.005 - (int)(num_in_group%10)*0.005 - 0.27);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    int* degA;
    int* degAout;
    char** Anames = getNames(MATRIX_MAX);
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);

    degAout = degMatrixOut(A, MATRIX_MAX, hdc, Anames);
    degA = degMatrixIn(A, MATRIX_MAX, hdc, Anames);
    DrawGraph(hWnd, hdc, A, Acoords, MATRIX_MAX, 1, Anames);

    free(A);
    free(Acoords);
    free(degA);
    free(degAout);
    free(Anames);    
}

void DrawMainGraph(HWND hWnd, HDC hdc, int dir)
{
    float k = (1.0 - (int)(num_in_group/10)*0.01 - (int)(num_in_group%10)*0.01 - 0.3);
    int* degA;
    int* degAout;
    char** Anames = getNames(MATRIX_MAX);
    float** A = createMatrixPreset(k, MATRIX_MAX);
    if(!dir){
        A = symMatrix(A, MATRIX_MAX);
        degA = degMatrix(A, MATRIX_MAX, hdc);
        checkRegular(degA, MATRIX_MAX, hdc);
        findSingalorIsolated(degA, MATRIX_MAX, hdc, Anames);
    }else if(dir == 1){
        degAout = degMatrixOut(A, MATRIX_MAX, hdc, Anames);
        degA = degMatrixIn(A, MATRIX_MAX, hdc, Anames);
        checkRegularbyOut(degAout, MATRIX_MAX, hdc);
        checkRegularbyIn(degA, MATRIX_MAX, hdc);
        findSingalorIsolatedbyInOut(degA, degAout, MATRIX_MAX, hdc, Anames);
    }
    int** Acoords = graphCoords(A, 300, MATRIX_MAX);
    printMatrix(A, MATRIX_MAX);

    DrawGraph(hWnd, hdc, A, Acoords, MATRIX_MAX, dir, Anames);
    
    free(A);
    free(Acoords);
    free(degA);
    free(degAout);
    free(Anames);
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

    hWnd = CreateWindow(ProgName, "Lab 4. by Alexandr Potaskalov", 
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
            Button_matrix_modif = CreateWindow("BUTTON", "Modified Matrix",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 100, 150, 30,
                                  hWnd, (HMENU) 3, NULL, NULL);
            Button_pathes       = CreateWindow("BUTTON", "Modified pathes",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 140, 150, 30,
                                  hWnd, (HMENU) 4, NULL, NULL);
            Button_access       = CreateWindow("BUTTON", "Matrix of Reachability",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 180, 150, 30,
                                  hWnd, (HMENU) 5, NULL, NULL);
            Button_strong       = CreateWindow("BUTTON", "Strongly Matrix",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  20, 220, 150, 30,
                                  hWnd, (HMENU) 6, NULL, NULL);
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
                        graph = 1;
                    break;
                    case 2:
                        system("cls");
                        hdc = BeginPaint(hWnd, &ps);
                        ClearScreen(hdc, hWnd, ps);
                        DrawMainGraph(hWnd, hdc, 0);
                        EndPaint(hWnd, &ps);
                        graph = 2;
                    break;
                    case 3:
                        system("cls");
                        hdc = BeginPaint(hWnd, &ps);
                        ClearScreen(hdc, hWnd, ps);
                        DrawModGraph(hWnd, hdc);
                        EndPaint(hWnd, &ps);
                        graph = 3;
                    break;
                    case 4:
                        if(graph == 3){
                            system("cls");
                            MainFindPaths( );
                        }else{
                            printf("\nMake Mod Graph first");
                        }
                    break;
                    case 5:
                        if(graph == 3){
                            system("cls");
                            ReachMatrix( );
                        }else{
                            printf("\nMake Mod Graph first");
                        }
                    break;
                    case 6:
                        system("cls");
                        hdc = BeginPaint(hWnd, &ps);
                        ClearScreen(hdc, hWnd, ps);
                        StronglyConnectedComponents(hWnd, hdc);
                        EndPaint(hWnd, &ps);
                        graph = 4;
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