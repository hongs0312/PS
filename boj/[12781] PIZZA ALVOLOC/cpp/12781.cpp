#include <bits/stdc++.h>

using namespace std;

typedef pair<long long int, long long int> vec;
typedef struct{
    vec a, b;
}line;

vec sub(vec a, vec b);
int dot(vec a, vec b);
int outer(vec a, vec b);
long long int ccw(vec a, vec b, vec c);
bool isInrange(line l, vec p);
bool canEat(line l1, line l2);

int main(){
    line l1, l2;
    cin >> l1.a.first >> l1.a.second >> l1.b.first >> l1.b.second;
    cin >> l2.a.first >> l2.a.second >> l2.b.first >> l2.b.second;

    if(canEat(l1, l2))
        cout << 1;
    else
        cout << 0;

    return 0;
}
vec sub(vec a, vec b){
    return {a.first - b.first, a.second - b.second};
}
int dot(vec a, vec b){
    return a.first * b.first + a.second * b.second;
}
int outer(vec a, vec b){
    return a.first * b.second - a.second * b.first;
}
long long int ccw(vec a, vec b, vec c){
    long long int res = outer(sub(b, a), sub(c, a));
    
    if(res > 0) return 1;
    if(res < 0) return -1;
    
    return 0;
}
bool isInrange(line l, vec p){
    vec pa = sub(l.a, p);
    vec pb = sub(l.b, p);

    return outer(pa, pb) == 0 && dot(pa, pb) <= 0;
}
bool canEat(line l1, line l2){
    if(isInrange(l1, l2.a) || isInrange(l1, l2.b))
        return false;
    
    if(isInrange(l2, l1.a) || isInrange(l2, l1.b)) 
        return false;

    if(ccw(l1.a, l1.b, l2.a)*ccw(l1.a, l1.b, l2.b) > 0)
        return false;

    if(ccw(l2.a, l2.b, l1.a)*ccw(l2.a, l2.b, l1.b) > 0)
        return false;

    return true;
}