#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct lList{
    int key;
    int data;
    struct lList*prev;
} List;


void printAll(List* l)
{
    while (l != NULL) {
        printf("[%d] %d \n", l -> key, l -> data);
        l = l -> prev;
    }
}

int getdata(List* l, int k){
    while(l != NULL){
        if(l -> key == k){
            return l -> data;
        }
        l = l -> prev;
    }
    return 0;
}

int main() {
    int count, sum = 0;
    printf("Enter max:");
    scanf("%d", &count);
    if(count < 1){
        printf("Ur max must be > 0");
        return 0;
    }
    List *old = NULL;
    List *cur = NULL;
    for(int l = 0; l < count; l++){
        cur = malloc(sizeof(struct lList));
        cur -> data = l+100;
        cur -> key  = l;
        cur -> prev = old;
        old = cur;
    }
    printAll(cur);
    for(int i = 0, t = count-1; i < count/2; i++, t--){
        sum += getdata(cur, i) + getdata(cur, t);
    }
    if((int)(count%2) == 1){
        sum += getdata(cur, roundf(count/2));
    }
    printf("\n Ans: %d\n", sum);
    while (cur->prev)
    {
        old = cur->prev;
        cur = old;
        free(old);
    }    
    free(cur);
    free(old);
    return 0;
}