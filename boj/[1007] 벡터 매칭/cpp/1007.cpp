#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> vec;
double ans;
int t, n;

vector<vec> points;
bool isNeg[20];

vec sumAll();
double getNorm(vec v);
void solve(int idx, int cnt);
int main(){
    ios::sync_with_stdio(false);

    cin >> t;
    while(t--){
        cin >> n;
        points.clear();
        memset(isNeg, false, sizeof(isNeg));

        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            points.push_back({x, y});
        }
        ans = 987654321.0;

        solve(0, 0);

        printf("%lf\n", ans);
    }
    return 0;
}
vec sumAll(){
    vec sum = {0, 0};
    for(int i = 0; i < n; i++){
        if(isNeg[i]){
            sum.first -= points[i].first;
            sum.second -= points[i].second;
        }
        else{
            sum.first += points[i].first;
            sum.second += points[i].second;
        }
    }
    return sum;
}
double getNorm(vec v){
    return sqrt(pow(v.first, 2) + pow(v.second, 2));
}
void solve(int idx, int cnt){
    if(cnt == n / 2){
        vec sum = sumAll();

        ans = min(ans, getNorm(sum));

        return;
    }

    for(int i = idx; i < n; i++){
        isNeg[i] = true;

        solve(i+1, cnt+1);
        
        isNeg[i] = false;
    }
}