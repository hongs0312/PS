#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int idx, num;
} data;
typedef struct node* nodePointer;
typedef struct node {
    data item;
    nodePointer lLink, rLink;
} node;
nodePointer deque;
int size = 0;

nodePointer getnode(data item);
data deleteFront(nodePointer deque);
void insertRear(nodePointer deque, data item);
data deleteRear(nodePointer deque);

int input[5000000];

int main(){
    int n, l;
    scanf("%d %d", &n, &l);

    for(int i = 0; i < n; i++)
        scanf("%d", &input[i]);

    data item = {-1, 0};
    deque = getnode(item);
    deque->lLink = deque->rLink = deque;

    for(item.idx = 0; item.idx < n; item.idx++){
        if(size && deque->rLink->item.idx <= item.idx - l)
            deleteFront(deque);

        item.num = input[item.idx];

        while(size && deque->lLink->item.num >= item.num) 
            deleteRear(deque);
        
        insertRear(deque, item);

        printf("%d ", deque->rLink->item.num);
    }
    return 0;
}
nodePointer getnode(data item){
    nodePointer temp = (nodePointer)malloc(sizeof(node));
    temp->item = item;
    temp->lLink = temp->rLink = NULL;
    return temp;
}
data deleteFront(nodePointer deque){
    nodePointer temp = deque->rLink;
    data item = temp->item;

    deque->rLink = temp->rLink;
    temp->rLink->lLink = deque;
    free(temp);

    size--;
    return item;
}
void insertRear(nodePointer deque, data item){
    nodePointer temp = getnode(item);

    temp->rLink = deque;
    temp->lLink = deque->lLink;
    deque->lLink->rLink = temp;
    deque->lLink = temp;

    size++;
}
data deleteRear(nodePointer deque){
    nodePointer temp = deque->lLink;
    data item = temp->item;

    deque->lLink = temp->lLink;
    temp->lLink->rLink = deque;
    free(temp);

    size--;
    return item;
}