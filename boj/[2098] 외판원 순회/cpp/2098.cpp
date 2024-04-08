#include <bits/stdc++.h>

using namespace std;

int adj[16][16];
long long dp[16][1 << 16];
long long tsp(int n, int cur, int visited);
int main(){
    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> adj[i][j];

    memset(dp, -1, sizeof(dp));
    cout << tsp(n, 0, 1) << "\n";

    return 0;
}
long long tsp(int n, int cur, int visited){
    if(visited == (1 << n) - 1){ //모든 도시를 돌았을 때
        if(adj[cur][0] == 0) return 1e9;
        return adj[cur][0];
    }

    if(dp[cur][visited] != -1) return dp[cur][visited]; //이미 방문한 도시일 때

    dp[cur][visited] = 1e9;
    for(int i = 0; i < n; i++){
        //visited & (1 << i) : i번째 도시를 방문했는지 확인
        //adj[cur][i] == 0 : cur에서 i로 갈 수 없는 경우
        if(visited & (1 << i) || adj[cur][i] == 0) continue;

        //i번째 도시를 방문한 상태로 재귀 호출
        dp[cur][visited] = min(dp[cur][visited], tsp(n, i, visited | (1 << i)) + adj[cur][i]);
    }

    return dp[cur][visited];
}