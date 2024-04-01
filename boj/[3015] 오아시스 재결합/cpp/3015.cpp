#include <bits/stdc++.h>

using namespace std;

stack<pair<long long, long long>> s;
long long input[500000];
long long ans;
int main(){
    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> input[i];

    for(int i = 0; i < n; i++){
        while(!s.empty() && s.top().first < input[i]){
            ans += s.top().second;
            s.pop();
        }
        
        if(s.empty())
            s.push({input[i], 1});
        else if(s.top().first == input[i]){
            ans += s.top().second + (s.size() > 1);

            int tmp = s.top().second ;
            
            s.pop();
            s.push({input[i], tmp + 1});
        }
        else{
            ans++;
            s.push({input[i], 1});
        }
    }
    cout << ans;

    return 0;
}