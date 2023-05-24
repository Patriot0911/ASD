struct Graph{
    struct Node* head[vertices];
};

struct Node{
    int dest;
    double weight;
    struct Node* next;
};

int find_min_key(int weights[], int visited[]){
    int min = INT_MAX;    
    int min_index;
    for (int i = 0; i < vertices; ++i)
    {
        if (visited[i] == 0 && weights[i] < min)
        {
            min = weights[i];
            min_index = i;        
        }
    }    
    return min_index;
}

void prim(struct Graph* graph, double** W, int* parents){
    double weigths[vertices];    
    int visited[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        weigths[i] = INT_MAX;
        visited[i] = 0;    
    }
    weigths[0] = 0;
    parents[0] = -1;
    for (int i = 0; i < vertices - 1; ++i)
    {
        int min_key = find_min_key(weigths, visited);
        visited[min_key] = 1;
        struct Node* temp = graph->head[min_key];
        while (temp != NULL)
        {
            int dest = temp->dest;            double weight = W[min_key][dest];;
            if (visited[dest] == 0 && weight < weigths[dest])
            {                
                parents[dest] = min_key;
                weigths[dest] = weight;            
            }
            temp = temp->next;
        }
    }
}

void print_tree(int* parents, double** W){
    OutputDebugString(L"Edge \tWeight\n");    
    for (int i = 1; i < vertices; i++)
    {
        int idx = parents[i];
        if (W[idx][i] != 0 && W[idx][i] != INT_MAX)
        {
            wchar_t buffer[25];            
            swprintf(buffer, 25, L"%d - %d \t%lf \n", parents[i], i, W[idx][i]);
            OutputDebugString(buffer);
        }
    }
}