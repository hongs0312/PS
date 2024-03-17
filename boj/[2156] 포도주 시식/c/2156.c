#define MAX(a, b) (a > b ? a : b)
#include <stdio.h>

int wine[10001], dp[10001];

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++)
        scanf("%d", &wine[i]);

    dp[1] = wine[1];

    for(int i = 2; i <= n; i++){
        if(i == 2)
            dp[i] = wine[i] + wine[i-1];
        else
            dp[i] = MAX(dp[i - 1], MAX(dp[i - 2], dp[i - 3] + wine[i - 1]) + wine[i]);
    }
    printf("%d\n", dp[n]);

    return 0;
}