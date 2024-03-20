#include <stdio.h>
#include <math.h>

typedef struct {
    int x, y;
}Vector;
typedef struct {
    Vector center;
    int r;
}Circle;

int main(){
    int t;
    scanf("%d", &t);

    while(t--){
        Vector start, end;
        scanf("%d %d %d %d", &start.x, &start.y, &end.x, &end.y);

        int n;
        scanf("%d", &n);

        Circle c; int result = 0;
        for(int i = 0; i < n; i++){
            scanf("%d %d %d", &c.center.x, &c.center.y, &c.r);

            int startIn = isInside(start, c);
            int endIn = isInside(end, c);

            if(startIn != endIn)
                result++;
        }
        printf("%d\n", result);
    }
    return 0;
}
double getDistance(Vector a, Vector b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
int isInside(Vector v, Circle c){
    return getDistance(v, c.center) < c.r;
}