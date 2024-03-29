#include <bits/stdc++.h>

using namespace std;

vector<int> kmpSearch(string s, string p);
vector<int> getPartialMatch(string p);
int main(){
    string s, p;
    getline(cin, s);
    getline(cin, p);

    vector<int> ans = kmpSearch(s, p);

    cout << ans.size() << '\n';
    for(int i = 0; i < ans.size(); i++)
        cout << ans[i] + 1 << ' ';

    return 0;
}
vector<int> kmpSearch(string s, string p){
    int n = s.size(); //원본 문자열의 길이
    int m = p.size(); //찾을 문자열의 길이

    vector<int> ret; // 찾은 위치를 저장할 벡터
    vector<int> pi;  // 찾을 문자열의 pi 배열

    //pi 배열을 구하기
    pi = getPartialMatch(p);

    int begin = 0, matched = 0; //begin: s의 현재 위치, matched: 찾을 문자열과 일치하는 길이
    while(begin <= n - m){
        if(matched < m && s[begin + matched] == p[matched]){ // 일치하는 경우
            matched++;

            //찾을 문자열을 찾은 경우
            if(matched == m) ret.push_back(begin);
        }
        else{ // 일치하지 않는 경우 or 찾을 문자열을 찾은 경우
            if(matched == 0)
                begin++;
            else{
                //현재 위치에서 접미사의 시작위치로 이동
                begin += matched - pi[matched - 1]; 

                //접두사 == 접미사이므로 이전 문자열의 접두사 길이만큼은 일치함
                matched = pi[matched - 1];
            }
        }
    }
    return ret;
}
vector<int> getPartialMatch(string p){
    int m = p.size();
    vector<int> pi(m, 0);

    //KMP로 자기 자신을 찾는다
    //N에서 N을 찾는다. begin = 0이면 자기 자신을 찾아버리니까 안됨
    int begin = 1, matched = 0;
    while(begin + matched < m){
        if(p[begin + matched] == p[matched]){
            matched++;

            pi[begin + matched - 1] = matched;
        }
        else{
            if(matched == 0)
                begin++;
            else{
                begin += matched - pi[matched - 1];

                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}