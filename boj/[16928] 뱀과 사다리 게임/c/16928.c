#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int vertex;
}element;
typedef struct node* nodePointer;
typedef struct node{
    element data;
    nodePointer link;
}node;
typedef struct queue{
    nodePointer front;
    nodePointer rear;
}queue;

nodePointer adj[101];
int visited[101];

nodePointer createNode(element data);
void initQueue(queue* q);
void addq(queue* q, element data);
element deleteq(queue* q);
void bfs();
void makeBoard();

int main(){
    makeBoard();

    int n, m;
    scanf("%d %d", &n, &m);

    for(int i = 0; i < n+m; i++){
        int x, y;
        scanf("%d %d", &x, &y);

        for(int i = 1; i <= 6; i++){
            int temp = x - i;
            if(temp > 0){
                nodePointer cur = adj[temp];
                for(; cur; cur = cur->link){
                    if(cur->data.vertex == x){
                        cur->data.vertex = y;

                        break;
                    }
                }
            }
        }
    }
    bfs();

    printf("%d", visited[100]);

    return 0;
}
nodePointer createNode(element data){
    nodePointer temp = (nodePointer)malloc(sizeof(node));

    temp->data = data;
    temp->link = NULL;

    return temp;
}
void initQueue(queue* q){
    q->front = q->rear = NULL;
}
void addq(queue* q, element data){
    nodePointer temp = createNode(data);

    if(q->front == NULL) 
        q->front = temp;
    else 
        q->rear->link = temp;
    
    q->rear = temp;
}
element deleteq(queue* q){
    nodePointer temp = q->front;

    element data = temp->data;
    q->front = temp->link;
    free(temp);

    return data;
}
void bfs(){
    queue q;
    initQueue(&q);

    addq(&q, (element){1}); visited[1] = 0;

    element cur;
    while(visited[100] == 0){
        cur = deleteq(&q);
        
        nodePointer temp = adj[cur.vertex];
        while(temp){
            if(!visited[temp->data.vertex]){
                addq(&q, temp->data);

                visited[temp->data.vertex] = visited[cur.vertex] + 1;
            }
            temp = temp->link;
        }
    }
}
void makeBoard(){
    for(int i = 1; i <= 100; i++){
        for(int j = 1; j <= 6; j++){
            if(i+j <= 100){
                element e;
                e.vertex = i + j;

                nodePointer temp = createNode(e);
                temp->link = adj[i];
                adj[i] = temp;
            }
        }
    }
}