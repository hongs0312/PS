#define MAX(a, b) (a > b ? a : b)
#include <stdio.h>

int stair[301], dp[301];

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++)
        scanf("%d", &stair[i]);

    dp[1] = stair[1];

    for(int i = 2; i <= n; i++){
        if(i == 2)
            dp[i] = stair[i] + stair[i-1];
        else
            dp[i] = MAX(dp[i-3] + stair[i-1] + stair[i], dp[i-2] + stair[i]);
    }
    printf("%d\n", dp[n]);

    return 0;
}
