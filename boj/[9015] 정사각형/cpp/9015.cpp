#include <bits/stdc++.h>

using namespace std;

int getDistance(pair<int, int> p1, pair<int, int> p2);
int main(){
    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        set<pair<int, int>>pointSet;

        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            pointSet.insert({x, y});
        }

        int ans = 0;
        for(auto it = pointSet.begin(); it != pointSet.end(); it++){
            for(auto it2 = next(it); it2 != pointSet.end(); it2++){
                pair<int, int> p1 = *it;
                pair<int, int> p2 = *it2;

                int dx = p2.first - p1.first;
                int dy = p2.second - p1.second;
                
                pair<int, int> expected1 = {p1.first + dy, p1.second - dx};
                pair<int, int> expected2 = {p2.first + dy, p2.second - dx};

                if(pointSet.find(expected1) != pointSet.end() && pointSet.find(expected2) != pointSet.end()){
                    ans = max(ans, getDistance(p1, p2));
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
int getDistance(pair<int, int> p1, pair<int, int> p2){
    return pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2);
}