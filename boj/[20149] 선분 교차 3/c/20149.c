#include <stdio.h>
typedef struct {
    long long int x;
    long long int y;
}vector;
 
typedef struct {
    vector a;
    vector b;
}line;
line l1, l2;

vector sub(vector a, vector b);
long long int outer(vector a, vector b);

int ccw(vector a, vector b, vector c);
int in_range(line ln, vector q);
int compare(vector a, vector b);

int main(){
    scanf("%lld %lld %lld %lld", &l1.a.x, &l1.a.y, &l1.b.x, &l1.b.y);
    scanf("%lld %lld %lld %lld", &l2.a.x, &l2.a.y, &l2.b.x, &l2.b.y);
    
    int state = 0;
    int result[] = {1, 1};
    result[0] *= ccw(l1.a, l1.b, l2.a);
    result[0] *= ccw(l1.a, l1.b, l2.b);

    result[1] *= ccw(l2.a, l2.b, l1.a);
    result[1] *= ccw(l2.a, l2.b, l1.b);

    if(result[0] < 0 && result[1] < 0)
        state = 1;
    else if(result[0]*result[1] == 0){
        if(in_range(l1, l2.a))
            state = 1;
        else if(in_range(l1, l2.b))
            state = 1;
        else if(in_range(l2, l1.a))
            state = 1;
        else if(in_range(l2, l1.b))
            state = 1;
    }
    
    printf("%d\n", state);
    if(state){
        vector ab, cd;
        ab = sub(l1.a, l1.b); cd = sub(l2.a, l2.b);
        double basin = (double)outer(ab, cd);
        if(basin){
            double x = (outer(l1.a, l1.b)*cd.x-outer(l2.a, l2.b)*ab.x)/basin;
            double y = (outer(l1.a, l1.b)*cd.y-outer(l2.a, l2.b)*ab.y)/basin;

            printf("%.10lf %.10lf", x, y);
        }
        else if(compare(l1.a, l2.a) && !in_range(l1, l2.b) && !in_range(l2, l1.b))
            printf("%lld %lld", l1.a.x, l1.a.y);
        else if(compare(l1.a, l2.b) && !in_range(l1, l2.a) && !in_range(l2, l1.b))
            printf("%lld %lld", l1.a.x, l1.a.y);
        else if(compare(l1.b, l2.a) && !in_range(l1, l2.b) && !in_range(l2, l1.a))
            printf("%lld %lld", l1.b.x, l1.b.y);
        else if(compare(l1.b, l2.b) && !in_range(l1, l2.a) && !in_range(l2, l1.a))
            printf("%lld %lld", l1.b.x, l1.b.y);
    }
    return 0;
}
vector sub(vector a, vector b){
    vector result = {a.x-b.x, a.y-b.y};
    return result;
}
long long int outer(vector a, vector b){
    return a.x*b.y - a.y*b.x;
}
int ccw(vector a, vector b, vector c){
    b = sub(b, a);
    c = sub(c, a);

    long long int result = outer(b, c);
    
    return (result < 0)? -1 : (result > 0)? 1 : 0;
}
int in_range(line ln, vector q){
    vector a = sub(ln.a, q);
    vector b = sub(ln.b, q);
    if((a.x == 0 && a.y == 0) || (b.x == 0 && b.y == 0))
        return 1;
    else if((a.x*b.x < 0 || a.y*b.y < 0) && outer(a, b) == 0)
        return 1;
    return 0;
}
int compare(vector a, vector b){
    if(a.x == b.x && a.y == b.y)
        return 1;
    return 0;
}