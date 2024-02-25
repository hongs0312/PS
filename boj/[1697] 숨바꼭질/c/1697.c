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
    nodePointer front, rear;
}Queue;

nodePointer adj[100001];
int visited[100001];
Queue queue;

nodePointer createNode(element item);
void initQueue(Queue* q);
void addq(Queue* q, element item);
element deleteq(Queue* q);
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
            nodePointer temp = createNode((element){i*2, 1});
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
void initQueue(Queue* q){
    q->front = q->rear = NULL;
}
void addq(Queue* q, element item){
    nodePointer temp = createNode(item);
    temp->data = item;
    temp->link = NULL;

    if(q->front)
        q->rear->link = temp;
    else
        q->front = temp;
    
    q->rear = temp;
}
element deleteq(Queue* q){
    nodePointer temp = q->front;
    element item;

    item = temp->data;
    q->front = temp->link;
    free(temp);

    return item;
}
element bfs(int v, int k){
    nodePointer w;
    addq(&queue, (element){v, 0});

    int cnt = 0, flag = 1, timeTot = 0;
    while(flag || (queue.front && queue.front->data.walk == timeTot)){
        element item = deleteq(&queue);
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
                    
                    addq(&queue, (element){vertex, walk+time});
                }
            }
        }
    }
    return (element){timeTot, cnt};
}