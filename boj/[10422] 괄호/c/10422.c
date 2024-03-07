/*
괄호
*/
#include <stdio.h>
#define MOD 1000000007

long long int dp[5001]; //dp[i] = 길이가 i일 때 만들 수 있는 괄호 문자열의 개수
int input[1000];

int main(){
    int t;
    scanf("%d", &t);

    int max = 0;
    for(int i = 0; i < t; i++){
        scanf("%d", &input[i]);

        if(max < input[i]) max = input[i];
    }
    dp[0] = dp[2] = 1;
    for(int i = 4; i <= max; i+=2)
        for(int j = 2; j <= i; j+=2)
            dp[i] = (dp[i] + dp[j-2] * dp[i-j]) % MOD;
        

    for(int i = 0; i < t; i++)
        printf("%lld\n", dp[input[i]]);
    
    return 0;
}