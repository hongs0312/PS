#define MIN(a, b) (a < b ? a : b)
#define INF 50000000
#include <stdio.h>

int dp[500][500];
int input[501];

int cnt(int left, int right);

int main(){
    int n;
    scanf("%d", &n);
    
    while(n--){
        int m;
        scanf("%d", &m);

        for(int i = 0; i < m; i++)
            for(int j = i; j < m; j++)
                dp[i][j] = INF;

        for(int i = 1; i <= m; i++){
            scanf("%d", &input[i]);

            input[i] += input[i-1];
        }
        for(int i = 0; i < m; i++)
            dp[i][i] = 0;
        
        for(int i = 1; i < m; i++)
            for(int j = 0; j+i < m; j++)
                for(int k = j; k < j+i; k++)
                    dp[j][j+i] = MIN(dp[j][j+i], dp[j][k]+dp[k+1][j+i]+input[j+i+1]-input[j]);
        
        printf("%d\n", dp[0][m-1]);
    }
    return 0;
}