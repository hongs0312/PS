#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int r, c;
    int speed, dir;
    int size;
    int isAlive;
}Shark;

int map[101][101];

int rr[] = {-1, 1, 0, 0};
int cc[] = {0, 0, 1, -1};
int R, C, m;

int catch_shark(int col);
void move_shark();

Shark* sharks;

int main(){
    scanf("%d %d %d", &R, &C, &m);

    sharks = (Shark*)malloc(sizeof(Shark) * (m+1));

    for(int i = 1; i <= m; i++){
        int r, c, s, d, z;
        scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);

        map[r][c] = i;

        sharks[i].r = r; sharks[i].c = c;
        sharks[i].speed = s; sharks[i].dir = d-1;
        sharks[i].size = z; sharks[i].isAlive = 1;
    }
    int catchSum = 0;
    for(int i = 1; i <= C; i++){ // 낚시왕이 이동한다.
        // 상어를 잡는다.
        int shark = catch_shark(i);
        if(shark) catchSum += sharks[shark].size;

        // 상어를 이동시킨다.
        move_shark();        
    }
    printf("%d", catchSum);
    
    return 0;
}
int catch_shark(int col){
    for(int r = 1; r <= R; r++){
        if(map[r][col]){
            int shark = map[r][col];

            sharks[shark].isAlive = 0;
            map[r][col] = 0;

            return shark;
        }
    }
    return 0;
}
void move_shark(){
    int temp[101][101] = {0};
    int r, c, n_r, n_c;

    for(int shark = 1; shark <= m; shark++){
        if(sharks[shark].isAlive == 0) continue;  // 이미 죽은 상어는 무시

        r = sharks[shark].r; c = sharks[shark].c;

        map[r][c] = 0;
        
        n_r = r + rr[sharks[shark].dir] * sharks[shark].speed;
        n_c = c + cc[sharks[shark].dir] * sharks[shark].speed;

        while(n_r < 1 || R < n_r || n_c < 1 || C < n_c){
            if(n_r < 1){ // 벽에 부딪힌다면
                n_r = 2 - n_r;
                sharks[shark].dir = 1;
            }
            else if(n_r > R){
                n_r = 2 * R - n_r;
                sharks[shark].dir = 0;
            }
            else if(n_c < 1){
                n_c = 2 - n_c;
                sharks[shark].dir = 2;
            }
            else if(n_c > C){
                n_c = 2 * C - n_c;
                sharks[shark].dir = 3;
            }
        }
        sharks[shark].r = n_r; sharks[shark].c = n_c;
        if(temp[n_r][n_c]){ // 다른 상어가 있다면
            if(sharks[temp[n_r][n_c]].size < sharks[shark].size){  // 내가 더 크다면
                sharks[temp[n_r][n_c]].isAlive = 0;
                temp[n_r][n_c] = shark;
            }
            else sharks[shark].isAlive = 0;   // 내가 더 작다면
        }
        else temp[n_r][n_c] = shark;   // 아무도 없다면
    }
    for(int i = 1; i <= R; i++)
        for(int j = 1; j <= C; j++)
            map[i][j] = temp[i][j];
}