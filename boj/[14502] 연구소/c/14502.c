#define Q_SIZE 100
#include <stdio.h>

typedef struct{
    int r, c;
} pos;

typedef struct{
    int n, m;
    int map[10][10];

    int virus_cnt; pos virus[10];
} map;

pos queue[Q_SIZE];
int front, rear;

int rr[] = {1, -1, 0, 0};
int cc[] = {0, 0, 1, -1};

int max = 0;

void push(pos item);
pos pop();

map cpy_map(map m);
void bfs(map *m);
void safe_chk(int recur, pos wall, map m);
int cnt_safe_area(map m);

int main(){
    map map;
    scanf("%d %d", &map.n, &map.m);

    for(int i = 1; i < map.n+1; i++)
        map.map[i][0] = map.map[i][map.m+1] = 1;
    
    for(int i = 1; i < map.m+2; i++)
        map.map[0][i] = map.map[map.n+1][i] = 1;

    map.virus_cnt = 0;
    for(int i = 1; i <= map.n; i++){
        for(int j = 1; j <= map.m; j++){
            scanf("%d", &map.map[i][j]);

            if(map.map[i][j] == 2){
                map.virus[map.virus_cnt] = (pos){i, j};

                map.virus_cnt++;
            }
        }
    }
    safe_chk(0, (pos){1, 1}, map);

    printf("%d\n", max);

    return 0;
}
void push(pos item){
    rear = (rear + 1) % Q_SIZE;
    queue[rear] = item;
}
pos pop(){
    front = (front + 1) % Q_SIZE;
    return queue[front];
}
void bfs(map *m){
    for(int i = 0; i < m->virus_cnt; i++)
        push(m->virus[i]);

    while(front != rear){
        pos cur = pop();

        for(int i = 0; i < 4; i++){
            int nr = cur.r + rr[i];
            int nc = cur.c + cc[i];

            if(m->map[nr][nc] == 0){
                m->map[nr][nc] = 2;

                push((pos){nr, nc});
            }
        }
    }
}
int cnt_safe_area(map m){
    int cnt = 0;

    for(int i = 1; i <= m.n; i++)
        for(int j = 1; j <= m.m; j++)
            if(m.map[i][j] == 0) cnt++;

    return cnt;
}
void safe_chk(int recur, pos wall, map m){
    if(recur == 3){
        bfs(&m);

        int safe = cnt_safe_area(m);

        if(safe > max) max = safe;
    }
    int i = wall.r; int j = wall.c;
    for(; i <= m.n; i++){
        for(; j <= m.m; j++){
            if(m.map[i][j] == 0){
                m.map[i][j] = 1;

                safe_chk(recur+1, (pos){i, j+1}, m);

                m.map[i][j] = 0;
            }
        }
        j = 1;
    }
}