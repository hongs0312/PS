#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int dp[100001]; // dp[i] : i번째 수로 끝나는 연속합 중 최대값
int input[100001];

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++){
        scanf("%d", &input[i]);
    }

    for(int i = 1; i <= n; i++)
        dp[i] = MAX(dp[i-1] + input[i], input[i]);

    int max = dp[1];
    for(int i = 2; i <= n; i++)
        max = MAX(max, dp[i]);
    
    printf("%d", max);

    return 0;
}