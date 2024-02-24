/*
숨바꼭질 3
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int vertex;
    int walk;
}element;
typedef struct node* nodePointer;
typedef struct node{
    element data;
    nodePointer link;
}node;
typedef struct{
    element heap[100001];
    int size;   
}Heap;


nodePointer adj[100001];
int visited[100001];
Heap heap;

nodePointer createNode(element item);
void initHeap(Heap* h);
void insertHeap(Heap* h, element item);
element deleteHeap(Heap* h);
element bfs(int v, int k);

int main(){
    int n, k;
    scanf("%d %d", &n, &k);

    for(int i = 0; i <= 100000; i++){
        if(i-1 >= 0){
            nodePointer temp = createNode((element){i-1, 1});
            temp->link = adj[i];
            adj[i] = temp;
        }
        if(i+1 <= 100000){
            nodePointer temp = createNode((element){i+1, 1});
            temp->link = adj[i];
            adj[i] = temp;
        }
        if(i*2 <= 100000){
            nodePointer temp = createNode((element){i*2, 0});
            temp->link = adj[i];
            adj[i] = temp;
        }
    }
    element result = bfs(n, k);
    printf("%d", result.vertex);
    
    return 0;
}
nodePointer createNode(element item){
    nodePointer temp = (nodePointer)malloc(sizeof(node));
    temp->data = item;
    temp->link = NULL;

    return temp;
}
void initHeap(Heap* h){
    h->size = 0;
}
void insertHeap(Heap* h, element item){
    int i = ++(h->size);

    while(i != 1 && item.walk < h->heap[i/2].walk){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}
element deleteHeap(Heap* h){
    int parent = 1, child = 2;
    element item = h->heap[1], temp = h->heap[(h->size)--];

    while(child <= h->size){
        if(child < h->size && h->heap[child].walk > h->heap[child+1].walk)
            child++;
        
        if(temp.walk <= h->heap[child].walk)
            break;
        
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;

    return item;
}
element bfs(int v, int k){
    nodePointer w;
    insertHeap(&heap, (element){v, 0});

    int cnt = 0, flag = 1, timeTot = 0;
    while(flag || (heap.size && heap.heap[0].walk == timeTot)){
        element item = deleteHeap(&heap);
        int v = item.vertex, walk = item.walk;
        visited[v] = 1;

        if (v == k){
            if(flag){
                flag = 0;
                timeTot = walk;
            }
            cnt++;
        }
        else{
            for(w = adj[v]; w; w = w->link){
                if(!visited[w->data.vertex]){
                    int vertex = w->data.vertex, time = w->data.walk;
                    
                    insertHeap(&heap, (element){vertex, walk+time});
                }
            }
        }
    }
    return (element){timeTot, cnt};
}