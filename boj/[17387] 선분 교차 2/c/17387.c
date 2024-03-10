#include <stdio.h>

typedef struct {
    long int x;
    long int y;
}vector;

vector sub(vector a, vector b);
long int outer(vector a, vector b);

int ccw(vector a, vector b, vector c);

int in_range(vector p1, vector p2, vector q);

int main(){
    vector line[2][2];

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            scanf("%ld %ld", &line[i][j].x, &line[i][j].y);

    int result[] = {1, 1};
    for(int i = 0; i < 2; i++){
        result[i] *= ccw(line[i][0], line[i][1], line[1-i][0]);
        result[i] *= ccw(line[i][0], line[i][1], line[1-i][1]);
    }

    if(result[0] < 0 && result[1] < 0)
        printf("1");
    else if(result[0]*result[1] == 0){
        int chk = 0;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                if(in_range(line[i][0], line[i][1], line[1-i][j]))
                    chk = 1;
        if(chk)
            printf("1");
        else printf("0");
    }
    else printf("0");

    return 0;
}
vector sub(vector a, vector b){
    vector result = {a.x-b.x, a.y-b.y};
    return result;
}
long int outer(vector a, vector b){
    return a.x*b.y - a.y*b.x;
}
int ccw(vector a, vector b, vector c){
    b = sub(b, a);
    c = sub(c, a);

    long int result = outer(b, c);
    
    return (result < 0)? -1 : (result > 0)? 1 : 0;
}
int in_range(vector p1, vector p2, vector q){
    vector a = sub(p1, q);
    vector b = sub(p2, q);
    if((a.x == 0 && a.y == 0) || (b.x == 0 && b.y == 0))
        return 1;
    else if((a.x*b.x < 0 || a.y*b.y < 0) && outer(a, b) == 0)
        return 1;
    return 0;
}