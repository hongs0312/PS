#include <stdio.h>
#define MAX(a, b) (a > b ? a : b)
#define LEN 1000

int lis[LEN], lds[LEN], input[LEN]; //arr[i] = 길이가 i일 때 만들 수 있는 부분 수열의 최대 길이

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", &input[i]);

    for(int i = 0; i < n; i++){
        lis[i] = 1;
        for(int j = 0; j < i; j++)
            if(input[i] > input[j])
                lis[i] = MAX(lis[i], lis[j] + 1);
    }
    for(int i = n-1; i >= 0; i--){
        lds[i] = 1;
        for(int j = n-1; j > i; j--)
            if(input[i] > input[j])
                lds[i] = MAX(lds[i], lds[j] + 1);
    }
    int max = 0;
    for(int i = 0; i < n; i++)
        max = MAX(max, lis[i] + lds[i] - 1);

    printf("%d", max);

    return 0;
}