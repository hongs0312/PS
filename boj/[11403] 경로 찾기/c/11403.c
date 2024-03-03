#define MIN(a, b) (a) < (b) ? (a) : (b)
#define INF 0x0fffffff
#include <stdio.h>

void floyd(int n);

int adj[100][100];

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &adj[i][j]);

            if(adj[i][j] == 0)
                adj[i][j] = INF;
        }
    }
    floyd(n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adj[i][j] == INF)
                printf("0 ");
            else
                printf("1 ");
        }
        printf("\n");
    }
    return 0;
}
void floyd(int n){
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                adj[i][j] = MIN(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}