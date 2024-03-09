#include <stdio.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int dp[1001][1001];
int arr[1000][1000];

int main(){
    int n, m;
    scanf("%d %d\n", &n, &m);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            arr[i][j] = getchar() - '0';
        }
        getchar();
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(arr[i-1][j-1] == 1){
                dp[i][j] = MIN(MIN(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
            }
        }
    }
    int max = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(dp[i][j] > max){
                max = dp[i][j];
            }
        }
    }
    printf("%d\n", max * max);

    return 0;
}