#include <bits/stdc++.h>

using namespace std;

long long pageCnt[10]; //페이지 카운트, pageCnt[i] = i의 개수

void solve(int n);
int main() {
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    if(n == 1) pageCnt[1] = 1;
    else solve(n);

    for(int i = 0; i < 10; i++)
        cout << pageCnt[i] << ' ';

    return 0;
}
void solve(int n) {
    //start = 시작 페이지, end = 끝 페이지
    //if start = 10, end = 39 -> 각 1의 자리수에서 0~9 출현횟수 = (3 - 1 + 1) = 3
    int start = 1, end = n;
    int digit = 1;

    long long cnt;
    while(start <= end) {
        //start와 end의 1의 자리를 0과 9로 만들어주는 과정
        while(start % 10 != 0 && start <= end) {
            for(int i = start; i > 0; i /= 10)
                pageCnt[i % 10] += digit;
            start++;
        }
        if(start > end) break;

        while(end % 10 != 9 && start <= end) {
            for(int i = end; i > 0; i /= 10)
                pageCnt[i % 10] += digit;
            end--;
        }
        if(start > end) break;

        //0 ~ 9까지 얼마가 나왔는지 카운트
        cnt = end/10 - start/10 + 1;
        for(int i = 0; i < 10; i++)
            pageCnt[i] += cnt*digit;

        start /= 10;  end /= 10;
        digit *= 10;
    }
}