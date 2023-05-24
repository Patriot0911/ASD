Node* getNode(Node* fnode, int N, int key){
    Node* nnode = fnode;
    for(int i = 0; i < N; i++){
        if(nnode->key == key){
            return nnode;
        }
        nnode = nnode->prev;
    }
    return nnode;
}
void printNodes(Node* fnode, int N){
    Node *next = getNode(fnode, N, 0);
    for(int i = 0; i < N; i++){
        for(int l = 0; l < N; l++){
            printf("%d ", next->links[l]);
        }
        printf("\n");
        next = next->next;
    }
}
Node* createLinkedNodesBasedOn(int** A, int** W, int N, int begin){
    Node* cur = NULL;
    Node* old = NULL;
    Node* firstnode = NULL;
    for(int i = 0; i < N; i++){
        cur = (Node*)malloc(sizeof(Node));
        cur->links = (int*)malloc(N * sizeof(int));
        cur->ws = (int*)malloc(N * sizeof(int));
        for(int l = 0; l < N; l++){
            cur->ws[l] = W[i][l];
            cur->links[l] = A[i][l];
        }
        cur->key = i;
        if(i > 8){
            sprintf(cur->name, "%d", i+1);
        }else{
            sprintf(cur->name, "0%d", i+1);
        }
        if(old){
            cur->prev = old;
            old->next = cur;
        }
        if(i == 0){
            firstnode = cur;
        }
        if(i == N-1){
            cur->next = firstnode;
            firstnode->prev = cur;
            break;
        }        
        old = cur;
    }
    return cur;
}
Node* addCoordsToNodes(Node* fnode, int N, float a){
    Node* nnode = fnode;
    float leng = a/(2*sin(180/(N-1)));
    for(int i = 0; i < N; i++){
        if(i == 0){
            nnode->x = startx; 
            nnode->y = starty;
            nnode = nnode->prev;
            continue;
        }
        nnode->x = startx + leng * cos(2 * M_PI * i / (N-1));
        nnode->y = starty + leng * sin(2 * M_PI * i / (N-1));
        nnode = nnode->prev;
    }
    return nnode;
}