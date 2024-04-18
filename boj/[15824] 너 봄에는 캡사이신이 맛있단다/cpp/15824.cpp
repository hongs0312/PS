#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

vector <long long> v;
long long powNum[300001];

void getPow(long long n, long long m);
int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    int tmp;
    for(int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());

    getPow(2, n-1);

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        ans += v[i]*(powNum[i] - powNum[n-i-1])%MOD;
        ans %= MOD;
    }
    if(ans < 0)
        ans += MOD;
    
    cout << ans << '\n';

    return 0;
}
void getPow(long long n, long long m) {
    powNum[0] = 1;

    for(int i = 1; i <= m; i++) 
        powNum[i] = (powNum[i-1] * n) % MOD;
}