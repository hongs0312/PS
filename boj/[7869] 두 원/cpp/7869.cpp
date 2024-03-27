#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> vec;
typedef struct{
    vec c;
    double r;
}circle;

double dist(vec a, vec b);
double getIntersectArea(circle c1, circle c2);
int main(){
    circle c1, c2;
    cin >> c1.c.first >> c1.c.second >> c1.r;
    cin >> c2.c.first >> c2.c.second >> c2.r;

    double d = dist(c1.c, c2.c);

    double big_r = max(c1.r, c2.r);
    double small_r = min(c1.r, c2.r);
    
    double result;
    if(d+small_r <= big_r) //한 원이 다른 원을 포함하는 경우
        result = pow(small_r, 2)*M_PI;
    else if(small_r + big_r <= d) //두 원의 공통부분이 없는 경우
        result = 0;
    else //두 원이 일부분 겹치는 경우
        result = getIntersectArea(c1, c2);
    
    cout << fixed << setprecision(3) << result;
    
    return 0;
}
double dist(vec a, vec b){  
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}
double getIntersectArea(circle c1, circle c2){
    double d = dist(c1.c, c2.c);
    double r1 = c1.r; 
    double r2 = c2.r;

    double cosAlpha = (pow(r1, 2) + pow(d, 2) - pow(r2, 2)) / (2*r1*d);
    double alpha = acos(cosAlpha);

    double cosBeta = (pow(r2, 2) + pow(d, 2) - pow(r1, 2)) / (2*r2*d);
    double beta = acos(cosBeta);

    double s1 = pow(r1, 2)*(alpha - sin(2*alpha)/2);
    double s2 = pow(r2, 2)*(beta - sin(2*beta)/2);

    return s1 + s2;
}