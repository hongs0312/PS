#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

long long fac[4000001];
pair<int, int> input[100000];
void makeFac();
long long getComb(pair<int, int> input);
int main() {
    ios::sync_with_stdio(false);

    makeFac();

    int m;
    cin >> m;
    for(int i = 0; i < m; i++)
        cin >> input[i].first >> input[i].second;

    int n, k;
    for (int i = 0; i < m; i++)
        cout << getComb(input[i]) << '\n';

    return 0;
}
//팩토리얼 생성
void makeFac() {
    fac[0] = 1;
    for (int i = 1; i <= 4000000; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
}
//분할정복을 이용한 거듭제곱
long long getPow(int a, int b) {
    long long result = 1;
    long long base = a;

    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        b /= 2;
    }
    return result;
}
// 페르마의 소정리
// p가 소수이고 a가 p의 배수가 아니라면
// a^p === a (mod p) 
// a^(p - 1) === 1 (mod p)  위에서 a를 나눠줌
// (대충 엄밀한 증명), 합동식도 항등식이랑 비슷한 느낌같다.
// a^(-1) === a^(p - 2) (mod p)
long long getComb(pair<int, int> input) {
    const int n = input.first;
    const int k = input.second;

    const long long nFac = fac[n];
    const long long kFac = fac[k];
    const long long nmkFac = fac[n - k];

    long long result = nFac;
    result = (result * getPow(kFac, MOD - 2)) % MOD;
    result = (result * getPow(nmkFac, MOD - 2)) % MOD;

    return result;
}