#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> point;
point points[100000];

bool cmp(point a, point b){
    return a.second < b.second;
}
int dist(point a, point b);
int solve(int left, int right);
int main(){
    int n;
    cin >> n;

    int x, y;
    for(int i = 0; i < n; i++){    
        cin >> x >> y;
        points[i] = {x, y};
    }
    sort(points, points+n);

    int ans = solve(0, n-1);

    cout << ans;

    return 0;
}
int dist(point a, point b){
    return pow(a.first - b.first, 2) + pow(a.second - b.second, 2);
}
int solve(int left, int right){
    if(left == right) return 0x7fffffff;

    int mid = (left + right) / 2;

    int leftMin = solve(left, mid);
    int rightMin = solve(mid+1, right);

    int minDist = min(leftMin, rightMin);

    vector<point> candidate;
    double midX = (points[mid].first + points[mid+1].first) / 2;
    for(int i = left; i <= right; i++){
        if(pow(points[i].first - midX, 2) < minDist)
            candidate.push_back(points[i]);
    }

    sort(candidate.begin(), candidate.end(), cmp);

    for(int i = 0; i < candidate.size(); i++){
        for(int j = i+1; j < candidate.size(); j++){
            if(pow(candidate[i].second - candidate[j].second, 2) > minDist)
                break;
            minDist = min(minDist, dist(candidate[i], candidate[j]));
        }
    }
    
    return minDist;
}