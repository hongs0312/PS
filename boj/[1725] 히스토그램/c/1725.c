#define MAX(a, b) ((a > b)? a : b)
#define MIN(a, b) ((a < b)? a : b)
#include <stdio.h>

int sticks[100000];

long int find_rac(int l, int r);

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", &sticks[i]);

    printf("%ld", find_rac(0, n-1));

    return 0;
}
long int find_rac(int l, int r){
    int mid = (l+r)/2;
    long int height = sticks[mid];
    long int max = height;

    if(l < r){
        long int l_max = find_rac(l, mid);
        long int r_max = find_rac(mid+1, r);

        max = MAX(max, MAX(l_max, r_max));
    }

    int l_end, r_end; l_end = r_end = mid;
    while(l_end != l && r_end != r){
        if(sticks[l_end-1] >= sticks[r_end+1]){
            l_end--;
            height = MIN(height, sticks[l_end]);
        }
        else{
            r_end++;
            height = MIN(height, sticks[r_end]);
        }
        max = MAX(max, height*(r_end - l_end + 1));
    }
    if(r_end != r){
        for(; r_end <= r; r_end++){
            height = MIN(height, sticks[r_end]);
            max = MAX(max, height*(r_end - l_end + 1));
        }
    }
    else if(l_end != l){
        for(; l_end >= l; l_end--){
            height = MIN(height, sticks[l_end]);
            max = MAX(max, height*(r_end - l_end + 1));
        }
    }
    return max;
}