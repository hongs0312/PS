#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num;
    char cmd[20];
}element;

typedef struct node* nodePointer;
typedef struct node{
    element data;
    nodePointer link;
}node;
typedef struct {
    nodePointer front, rear;
}Queue;
Queue q;

char cmd[4] = {'D', 'S', 'L', 'R'};
int visited[10001];
nodePointer createNode(element item);

void init(Queue *q);
void push(Queue *q, element item);
element pop(Queue *q);

element DSLR(element data, char cmd);
void bfs(int start, int end);

int main(){
    int T;
    scanf("%d", &T);

    init(&q);
    while(T--){
        while(q.front) pop(&q);
        
        memset(visited, 0, sizeof(visited));

        int start, end;
        scanf("%d %d", &start, &end);

        bfs(start, end);
    }

    return 0;
}
nodePointer createNode(element item){
    nodePointer temp = (nodePointer)malloc(sizeof(node));
    
    temp->data.num = item.num;
    strcpy(temp->data.cmd, item.cmd);
    temp->link = NULL;

    return temp;
}
void init(Queue *q){
    q->front = q->rear = NULL;
}
void push(Queue *q, element item){
    nodePointer temp = createNode(item);
    
    if(q->front == NULL)
        q->front = temp;
    else
        q->rear->link = temp;
    
    q->rear = temp;
}
element pop(Queue *q){
    nodePointer temp = q->front;

    element item = temp->data;
    q->front = temp->link;

    free(temp);

    return item;
}
element DSLR(element data, char cmd){
    element result;
    strcpy(result.cmd, data.cmd);
    
    int num = data.num;
    if(cmd == 'D'){
        num = (num*2)%10000;

        result.num = num;
        strcat(result.cmd, "D");
    }
    else if(cmd == 'S'){
        num = (num == 0) ? 9999 : num-1;

        result.num = num;
        strcat(result.cmd, "S");
    }
    else if(cmd == 'L'){
        num = (num%1000)*10 + num/1000;

        result.num = num;
        strcat(result.cmd, "L");
    }
    else if(cmd == 'R'){
        num = (num/10) + (num%10)*1000;

        result.num = num;
        strcat(result.cmd, "R");
    }
    return result;
}
void bfs(int start, int end){
    element item;
    item.num = start; item.cmd[0] = '\0';
    push(&q, item);

    while(1){
        element cur = pop(&q);
        for(int i = 0; i < 4; i++){
            element next = DSLR(cur, cmd[i]);
            
            if(visited[next.num]) continue;
            visited[next.num] = 1;

            if(next.num == end){
                printf("%s\n", next.cmd);

                return;
            }
            push(&q, next);
        }
    }
}