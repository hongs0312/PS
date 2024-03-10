#define MOD 1000000007
#include <stdio.h>

typedef struct node* treePointer;
typedef struct node{
    int left, right;
    long long int value;
    treePointer leftChild, rightChild;
} node;
treePointer root;

treePointer createNode(int left, int right);
treePointer makeSeg(int left, int right);
void update(treePointer root, int idx, int value);
long long int getMul(treePointer root, int left, int right);

int input[1000000];

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for(int i = 0; i < n; i++)
        scanf("%d", &input[i]);

    root = makeSeg(0, n - 1);

    for(int i = 0; i < m + k; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        if(a == 1) update(root, b - 1, c);
        else printf("%lld\n", getMul(root, b - 1, c - 1));
    }
    return 0;
}
treePointer createNode(int left, int right){
    treePointer temp = (treePointer)malloc(sizeof(node));
    temp->left = left;
    temp->right = right;
    temp->value = 0;
    temp->leftChild = temp->rightChild = NULL;
    
    return temp;
}
treePointer makeSeg(int left, int right){
    if(left == right){
        treePointer temp = createNode(left, right);
        temp->value = input[left]%MOD;
        return temp;
    }
    int mid = (left + right) / 2;
    treePointer temp = createNode(left, right);

    temp->leftChild = makeSeg(left, mid);
    temp->rightChild = makeSeg(mid + 1, right);

    long long int leftValue = temp->leftChild->value;
    long long int rightValue = temp->rightChild->value;

    temp->value = (leftValue*rightValue)%MOD;

    return temp;
}
void update(treePointer root, int idx, int value){
    if(root->left == root->right){
        root->value = value;
        return;
    }
    int mid = (root->left + root->right) / 2;
    if(idx <= mid)
        update(root->leftChild, idx, value);
    else
        update(root->rightChild, idx, value);
    
    root->value = (root->leftChild->value*root->rightChild->value)%MOD;
}
long long int getMul(treePointer root, int left, int right){
    if(root->left > right || root->right < left)
        return 1;
    if(root->left >= left && root->right <= right)
        return root->value;
    return (getMul(root->leftChild, left, right)*getMul(root->rightChild, left, right))%MOD;
}