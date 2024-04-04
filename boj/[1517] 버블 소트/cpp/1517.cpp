#include <bits/stdc++.h>

using namespace std;

typedef struct node* treePointer;
typedef struct node{
    int left, right;

    long long swapCount;
    int *data;

    treePointer leftChild, rightChild;
} node;
treePointer root;

int input[500000];

treePointer createNode(int left, int right);
treePointer makeTree(int left, int right);
int main(){
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> input[i];

    root = makeTree(0, n - 1);

    cout << root->swapCount;

    return 0;
}
treePointer createNode(int left, int right){
    treePointer temp = new node;
    temp->left = left;
    temp->right = right;

    temp->swapCount = 0;
    temp->data = new int[right - left + 1];
    
    temp->leftChild = temp->rightChild = NULL;
    
    return temp;
}
treePointer makeTree(int left, int right){
    treePointer temp = createNode(left, right);

    if(left == right){
        temp->data[0] = input[left];

        return temp;
    }

    int mid = (left + right) / 2;
    temp->leftChild = makeTree(left, mid);
    temp->rightChild = makeTree(mid + 1, right);

    temp->swapCount = temp->leftChild->swapCount + temp->rightChild->swapCount;

    // MergeSort의 아이디어를 이용한 bubble sort swapCount 계산
    // 버블정렬 swapCount = merge할때 바뀐 자리 수
    int leftIndex = 0, rightIndex = 0, index = 0;
    while(leftIndex < mid - left + 1 && rightIndex < right - mid){
        if(temp->leftChild->data[leftIndex] > temp->rightChild->data[rightIndex]){ // 왼쪽이 더 크면 swap
            temp->data[index++] = temp->rightChild->data[rightIndex++];

            temp->swapCount += mid - left - leftIndex + 1;
        }
        else // 오른쪽이 더 크면 그냥 넣음, swap 없음
            temp->data[index++] = temp->leftChild->data[leftIndex++];
    }

    while(leftIndex < mid - left + 1)
        temp->data[index++] = temp->leftChild->data[leftIndex++];
    
    while(rightIndex < right - mid)
        temp->data[index++] = temp->rightChild->data[rightIndex++];

    return temp;
}