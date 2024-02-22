#include <stdio.h>

typedef struct{
    int x, y;
}vec;

int outer(vec a, vec b);

int main(){
    vec p1, p2, p3;
    scanf("%d %d", &p1.x, &p1.y);
    scanf("%d %d", &p2.x, &p2.y);
    scanf("%d %d", &p3.x, &p3.y);

    vec a = {p2.x-p1.x, p2.y-p1.y};
    vec b = {p3.x-p2.x, p3.y-p2.y};

    int res = outer(a, b);

    if(res > 0) printf("1");
    else if(res < 0) printf("-1");
    else printf("0");

    return 0;
}
int outer(vec a, vec b){
    return a.x*b.y - a.y*b.x;
}