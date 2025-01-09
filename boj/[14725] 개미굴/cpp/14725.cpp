/*
개미굴
*/
#include <bits/stdc++.h>

using namespace std;

typedef struct node* node_ptr;
typedef struct node{
    string prey;
    node_ptr sibling, child;
}node;

node_ptr root = NULL;
vector<string> preys_in_a_row;

node_ptr create_node(string str);
node_ptr alloc_strings(node_ptr elder_node, auto cur_prey); //cur_prey: preys_in_a_row의 iterator
void print_result(node_ptr cur_node, int level);
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, k;
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> k;
        preys_in_a_row.clear();

        //한 행 입력
        string input;
        for(int j = 0; j < k; j++) {
            cin >> input;
            preys_in_a_row.push_back(input);
        }
        root = alloc_strings(root, preys_in_a_row.begin()); //preys_in_a_row의 iterator를 넘겨줌
    }
    //결과 출력
    print_result(root, 0);

    return 0;
}

//노드 생성
node_ptr create_node(string str) {
    node_ptr temp = new node;

    temp->prey = str;
    temp->sibling = NULL;
    temp->child = NULL;

    return temp;
}

node_ptr alloc_strings(node_ptr elder_node, auto cur_prey) {
    //입력값의 끝 확인
    if(cur_prey == preys_in_a_row.end())
        return NULL;
    
    //형제 노드 순회 하면서 동일한 먹이 있는지 확인
    node_ptr past_node = NULL;
    node_ptr cur_node = elder_node;
    while(cur_node != NULL && cur_node->prey < *cur_prey) {
        past_node = cur_node;
        cur_node = cur_node->sibling;
    }

    //형제 노드 중 동일한 먹이가 있는 경우
    if(cur_node != NULL && cur_node->prey == *cur_prey) {
        cur_node->child = alloc_strings(cur_node->child, cur_prey+1);

        return elder_node;
    }
    
    //새로운 노드 생성
    node_ptr new_node = create_node(*cur_prey);
    new_node->child = alloc_strings(new_node->child, cur_prey+1);

    //new node 뒤에 오는 형제들 할당
    new_node->sibling = cur_node;

    //past_node가 NULL -> 가장 사전순 앞선다
    if(past_node == NULL)
        elder_node = new_node;
    else
        past_node->sibling = new_node;
    
    //최선임노드 반환
    return elder_node;
}
//결과 출력 with dfs
void print_result(node_ptr cur_node, int level) {
    while(cur_node != NULL) {
        //층의 깊이 만큼 -- 출력
        for(int i = 0; i < level; i++)
            cout << "--";
        cout << cur_node->prey << "\n";

        print_result(cur_node->child, level+1);

        cur_node = cur_node->sibling;
    }
}