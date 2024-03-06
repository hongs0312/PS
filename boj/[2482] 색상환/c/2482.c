#define MOD 1000000003
#include <stdio.h>

int dp[1001][1001]; //dp[n][k]; n개의 색깔 중 k개를 고르는 경우의 수

int main(){
    int n, k;
    scanf("%d\n%d", &n, &k);

    for(int i = 1; i <= n; i++){
        dp[i][0] = 1; dp[i][1] = i;
    }
    for(int i = 2; i <= n; i++) 
        for(int j = 2; j <= k; j++)
            dp[i][j] = (dp[i-2][j-1] + dp[i-1][j]) % MOD;
    
    printf("%d", (dp[n-1][k] + dp[n-3][k-1]) % MOD);

    return 0;
}