#include <stdio.h>

unsigned long long int count_ones(long long int x);

int main(){
    unsigned long long int a, b;
    scanf("%llu %llu", &a, &b);

    printf("%llu", count_ones(b) - count_ones(a-1));

    return 0;
}
unsigned long long int count_ones(long long int x){
    unsigned long long int count = 0;
    unsigned long long int left_mask = 0xfffffffffffffffe, middle_mask = 1, right_mask = 0;
    while(middle_mask <= x){
        count += ((x&left_mask)>>1);
        if(x&middle_mask) 
            count += (x&right_mask) + 1;

        right_mask = (right_mask<<1) + 1;
        middle_mask = middle_mask<<1;
        left_mask = left_mask<<1;
    }
    return count;
}