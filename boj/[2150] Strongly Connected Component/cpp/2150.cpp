#include <bits/stdc++.h>

#define MAX 10001

using namespace std;

int id, d[MAX];
bool finished[MAX];
vector<int> adj[MAX];
vector<vector<int>> SCC;
stack<int> s;

int dfs(int x);
int main(){
    ios::sync_with_stdio(false);

    int v, e;
    cin >> v >> e;

    for(int i = 0; i < e; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    for(int i = 1; i <= v; i++)
        sort(adj[i].begin(), adj[i].end());
    
    for(int i = 1; i <= v; i++)
        if(d[i] == 0) dfs(i);

    sort(SCC.begin(), SCC.end());
    cout << SCC.size() << '\n';
    for(int i = 0; i < SCC.size(); i++){
        for(int j = 0; j < SCC[i].size(); j++)
            cout << SCC[i][j] << ' ';
        cout << "-1\n";
    }
    return 0;
}
int dfs(int x){
    d[x] = ++id;
    s.push(x);

    int parent = d[x];
    for(int i = 0; i < adj[x].size(); i++){
        int y = adj[x][i];
        if(d[y] == 0) parent = min(parent, dfs(y));
        else if(!finished[y]) parent = min(parent, d[y]);
    }

    if(parent == d[x]){
        vector<int> scc;
        while(1){
            int t = s.top();
            s.pop();
            scc.push_back(t);
            finished[t] = true;
            if(t == x) break;
        }
        sort(scc.begin(), scc.end());
        SCC.push_back(scc);
    }
    return parent;
}