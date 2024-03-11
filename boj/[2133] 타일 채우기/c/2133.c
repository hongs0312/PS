#include <stdio.h>

int dp[31]; //dp[i] = 3xi 크기의 사각형을 채우는 방법의 수

int main(){
    int n;
    scanf("%d", &n);

    dp[2] = 3; //base case
    for(int i = 4; i <= n; i += 2){
        dp[i] = dp[i-2]*dp[2] + 2;

        for(int j = 4; j < i; j += 2)
            dp[i] += dp[i-j]*2;
    }
    printf("%d\n", dp[n]);

    return 0;
}