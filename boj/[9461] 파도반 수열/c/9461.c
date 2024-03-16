#include <stdio.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

long long int dp[101]; // dp[i] : i번째 수의 파도반 수열 값
int input[101];

int main(){
    int t;
    scanf("%d", &t);

    int n = 0;
    for(int i = 0; i < t; i++){
        scanf("%d", &input[i]);
        n = MAX(n, input[i]);
    }

    dp[1] = 1; dp[2] = 1; dp[3] = 1; dp[4] = 2; dp[5] = 2; // base case
    for(int i = 6; i <= n; i++)
        dp[i] = dp[i-1] + dp[i-5];

    for(int i = 0; i < t; i++)
        printf("%lld\n", dp[input[i]]);
    
    return 0;
}