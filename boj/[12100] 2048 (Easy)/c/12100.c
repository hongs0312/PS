#include <stdio.h>

typedef struct{
    int num;
    int merged;
}block;

void move(int board[][20], int temp[20][20], int dir); //0: up, 1: down, 2: left, 3: right
int max(int board[][20]);
void dfs(int board[][20], int depth);

int n, m;

int main(){
    scanf("%d", &n);
    getchar();

    int board[20][20];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &board[i][j]);
    
    dfs(board, 0);

    printf("%d", m);

    return 0;
}
void move(int board[][20], int temp[20][20], int dir){ //0: up, 1: down, 2: left, 3: right
    block b[20][20];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            b[i][j].num = 0;
            b[i][j].merged = 0;
        }
    }
    switch (dir){
    case 0: //up
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j]){
                    int k = i;
                    for(; k > 0 && !b[k][j].num ; k--); //정지 조건 : 1. 벽을 만날 때까지 2. 다른 블록을 만날 때까지

                    if(k != i){
                        if(b[k][j].num == 0) //빈칸이면 그냥 옮김
                            b[k][j].num = board[i][j];
                        else{ //빈칸이 아니면
                            if(b[k][j].num == board[i][j]){ //같은 블록이면
                                if(!b[k][j].merged){ //합쳐진 적이 없으면
                                    b[k][j].num *= 2;
                                    b[k][j].merged = 1;
                                }
                                else b[k+1][j].num = board[i][j];
                            }
                            else if(b[k][j].num != board[i][j]) //다른 블록이면
                                b[k+1][j].num = board[i][j];
                        }   
                    }
                    else b[k][j].num = board[i][j];
                }
            }
        }
        break;
    case 1: //down
        for(int i = n-1; i >= 0; i--){
            for(int j = 0; j < n; j++){
                if(board[i][j]){
                    int k = i;
                    for(; k < n-1 && !b[k][j].num; k++); //정지 조건 : 1. 벽을 만날 때까지 2. 다른 블록을 만날 때까지

                    if(k != i){
                        if(b[k][j].num == 0) //빈칸이면 그냥 옮김
                            b[k][j].num = board[i][j];
                        else{ //빈칸이 아니면
                            if(b[k][j].num == board[i][j]){ //같은 블록이면
                                if(!b[k][j].merged){ //합쳐진 적이 없으면
                                    b[k][j].num *= 2;
                                    b[k][j].merged = 1;
                                }
                                else b[k-1][j].num = board[i][j];
                            }
                            else if(b[k][j].num != board[i][j]) //다른 블록이면
                                b[k-1][j].num = board[i][j];
                        }
                    }
                    else b[k][j].num = board[i][j];
                }
            }
        }
        break;
    case 2: //left
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j]){
                    int k = j;
                    for(; k > 0 && !b[i][k].num; k--); //정지 조건 : 1. 벽을 만날 때까지 2. 다른 블록을 만날 때까지
                    
                    if(k != j){
                        if(b[i][k].num == 0) //빈칸이면 그냥 옮김
                            b[i][k].num = board[i][j];
                        else{ //빈칸이 아니면
                            if(b[i][k].num == board[i][j]){ //같은 블록이면
                                if(!b[i][k].merged){ //합쳐진 적이 없으면
                                    b[i][k].num *= 2;
                                    b[i][k].merged = 1;
                                }
                                else b[i][k+1].num = board[i][j];
                            }
                            else if(b[i][k].num != board[i][j]) //다른 블록이면
                                b[i][k+1].num = board[i][j];
                        }
                    }
                    else b[i][k] .num= board[i][j];
                }
            }
        }
        break;
    case 3: //right
        for(int i = 0; i < n; i++){
            for(int j = n-1; j >= 0; j--){
                if(board[i][j]){
                    int k = j;
                    for(; k < n-1 && !b[i][k].num; k++); //정지 조건 : 1. 벽을 만날 때까지 2. 다른 블록을 만날 때까지
                    
                    if(k != j){
                        if(b[i][k].num == 0) //빈칸이면 그냥 옮김
                            b[i][k].num = board[i][j];
                        else{ //빈칸이 아니면
                            if(b[i][k].num == board[i][j]){ //같은 블록이면
                                if(!b[i][k].merged){ //합쳐진 적이 없으면
                                    b[i][k].num *= 2;
                                    b[i][k].merged = 1;
                                }
                                else b[i][k-1].num = board[i][j];
                            }
                            else if(b[i][k].num != board[i][j]) //다른 블록이면
                                b[i][k-1].num = board[i][j];
                        }
                    }
                    else b[i][k].num = board[i][j];
                }
            }
        }
        break;
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            temp[i][j] = b[i][j].num;
}
int max(int board[][20]){
    int max = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            max = max > board[i][j] ? max : board[i][j];
    
    return max;
}
void dfs(int board[][20], int depth){
    // printf("depth: %d\n", depth);
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++)
    //         printf("%d ", board[i][j]);
    //     printf("\n");
    // }
    // printf("\n");

    if(depth == 5){
        int temp = max(board);
        m = m > temp ? m : temp;
        return;
    }
    for(int i = 0; i < 4; i++){
        int temp[20][20];
        move(board, temp, i);
        dfs(temp, depth+1);
    }
}