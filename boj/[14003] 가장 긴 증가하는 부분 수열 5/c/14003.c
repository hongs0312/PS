#define COMPARE(x, y) (((x) < (y))? -1: ((x) == (y))? 0: 1)
#include <stdio.h>

long int sequence[1000500];
int top = -1;

long int a[1000500][2];
long int output[1000500];

int binsearch(long int list[], int search_num, int left, int right);

int main(){
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        scanf("%ld", &a[i][0]);
    }

    sequence[++top] = a[0][0];
    a[0][1] = top;
    for(int i = 1; i < n; i++){
        if(sequence[top] < a[i][0]){
            a[i][1] = ++top;
            sequence[top] = a[i][0];
        }
        else {
            int idx = binsearch(sequence, a[i][0], 0, top);
            
            if(sequence[idx] > a[i][0]){
                a[i][1] = idx;
                sequence[idx] = a[i][0];
            }
            else a[i][1] = -1;
        }
    }
    int tmp = top;
    for(int i = n-1; i >= 0; i--){
        if(a[i][1] == tmp){
            output[tmp--] = a[i][0];
        }
    }
    printf("%d\n", top+1);
    for(int i = 0; i <= top; i++){
        printf("%ld ", output[i]);
    }
    return 0;
}
int binsearch(long int list[], int search_num, int left, int right){
    int middle;
    while(left < right){
        middle = (left+right)/2;
        switch (COMPARE(list[middle], search_num))
        {
        case -1: 
            left = middle+1;
            break;
        case 0: return middle;
        case 1: 
            right = middle;
            break;
        }
    }
    return right;
}