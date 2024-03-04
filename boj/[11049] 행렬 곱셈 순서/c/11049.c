#define MIN(a, b) ((a) < (b) ? (a) : (b))
#include <stdio.h>

typedef struct{
    int row;
    int col;
}Matrix;
Matrix matrix[500];
unsigned int dp[500][500]; // dp[i][j] = i번째 행렬부터 j번째 행렬까지의 곱셈 연산의 최소값

unsigned int multCnt(int left, int right);

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            dp[i][j] = 0xffffffff;
    
    for(int i = 0; i < n; i++)
        scanf("%d %d", &matrix[i].row, &matrix[i].col);

    printf("%u", multCnt(0, n-1));

    return 0;
}
unsigned int multCnt(int left, int right){
    if(left == right) //base case
        return 0;
    
    if(dp[left][right] != 0xffffffff) // memoization
        return dp[left][right];

    for(int i = left; i < right; i++){
        unsigned int cnt = multCnt(left, i) + multCnt(i+1, right) + matrix[left].row * matrix[i].col * matrix[right].col;
        dp[left][right] = MIN(dp[left][right], cnt);
    }
    return dp[left][right];
}