#include <bits/stdc++.h>

using namespace std;

int rr[] = {1, 1, -1, -1};
int cc[] = {1, -1, 1, -1};

int board[10][10];

int answer = 0;

void markAttack(int r, int c, int mode); // mode -1: 비숍을 치운다 1: 비숍을 놓는다
void solve(int n, int recur, int r, int c);
int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    int tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            board[i][j] = tmp^1; // 0: 비숍을 놓을 수 있는 곳 1: 비숍을 놓을 수 없는 곳
        }
    }

    solve(n, answer, 0, 0); // 0, 0부터 시작 흰 색 칸
    solve(n, answer, 0, 1); // 0, 1부터 시작 검은 색 칸

    cout << answer << '\n';

    return 0;
}
void markAttack(int r, int c, int mode) {
    for (int i = 0; i < 4; i++) {
        int rr = r, cc = c;
        
        board[rr][cc] += mode;
        while (true) {
            rr += ::rr[i];
            cc += ::cc[i];

            if (rr < 0 || rr >= 10 || cc < 0 || cc >= 10)
                break;

            board[rr][cc] += mode;
        }
    }
}
void solve(int n, int recur, int r, int c) {
    //체스판 순회
    int i = r, j = c;
    for(; i < n; i++) {
        for(; j < n; j = j+2) {
            if(board[i][j] == 0) {
                markAttack(i, j, 1);
                solve(n, recur + 1, i, j);
                markAttack(i, j, -1);
            }
        }
        j = (j+1)%2;
    }
    //체스판을 다 돌았을 때 가장 큰 값을 저장
    answer = max(answer, recur);
}