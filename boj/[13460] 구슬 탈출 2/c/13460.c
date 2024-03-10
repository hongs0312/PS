#define Q_SIZE 1000000
#include <stdio.h>

typedef struct{
    int moveCnt;
    int red[2], blue[2];
}state;
state queue[Q_SIZE];
int front = 0, rear = 0;

void addq(state s);
state deleteq();
state move(state s, int dir);
int bfs();

char map[10][10];
int out[2];
int rr[] = {-1, 0, 1, 0};
int cc[] = {0, 1, 0, -1};

int main(){
    int r, c;
    scanf("%d %d", &r, &c);
    getchar();

    state start;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            char tmp = getchar();
            if(tmp == '#' || tmp == '.'){
                map[i][j] = tmp;
            }
            else if(tmp == 'O'){
                out[0] = i; out[1] = j;
                map[i][j] = tmp;
            }
            else if(tmp == 'R'){
                start.red[0] = i; start.red[1] = j;
                map[i][j] = '.';
            }
            else if(tmp == 'B'){
                start.blue[0] = i; start.blue[1] = j;
                map[i][j] = '.';
            }
        }
        getchar();
    }
    start.moveCnt = 0;
    addq(start);
    
    printf("%d", bfs());

    return 0;
}
void addq(state s){
    rear =  (rear+1)%Q_SIZE;
    queue[rear] = s;
}
state deleteq(){
    front = (front+1)%Q_SIZE;
    return queue[front];
}
state move(state s, int dir){
    state ret = s;
    ret.moveCnt++;
    int n_r, n_c;
    for(int i = 0; i < 2; i++){
        while(ret.red[0] != out[0] || ret.red[1] != out[1]){
            n_r = ret.red[0] + rr[dir];
            n_c = ret.red[1] + cc[dir];
            
            if(n_r == out[0] && n_c == out[1]){
                ret.red[0] = n_r; ret.red[1] = n_c;
                break;
            }
            else if(map[n_r][n_c] == '#' || (n_r == ret.blue[0] && n_c == ret.blue[1])) 
                break;
            else{
                ret.red[0] = n_r; ret.red[1] = n_c;
            }
        }
        while(ret.blue[0] != out[0] || ret.blue[1] != out[1]){
            n_r = ret.blue[0] + rr[dir];
            n_c = ret.blue[1] + cc[dir];
            
            if(n_r == out[0] && n_c == out[1]){
                ret.blue[0] = n_r; ret.blue[1] = n_c;
                break;
            }
            else if(map[n_r][n_c] == '#' || (n_r == ret.red[0] && n_c == ret.red[1]))
                break;
            else{
                ret.blue[0] = n_r; ret.blue[1] = n_c;
            }
        }
    }
    return ret;
}
int bfs(){
    while(front != rear){
        state cur = deleteq();
        if(cur.moveCnt > 10)
            continue;
        for(int i = 0; i < 4; i++){
            state next = move(cur, i);
            if(next.blue[0] == out[0] && next.blue[1] == out[1])
                continue;
            else if(next.red[0] == out[0] && next.red[1] == out[1])
                return next.moveCnt;
            else addq(next);
        }
    }
    return -1;
}