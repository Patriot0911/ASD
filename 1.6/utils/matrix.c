void PrintSingleMatrix(int* A, int N, int plus){
    printf("{ ");
    for(int i = 0; i < N; i++){
        printf("%d ", A[i]+plus);
    }
    printf("}");
}

int** matrixWt(int N, int** A, float** T){
    int** Wt = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        Wt[i] = (int*)malloc(N * sizeof(int));
        for(int j = 0; j < N; j++){
            Wt[i][j] = round(T[i][j] * 100 * A[i][j]);
        }
    }
    return Wt;
}

int** addMatirx(int** A, int** B, int N){
    int** arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        arr[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            arr[i][j] = A[i][j] + B[i][j];
        }
    }
    return arr;
}

int** multelMatrix(int** A, int** B, int N){
    int** arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        arr[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            arr[i][j] = A[i][j] * B[i][j];
        }
    }
    return arr;
}

float** randm(int N){
    srand(SEED);
    float** arr = (float**)malloc(N * sizeof(float*));
    for(int i = 0; i < N; i++){
        arr[i] = (float*)malloc(N * sizeof(float));
        for(int l = 0; l < N; l++){
            arr[i][l] = (float)rand()/(float)(RAND_MAX)*2.0;
        }
    }
    return arr;
}

int** createMatrixPreset(float k, int N){
    srand(SEED);
    int** arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        arr[i] = (int*)malloc(N * sizeof(int));
        for(int l = 0; l < N; l++){
            arr[i][l] = (int)((float)rand()/(float)(RAND_MAX)*2.0*k < 1.0 ? 0 : 1);
        }
    }
    return arr;
}

int** symMatrix(int** A, int N){
    int** arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        arr[i] = (int*)malloc(N * sizeof(int));
        for(int j = 0; j < N; j++){
            if(A[i][j] == 1 || A[j][i] == 1){
                arr[i][j] = 1;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    return arr;
}

int** TringlBool(int N){
    int** arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        arr[i] = (int*)malloc(N * sizeof(int));
        for(int j = 0; j < N; j++){
            if(i < j){
                arr[i][j] = 1;
                continue;
            }
            arr[i][j] = 0;
        }
    }
    return arr;
}

void printMatrix(int** A, int N){
    for(int i = 0; i < N; i++){
        for(int f = 0; f < N; f++){
            printf("%d ", A[i][f]);
        }
        printf("\n");
    }
}

int** symelMatrix(int** A, int N){
    int** arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        arr[i] = (int*)malloc(N*sizeof(int));
        for(int k = 0; k < N; k++){
            if(A[i][k] == 0 && A[k][i] != 0){
                arr[i][k] = A[k][i];
            }else{
                arr[i][k] = A[i][k];
            }
        }
    }
    return arr;
}

int** CountW(int** A, int N){
    int** Wt = matrixWt(N, A, randm(MATRIX_MAX));
    int** Tr = TringlBool(N);
    int** B = (int**)malloc(N * sizeof(int*));
    int** D = (int**)malloc(N * sizeof(int*));
    int** C = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        B[i] = (int*)malloc(N * sizeof(int));
        for(int l = 0; l < N; l++){
            B[i][l] = Wt[i][l] == 0 ? 0 : 1;
        }
    }
    for(int i = 0; i < N; i++){
        C[i] = (int*)malloc(N * sizeof(int));
        for(int l = 0; l < N; l++){
            C[i][l] = B[i][l] == B[l][i] ? 0 : 1;
        }
    }
    for(int i = 0; i < N; i++){
        D[i] = (int*)malloc(N * sizeof(int));
        for(int l = 0; l < N; l++){
            D[i][l] = (B[i][l] == B[l][i] && B[i][l] == 1) ? 1 : 0;
        }
    }

    int** W = multelMatrix(D, Tr, MATRIX_MAX);
    W = addMatirx(C, W, MATRIX_MAX);
    W = multelMatrix(W, Wt, MATRIX_MAX);
    W = symelMatrix(W, MATRIX_MAX);

    free(B);
    free(D);
    free(C);
    free(Wt);    
    return W;
}

int PutToEnd(int* stack, int N, int a){
    for(int i = 0; i < N; i++){
        if(stack[i] == -1){
            stack[i] = a;
            return i;
        }
    }
    return -1;
}