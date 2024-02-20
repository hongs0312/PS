#define INF 100000001
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int v;
    int w;
}element;

typedef struct node* nodePointer;
typedef struct node{
    element data;
    nodePointer link;
}node;

typedef struct{
    element heap[100001];
    int heap_size;
}HeapType;
HeapType heap;

nodePointer graph[1001];
int visited[1001], memo[1001];

void init(HeapType* h);
void push(HeapType* h, element item);
element pop(HeapType* h);
void dijkstra(int start, int end);

int main(){
    int n, m;
    scanf("%d\n%d", &n, &m);

    for(int i = 1; i <= n; i++)
        visited[i] = INF;

    for(int i = 0; i < m; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        nodePointer temp = (nodePointer)malloc(sizeof(node));
        temp->data.v = b;
        temp->data.w = c;
        
        temp->link = graph[a];
        graph[a] = temp;
    }
    int start, end;
    scanf("%d %d", &start, &end);
    dijkstra(start, end);

    printf("%d\n", visited[end]);
    int path[1000], idx = 0;
    while(end){
        path[idx++] = end;
        end = memo[end];
    }
    printf("%d\n", idx);
    for(int i = idx-1; i >= 0; i--)
        printf("%d ", path[i]);

    return 0;
}
void init(HeapType* h){
    h->heap_size = 0;
}
void push(HeapType* h, element item){
    int i = ++(h->heap_size);

    while((i != 1) && (item.w < h->heap[i/2].w)){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}
element pop(HeapType* h){
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while(child <= h->heap_size){
        if((child < h->heap_size) && (h->heap[child].w) > h->heap[child+1].w)
            child++;
        if(temp.w <= h->heap[child].w) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}
void dijkstra(int start, int end){
    memo[start] = 0;

    element item = {start, 0};
    push(&heap, item);

    while(item.v != end){
        item = pop(&heap);
        int cur = item.v;
        if(visited[cur] < item.w) continue;
        visited[cur] = item.w;

        for(nodePointer p = graph[cur]; p; p = p->link){
            int v = p->data.v;
            int w = p->data.w + item.w;
            if(visited[v] > w){
                visited[v] = w; memo[v] = cur;
                element next = {v, w};
                push(&heap, next);
            }
        }
    }
}