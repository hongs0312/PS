#include <stdio.h>

int weight[31], ball[7];
int dp[31][30001]; //dp[i][j] : i번째 추까지 사용하여 무게를 만들 수 있는지 여부 , j = (-15000 ~ 15000) + 15000, -는 왼쪽에 두고 +는 오른쪽에 두는 경우

int main(){
    int n, m;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++)
        scanf("%d", &weight[i]);

    scanf("%d", &m);
    for(int i = 0; i < m; i++)
        scanf("%d", &ball[i]);

    dp[0][15000] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= 30000; j++){
            if(dp[i-1][j]){
                dp[i][j - weight[i]] = 1; //i번째 추를 왼쪽에 두는 경우

                dp[i][j] = 1; //i번째 추를 사용하지 않는 경우
                
                dp[i][j + weight[i]] = 1; //i번째 추를 오른쪽에 두는 경우
            }
        }
    }
    for(int i = 0; i < m; i++){
        if(ball[i] <= 15000 && dp[n][ball[i] + 15000])
            printf("Y ");
        else
            printf("N ");
    }
    return 0;
}