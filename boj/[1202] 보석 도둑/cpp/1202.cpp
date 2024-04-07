#include <bits/stdc++.h>

using namespace std;

priority_queue<int> pq;
int bag[300000];
pair<int, int> jewel[300000];
int main(){
    int n, k;
    cin >> n >> k;

    for(int i = 0; i < n; i++)
        cin >> jewel[i].first >> jewel[i].second;

    for(int i = 0; i < k; i++)
        cin >> bag[i];

    //보석 무게 기준 오름차순 정렬
    sort(jewel, jewel+n);

    //가방 무게 기준 오름차순 정렬
    sort(bag, bag+k);

    int idx = 0;
    long long ans = 0;
    for(int i = 0; i < k; i++){
        //가방에 넣을 수 있는 무게보다 가벼운 보석을을 모두 우선순위 큐에 넣음
        while(idx < n && bag[i] >= jewel[idx].first){
            pq.push(jewel[idx].second);
            idx++;
        }
        //우선순위 큐에 있는 가장 비싼 보석을 가방에 넣음
        if(!pq.empty()){
            ans += pq.top();
            pq.pop();
        }
    }
    cout << ans << endl;

    return 0;
}