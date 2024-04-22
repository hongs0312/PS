#include <bits/stdc++.h>

using namespace std;

int rr[] = {-1, 1, 0, 0};
int cc[] = {0, 0, 1, -1};
bool light[10][10];

void input(bool arr[][10]);
void flipLight(bool arr[][10], int r, int c);
int countTrunning(bool arr[][10]);
int solve(int n, int flipCnt);

int main() {
    input(light);

    cout << solve(0, 0);

    return 0;
}

void input(bool arr[][10]) {
    char temp;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> temp;

            if(temp == 'O')
                light[i][j] = true;
            else
                light[i][j] = false;
        }
    }
}

void flipLight(bool arr[][10], int r, int c) {
    arr[r][c] = arr[r][c] ^ true;

    int nr, nc;
    for(int i = 0; i < 4; i++) {
        nr = r + rr[i];
        nc = c + cc[i];

        if(nr < 0 || nc < 0)
            continue;
        
        if(nr >= 10 || nc >= 10)
            continue;

        arr[nr][nc] = arr[nr][nc] ^ true;
    }
}

int countTrunning(bool arr[][10]) {
    int cnt = 0;
    for(int i = 1; i < 10; i++) {
        for(int j = 0; j < 10; j++){
            //arr[i-1][j]가 켜져있으면
            if(arr[i-1][j]) {
                flipLight(arr, i, j);

                cnt++;
            }
        }
    }
    for(int j = 0; j < 10; j++) {
        if(arr[9][j])
            return -1;
    }
    return cnt;
}

int solve(int n, int flipCnt) {
    if(n == 10) {
        bool dup[10][10];

        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++)
                dup[i][j] = light[i][j];

        int result = countTrunning(dup);

        return (result == -1)? result : result+flipCnt;
    }
    
    int a, b;
    a = solve(n+1, flipCnt);
    flipLight(light, 0, n);
    b = solve(n+1, flipCnt+1);
    flipLight(light, 0, n);
    
    if(a != -1 && b != -1)
        return min(a, b);
    else if(a != -1)
        return a;
    else if(b != -1)
        return b;
    else
        return -1;
}