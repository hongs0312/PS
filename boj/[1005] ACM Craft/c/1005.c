#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int vertex;
}element;
typedef struct node* nodePointer;
typedef struct node{
    element data;
    nodePointer link;
}node;
typedef struct{
    nodePointer front, rear;
}queue;

nodePointer createNode(element item);
void init(queue *q);
void push(queue *q, element item);
element pop(queue *q);
void expireQueue(queue *q);

int main(){
    int t;
    scanf("%d", &t);

    while(t--){
        int n, k;
        scanf("%d %d", &n, &k);

        nodePointer graph[1001] = {NULL, };
        int buildInfo[1001][2] = {0, }; // buildInfo[i][0] : 건물 i 건설 시간, buildInfo[i][1] : 건물 i 진입 차수
        queue q; init(&q);
        
        for(int i = 1; i <= n; i++) //건물 건설 시간
            scanf("%d", &buildInfo[i][0]);

        for(int i = 1; i <= k; i++){
            int a, b;   //a -> b
            scanf("%d %d", &a, &b);

            nodePointer temp = createNode((element){b});
            temp->link = graph[a];
            graph[a] = temp;

            buildInfo[b][1]++; //b 진입 차수 증가
        }

        int goal;
        scanf("%d", &goal);

        int dp[1001] = {0, }; //dp[i] : 건물 i 건설 시간 누적
        for(int i = 1; i <= n; i++){
            if(buildInfo[i][1] == 0){
                push(&q, (element){i});  //진입 차수가 0인 건물들을 큐에 넣음

                dp[i] = buildInfo[i][0]; //건물 건설 시간 누적
            }
        }
        int cur = 0;
        while(1){
            cur = pop(&q).vertex;

            nodePointer temp = graph[cur];
            for(; temp; temp = temp->link){
                int next = temp->data.vertex;
                buildInfo[next][1]--;  //진입 차수 감소

                dp[next] = MAX(dp[next], dp[cur] + buildInfo[next][0]);   //건물 건설 시간 누적

                if(buildInfo[next][1] == 0)    //진입 차수가 0이 되면 큐에 넣음
                    push(&q, (element){next});
            }

            if(cur == goal) //목표 건물이면 종료
                break;
        }
        printf("%d\n", dp[goal]);

        expireQueue(&q);
    }

    return 0;
}
nodePointer createNode(element item){
    nodePointer temp = (nodePointer)malloc(sizeof(node));
    
    temp->data = item;
    temp->link = NULL;
    
    return temp;
}
void init(queue *q){
    q->front = q->rear = NULL;
}
void push(queue *q, element item){
    nodePointer temp = createNode(item);
    
    if(q->front == NULL)
        q->front = temp;
    else
        q->rear->link = temp;
    
    q->rear = temp;
}
element pop(queue *q){
    element item;
    nodePointer temp;
    
    temp = q->front;
    item = temp->data;
    q->front = temp->link;
    free(temp);
    
    return item;
}
void expireQueue(queue *q){
    nodePointer temp;
    
    while(q->front){
        temp = q->front;
        q->front = temp->link;
        free(temp);
    }
    q->rear = NULL;
}