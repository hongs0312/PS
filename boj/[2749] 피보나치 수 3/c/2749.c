#define MOD 1000000
#include <stdio.h>

long long int matrix[][2] = {
    {1, 1},
    {1, 0}
};
long long int A[2][2], B[2][2];

void power(long long int b);
void dot(long long int A[][2], long long int B[][2]);

int main(){
    long long int n;
    scanf("%lld", &n);
    if(n == 1)
        printf("1");
    else{
        power(n-1);
        printf("%lld", A[0][0]);
    }
    return 0;
}
void power(long long int b){
    if(b == 1){
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                A[i][j] = matrix[i][j]%MOD;
    }
    else{
        if(b%2){
            power(b/2);
            dot(A, A);
            dot(A, matrix);
        }
        else{
            power(b/2);
            dot(A, A);
        }
    }
}
void dot(long long int matA[][2], long long int matB[][2]){
    long long int tmp;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            tmp = 0;
            for(int k = 0; k < 2; k++){
                tmp += (matA[i][k]*matB[k][j])%MOD;
                tmp %= MOD;
            }
            B[i][j] = tmp%MOD;
        }
    }
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            A[i][j] = B[i][j];
}