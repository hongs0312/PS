#include <stdio.h>
#define MOD 1000000000

long long int dp[1000001]; //dp[i] : i명의 사람이 선물을 나누는 경우의 수

int main(){
    int n;
    scanf("%d", &n);

    dp[1] = 0; dp[2] = 1;
    for(int i = 3; i <= n; i++)
        dp[i] = ((i-1)*(dp[i-1]+dp[i-2]))%MOD;
    
    printf("%lld\n", dp[n]);
    
    return 0;
}