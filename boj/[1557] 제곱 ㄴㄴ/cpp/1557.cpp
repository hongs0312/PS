#include <bits/stdc++.h>

#define MAX 47000

using namespace std;

bool num[MAX];
vector<int> prime;

int sqCnt[MAX];

void getPrime();
int getCnt(int idx, int num, int x, bool include);
int main(){
    ios::sync_with_stdio(false);

    int k;
    cin >> k;

    getPrime();

    long long left = k, right = k*2 + 1, mid, cnt;
    int n;
    while(left < right) {
        mid = (left + right) / 2;
        
        for(int i = 2; i*i <= mid; i++) //mid보다 작은 각 제곱수의 배수 개수
            sqCnt[i] = mid/(i*i);

        n = mid - getCnt(0, 1, mid, true); //n번째 제곱 ㄴㄴ수

        if(n > k) right = mid - 1;
        else if (n < k) left = mid + 1;
        else right = mid;
    }
    cout << left << endl;

    return 0;
}
void getPrime() {
    for(int i = 2; i*i < MAX; i++) {
        if(num[i] == false) {
            for(int j = i+i; j < MAX; j += i)
                num[j] = true;
        }
    }
    for(int i = 2; i < MAX; i++) {
        if(num[i] == false)
            prime.push_back(i);
    }
}
// idx : 소수 인덱스, num : 현재까지의 소수 곱, x : 입력값, include : 현재 소수를 포함인가 배제인가
int getCnt(int idx, int num, int x, bool include) {
    int result, ret = 0, cnt;
    long long primeComb;
    for(int i = idx; i < prime.size(); i++) {
        primeComb = num*prime[i];

        if(primeComb*primeComb > x)
            break;

        cnt = sqCnt[primeComb];
        if(include == false)
            cnt *= -1;

        ret += cnt;
        ret += getCnt(i+1, primeComb, x, !include);
    }
    return ret;
}