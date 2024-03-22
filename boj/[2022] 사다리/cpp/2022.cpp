#include <bits/stdc++.h>

using namespace std;

double f(double x, double y, double z){
    double h1 = sqrt(x*x - z*z); double h2 = sqrt(y*y - z*z);
    return (h1*h2)/(h1+h2);
}

int main(){
    double x, y, c;
    cin >> x >> y >> c;
    
    double z;
    double left = 0, right = min(x, y);
    while(abs(right-left) > 1e-6){
        z = (left+right)/2;
        
        double n = f(x, y, z);

        if(n > c) left = z;
        else right = z;
    }
    cout << fixed << setprecision(3) << z << '\n';

    return 0;
}