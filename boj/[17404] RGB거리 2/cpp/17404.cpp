#include <bits/stdc++.h>

using namespace std;

int house[1000][3];
int dp[1000][3];

int painting(int n, int firstColor);
int main() {
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> house[i][0] >> house[i][1] >> house[i][2];

    int ans = 1e9;
    for (int i = 0; i < 3; i++) 
        ans = min(ans, painting(n, i));

    cout << ans << '\n';

    return 0;
}
int painting(int n, int firstColor) {
    for(int i = 0; i < 3; i++)
        if(i != firstColor) dp[0][i] = 1e9;
        else dp[0][i] = house[0][firstColor];

    for(int i = 1; i < n; i++) {
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + house[i][0];
        dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + house[i][1];
        dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + house[i][2];
    }

    int ret = 1e9;
    for(int i = 0; i < 3; i++) {
        if(i != firstColor)
            ret = min(ret, dp[n-1][i]);
    }

    return ret;
}