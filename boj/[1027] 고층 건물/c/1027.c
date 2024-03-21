#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN_SLOPE -1000000000

int building[50], can_see[50];

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", &building[i]);

    for(int i = 0; i < n; i++){
        double max = MIN_SLOPE;
        for(int j = i+1; j < n; j++){
            double slope = (double)(building[j] - building[i]) / (j - i);
            if(slope > max){
                max = slope;

                can_see[i]++;
                can_see[j]++;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++)
        ans = MAX(ans, can_see[i]);
    
    printf("%d", ans);
    
    return 0;
}