
void PrintSingleMatrix(int* A){
    printf("{ ");
    for(int i = 0; i < MATRIX_MAX; i++){
        printf("%d ", A[i]);
    }
    printf("}");
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

float** createMatrixPreset(float k, int N){
    srand(SEED);
    float** arr = (float**)malloc(N * sizeof(float*));
    for(int i = 0; i < N; i++){
        arr[i] = (float*)malloc(N * sizeof(float));
        for(int l = 0; l < N; l++){
            arr[i][l] = ((float)rand()/(float)(RAND_MAX/2.0)*k < 1.0 ? 0 : 1);
        }
    }
    return arr;
}

float** symMatrix(float** A, int N){
    float** arr = (float**)malloc(N * sizeof(float*));
    for(int i = 0; i < N; i++){
        arr[i] = (float*)malloc(N * sizeof(float));
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

void printMatrix(float** A, int N){
    for(int i = 0; i < N; i++){
        for(int f = 0; f < N; f++){
            printf("%0.f ", A[i][f]);
        }
        printf("\n");
    }
}

char** getNames(int N){
    char **Anames = (char**)malloc(N * sizeof(char*));
    for(int l = 0; l < N; l++){
        Anames[l] = (char*)malloc(2 * sizeof(char));
        if(l < 9){
            sprintf(Anames[l], "0%d", l+1);
        }else{
            sprintf(Anames[l], "%d", l+1);
        }
    }
    return Anames;
}

int** graphCoords(float** A, float a, int N){
    int** Acoords = (int**)malloc(N * sizeof(int*));
    float leng = a/(2*sin(180/(N-1)));

    for(int l = 0; l < N; l++){
        Acoords[l] = (int*)malloc(2 * sizeof(int));
        if(l == 0){
            Acoords[l][0] = startx;
            Acoords[l][1] = starty;
        }else{
            Acoords[l][0] = startx + leng * cos(2 * M_PI * l / (N-1));
            Acoords[l][1] = starty + leng * sin(2 * M_PI * l / (N-1));
        }
    }
    return Acoords;
}