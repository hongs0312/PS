#include <bits/stdc++.h>

#define INF 1e9

using namespace std;

int input[10001][2];
int dp[10001][3]; //dp[k][0] : k 번째칸 위아래를 다 채웠을때 최소 소대 수 / dp[k][1] : k 번째칸 위만 채웠을때 최소 소대 수 / dp[k][2] : k 번째칸 아래만 채웠을때 최소 소대 수

void initDp();
void solve(int n, int w);
int main(){
    int t;
    cin >> t;

    int n, w, ans;
    int tmp_up, tmp_down;
    while(t--){
        cin >> n >> w;

        for(int j = 0; j < 2; j++)
            for(int i = 1; i <= n; i++)
                cin >> input[i][j];

        if(n == 1){ //n이 1인 경우 예외처리
            ans = (input[1][0]+input[1][1] <= w)? 1 : 2;
            cout << ans << '\n';
            continue;
        }

        //1번째랑 마지막이 이어지지 않은 경우
        dp[1][0] = (input[1][0]+input[1][1] <= w)? 1 : 2;
        dp[1][1] = dp[1][2] = 1;

        ans = INF;
        solve(n, w);
        ans = min(ans, dp[n][0]);

        
        dp[1][0] = 2;
        //1번째 위랑 마지막 위가 이어진 경우
        if(input[1][0]+input[n][0] <= w){
            initDp();

            tmp_up = input[1][0];

            input[1][0] = INF; //1번째 위가 2번째 위랑 이어지는 경우를 제외하기 위해

            solve(n, w);
            ans = min(ans, dp[n][2]);

            input[1][0] = tmp_up;
        }
        
        //1번째 아래랑 마지막 아래가 이어진 경우
        if(input[1][1]+input[n][1] <= w){
            initDp();

            tmp_down = input[1][1];

            input[1][1] = INF; //1번째 아래가 2번째 아래랑 이어지는 경우를 제외하기 위해

            solve(n, w);
            ans = min(ans, dp[n][1]);

            input[1][1] = tmp_down;
        }

        //1번째 위아래랑 마지막 위아래가 이어진 경우
        if(input[1][0]+input[n][0] <= w && input[1][1]+input[n][1] <= w){
            initDp();

            tmp_up = input[1][0];
            tmp_down = input[1][1];

            input[1][0] = input[1][1] = INF; //1번째 위아래가 2번째 위아래랑 이어지는 경우를 제외하기 위해

            solve(n, w);
            ans = min(ans, dp[n-1][0]);

            input[1][0] = tmp_up;
            input[1][1] = tmp_down;
        }

        

        cout << ans << '\n';
    }
    return 0;
}
void initDp(){
    memset(dp, 0, sizeof(dp));

    dp[1][0] = 2;
    dp[1][1] = dp[1][2] = 1;
}
void solve(int n, int w){
    bool upper, lower; //각각 위아래 두 칸의 합이 w를 넘지 않는지 체크
    for(int i = 2; i <= n; i++){
        //i번째와 i-1번째 칸이 이어지는지 체크
        upper = lower = false;
        if(input[i][0]+input[i-1][0] <= w)
            upper = true;

        if(input[i][1]+input[i-1][1] <= w)
            lower = true;

        dp[i][1] = dp[i][2] = dp[i-1][0] + 1; //완전히 채워진 i-1번째까지에 1개가 더 붙는 경우
        dp[i][0] = dp[i-1][0] + 2;
        if(input[i][0]+input[i][1] <= w)
            dp[i][0] = dp[i-1][0] + 1;

        if(upper && lower)
            dp[i][0] = min(dp[i][0], dp[i-2][0] + 2);
        
        if(upper){
            dp[i][0] = min(dp[i][0], dp[i-1][2] + 2);
            dp[i][1] = min(dp[i][1], dp[i-1][2] + 1);
        }

        if(lower){
            dp[i][0] = min(dp[i][0], dp[i-1][1] + 2);
            dp[i][2] = min(dp[i][2], dp[i-1][1] + 1);
        }
    }
}