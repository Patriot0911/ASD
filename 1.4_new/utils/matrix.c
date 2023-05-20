
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

int** graphCoords(float a, int N){
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

int* degMatrix(float** A, int N, HDC hdc){
    /* For Undirected */
    int* degA = (int*)malloc(N * sizeof(int));
    char buffer[8];
    TextOut(hdc, 200, 10, "Degs:", 5);
    for(int i = 0; i< N; i++){
        degA[i] = 0;
        for(int l = 0; l < N; l++){
            if(A[i][l] == 1){
                ++degA[i];
            }
        }
        if(i < 9){
            sprintf(buffer, "0%d: %d", i+1, degA[i]);
        }else{
            sprintf(buffer, "%d: %d", i+1, degA[i]);
        }
        TextOut(hdc, 200, 40+20*i, buffer, strlen(buffer));
    }
    return degA;
}

int* degMatrixOut(float** A, int N, HDC hdc, char** Anames){
    int* degAout = (int*)malloc(N * sizeof(int));
    char buffer[8];
    TextOut(hdc, 200, 10, "Degs [Out]:", 11);
    for(int i = 0; i < N; i++){
        degAout[i] = 0;
        for(int l = 0; l < N; l++){
            if(A[i][l]){
                ++degAout[i];
            }
        }
        sprintf(buffer, "%s: %d", Anames[i], degAout[i]);
        TextOut(hdc, 200, 40+20*i, buffer, strlen(buffer));
    }
    return degAout; 
}

int* degMatrixIn(float** A, int N, HDC hdc, char** Anames){
    int* degAIn = (int*)malloc(N * sizeof(int));
    char buffer[8];
    TextOut(hdc, 300, 10, "Degs [In]:", 10);
    for(int i = 0; i < N; i++){
        degAIn[i] = 0;
    }
    for(int i = 0; i < N; i++){
        for(int l = 0; l < N; l++){
            if(A[i][l]){
                ++degAIn[l];
            }
        }
    }
    for(int i = 0; i < N; i++){
        sprintf(buffer, "%s: %d", Anames[i], degAIn[i]);
        TextOut(hdc, 300, 40+20*i, buffer, strlen(buffer));
    }
    return degAIn;
}

int checkRegular(int* degA, int N, HDC hdc){
    /* For Undirected */
    int reg = 1;
    for(int i = 1; i < N; i++){
        if(degA[0] != degA[i]){
            reg = 0;
            break;
        }
    }
    if(reg){
        char buffer[8];
        sprintf(buffer, "Regular: %d", reg);
        TextOut(hdc, 250, 10, buffer, strlen(buffer));
    }else{
        TextOut(hdc, 250, 10, "Not Regular", 11);
    }
    return reg;
}

int checkRegularbyOut(int* degA, int N, HDC hdc){
    int reg = 1;
    for(int i = 1; i < N; i++){
        if(degA[0] != degA[i]){
            reg = 0;
            break;
        }
    }
    if(reg){
        char buffer[8];
        sprintf(buffer, "Regular by Out: %d", reg);
        TextOut(hdc, 400, 10, buffer, strlen(buffer));
    }else{
        TextOut(hdc, 400, 10, "Not Regular by Out", 18);
    }
    return reg;
}

int checkRegularbyIn(int* degA, int N, HDC hdc){
    int reg = 1;
    for(int i = 1; i < N; i++){
        if(degA[0] != degA[i]){
            reg = 0;
            break;
        }
    }
    if(reg){
        char buffer[8];
        sprintf(buffer, "Regular by In: %d", reg);
        TextOut(hdc, 400, 40, buffer, strlen(buffer));
    }else{
        TextOut(hdc, 400, 40, "Not Regular by In", 17);
    }
    return reg;
}

void findSingalorIsolated(int* degA, int N, HDC hdc, char** Anames){
    TextOut(hdc, 400, 10, "Isolated:", 9);
    TextOut(hdc, 500, 10, "Singal:", 7);
    for(int i = 0, singaly = 0, isolatedy = 0; i < N; i++){
        if(!degA[i]){
            TextOut(hdc, 400, 40+20*isolatedy, Anames[i], strlen(Anames[i]));
            ++isolatedy;
        }else if(degA[i] == 1){
            TextOut(hdc, 500, 40+20*singaly, Anames[i], strlen(Anames[i]));
            ++singaly;
        }
    }
}

void findSingalorIsolatedbyInOut(int* degAIn, int* degAOut, int N, HDC hdc, char** Anames){
    TextOut(hdc, 550, 10, "Isolated:", 9);
    TextOut(hdc, 650, 10, "Singal:", 7);
    int* degA = (int*)malloc(N * sizeof(int));
    for(int i = 0, singaly = 0, isolatedy = 0; i < N; i++){
        degA[i] = degAIn[i] + degAOut[i];
        if(!degA[i]){
            TextOut(hdc, 550, 40+20*isolatedy, Anames[i], strlen(Anames[i]));
            ++isolatedy;
        }else if(degA[i] == 1){
            TextOut(hdc, 650, 40+20*singaly, Anames[i], strlen(Anames[i]));
            ++singaly;
        }
    }
}

void FindPath(float** A, int N, int start, int end, int len){
    /* Bad Realization */
    char buffer[64];
    char** Anames = getNames(N);
    if(len == 2){
        for(int i = 0; i < N; i++){
            if(A[start][i] && A[i][end]){
                sprintf(buffer, "%s -> %s -> %s\n", Anames[start], Anames[i], Anames[end]);
                printf(buffer);
            }
        }
    }else if(len == 3){
        for(int i = 0; i < N; i++){
            if(A[start][i]){
                for(int l = 0; l < N; l++){
                    if(A[i][l] && A[l][end]){
                        sprintf(buffer, "%s -> %s -> %s -> %s\n", Anames[start], Anames[i], Anames[l], Anames[end]);
                        printf(buffer);
                    }
                }
            }
        }
    }
    free(Anames);
}

float** CreateReachabilityMatrix(float** A, int N){
    float** arr = (float**)malloc(N * sizeof(float*));
    for(int i = 0; i < N; i++){
        arr[i] = (float*)malloc(N * sizeof(float));
        for(int j = 0; j < N; j++){
            arr[i][j] = A[i][j];
        }
    }
    for(int k = 0; k < N; k++){
        for(int l = 0; l < N; l++){
            for(int p = 0; p < N; p++){
                if(arr[l][p] || (arr[l][k] && arr[k][p])){
                    arr[l][p] = 1;
                }
            }
        }
    }
    return arr;
}

float** TransposeMatrix(float** A, int N){
    float** arr = (float**)malloc(N * sizeof(float*));
    for(int i = 0; i < N; i++){
        arr[i] = (float*)malloc(N * sizeof(float));
        for(int l = 0; l < N; l++){
            arr[i][l] = A[i][l];
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            arr[i][j] = A[j][i];
            arr[j][i] = A[i][j];
        }
    }
    return arr;
}

float** multMatrix(float** A, float** B, int N){
    float** arr = (float**)malloc(N * sizeof(float*));
    for(int i = 0; i < N; i++){
        arr[i] = (float*)malloc(N * sizeof(float));
        for (int j = 0; j < N; j++) {
            arr[i][j] = 0;
            for (int k = 0; k < N; k++) {
                arr[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return arr;
}

float** powerMatrix(float** A, int power, int N){
    float** arr = (float**)malloc(N * sizeof(float*));
    for(int i = 0; i < N; i++){
        arr[i] = (float*)malloc(N * sizeof(float));
        for(int j = 0; j < N; j++){
            arr[i][j] = A[i][j];
        }
    }
    for(int k = 1; k < power; k++){
        arr = multMatrix(arr, A, N);
    }
    return arr;
}

int DFS(int f, int N, float** Rarr, int top) {
    d_visited[f] = 1;
    for(int i = 0; i < N; i++) {
        if(Rarr[f][i] && !Rarr[i]) {
            DFS(i, N, Rarr, top);
        }
    }
    stack[++top] = f;
    return top;
}

void ReverseDFS(int v, int N, int num_components, float** Rarr) {
    d_visited[v] = 1;
    components[v] = num_components;
    for(int i = 0; i < N; i++) {
        if(Rarr[i][v] && !d_visited[i]) {
            ReverseDFS(i, N, num_components, Rarr);
        }
    }
}

int stronglyConnected(HWND hWnd, HDC hdc, float** A, int N) {
    float** Rarr = CreateReachabilityMatrix(A, N);
    int  num_components = 0,
        f,
        top = -1;
    components = (int*)malloc(N * sizeof(int));
    d_visited = (int*)malloc(N * sizeof(int));
    stack = (int*)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++){
        d_visited[i] = 0;
        components[i] = -1;
    }
    for(int i = 0; i < N; i++) {
        if(!d_visited[i]){
            top = DFS(i, N, Rarr, top);
        }
    }
    float** Tarr = TransposeMatrix(Rarr, N);
    for(int i = 0; i < N; i++) {
        d_visited[i] = 0;
    }

    while(top >= 0) {
        f = stack[top--];
        if(!d_visited[f]) {
            ReverseDFS(f, N, num_components, Rarr);
            num_components++;
        }
    }
    printf("The strongly connected components of the graph are:\n");
    for(int i = 0; i < num_components; i++) {
        printf("{ ");
        for(int j = 0; j < N; j++) {
            if(components[j] == i) {
                printf("%d ", j+1);
            }
        }
        printf("}\n");
    }
    free(Rarr);
    free(Tarr);
    free(d_visited);
    free(stack);
    return num_components;
}