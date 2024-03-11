#include <stdio.h>

int nodes[50];

int queue[50];
int front = -1, rear = -1;
void addq(int item){
    queue[++rear] = item;
}
int deleteq(){
    return queue[++front];
}

int chk[50];
int main(){
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", &nodes[i]);

    int elim, temp, cnt = 0;
    scanf("%d", &elim);
    chk[elim] = 1; cnt++;
    nodes[elim] = -2;
    addq(elim);

    while(front != rear){
        temp = deleteq();
        for(int i = 0; i < n; i++){
            if(nodes[i] == temp){
                nodes[i] = -2;
                chk[i] = 1; cnt++;
                addq(i);
            }
        }
    }
    for(int i = 0; i < n; i++){
        if(nodes[i] >= 0 && !chk[nodes[i]]){
            chk[nodes[i]] = 1; cnt++;
        }
    }
    printf("%d", n - cnt);

    return 0;
}