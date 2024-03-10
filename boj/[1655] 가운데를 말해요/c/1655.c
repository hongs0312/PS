#define MAX 50001
#include <stdio.h>

typedef struct{
    int key;
}element;
element maxHeap[MAX], minHeap[MAX];
int max_n, min_n;

void max_push(element item, int *max_n);
element max_pop(int *max_n);

void min_push(element item, int *min_n);
element min_pop(int *min_n);

int main(){
    int t;
    scanf("%d", &t);

    //기준점 == maxHeap의 해드
    for(int i = 0; i < t; i++){
        element item;
        scanf("%d", &item.key);

        if(max_n == 0)
            max_push(item, &max_n);
        else{
            if(maxHeap[1].key <= item.key)
                min_push(item, &min_n);
            else
                max_push(item, &max_n);
            
            if(max_n > min_n+1)
                min_push(max_pop(&max_n), &min_n);
            else if(max_n < min_n)
                max_push(min_pop(&min_n), &max_n);
        }
        printf("%d\n", maxHeap[1].key);
    }
    return 0;
}
void max_push(element item, int *max_n){
    int i = ++(*max_n);
    while(i != 1 && maxHeap[i/2].key < item.key){
        maxHeap[i] = maxHeap[i/2];
        i /= 2;
    }
    maxHeap[i] = item;
}
element max_pop(int *max_n){
    element item = maxHeap[1], temp = maxHeap[(*max_n)--];
    int parent = 1, child = 2;
    while(child <= *max_n){
        if(maxHeap[child].key < maxHeap[child+1].key)
            child++;
        if(maxHeap[child].key <= temp.key)
            break;
        maxHeap[parent] = maxHeap[child];
        parent = child;
        child *= 2;
    }
    maxHeap[parent] = temp;
    return item;
}
void min_push(element item, int *min_n){
    int i = ++(*min_n);
    while(i != 1 && minHeap[i/2].key > item.key){
        minHeap[i] = minHeap[i/2];
        i /= 2;
    }
    minHeap[i] = item;
}
element min_pop(int *min_n){
    element item = minHeap[1], temp = minHeap[(*min_n)--];
    int parent = 1, child = 2;
    while(child <= *min_n){
        if(minHeap[child].key > minHeap[child+1].key)
            child++;
        if(minHeap[child].key >= temp.key)
            break;
        minHeap[parent] = minHeap[child];
        parent = child;
        child *= 2;
    }
    minHeap[parent] = temp;
    return item;
}