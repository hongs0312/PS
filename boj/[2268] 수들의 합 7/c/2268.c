#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node{
    int left, right;
    long long int value;
    treePointer leftChild, rightChild;
} node;
treePointer root;

treePointer createNode(int left, int right);
treePointer createTree(int left, int right);
void modify(treePointer root, int index, int value);
long long int sum(treePointer root, int left, int right);

int num[1000000];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    root = createTree(0, n - 1);

    for(int i = 0; i < m; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        if(a == 0){
            if(b > c){
                int temp = b;
                b = c;
                c = temp;
            }
            printf("%lld\n", sum(root, b-1, c-1));
        }
        else modify(root, b-1, c);
    }
    return 0;
}
treePointer createNode(int left, int right){
    treePointer temp = (treePointer)malloc(sizeof(node));
    temp->left = left;
    temp->right = right;
    temp->value = 0;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;
}
treePointer createTree(int left, int right){
    if(left == right){
        treePointer temp = createNode(left, right);
        temp->value = num[left];
        return temp;
    }  
    int mid = (left + right) / 2;

    treePointer temp = createNode(left, right);

    temp->leftChild = createTree(left, mid);
    temp->rightChild = createTree(mid + 1, right);

    temp->value = temp->leftChild->value + temp->rightChild->value;

    return temp;
}
void modify(treePointer root, int index, int value){
    if(root->left == root->right){
        root->value = value;
        return;
    }
    int mid = (root->left + root->right) / 2;
    if(index <= mid)
        modify(root->leftChild, index, value);
    else
        modify(root->rightChild, index, value);
    
    root->value = root->leftChild->value + root->rightChild->value;
}
long long int sum(treePointer root, int left, int right){
    if(root->left == left && root->right == right)
        return root->value;
    int mid = (root->left + root->right) / 2;

    if(right <= mid)
        return sum(root->leftChild, left, right);
    else if(left > mid)
        return sum(root->rightChild, left, right);
    else
        return sum(root->leftChild, left, mid) + sum(root->rightChild, mid + 1, right);
}