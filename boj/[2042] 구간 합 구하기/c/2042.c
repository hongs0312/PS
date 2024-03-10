#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node{
    int left, right;   //구간
    long long int sun; //구간합
    treePointer leftChild, rightChild;
}node;
treePointer root;

treePointer createNode(int left, int right);
treePointer createTree(int left, int right);
long long int getSum(treePointer root, int left, int right);
void update(treePointer root, int index, long long int value);

long long int input[1000000];
int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for(int i = 0; i < n; i++)
        scanf("%lld", &input[i]);

    root = createTree(0, n-1);

    for(int i = 0; i < m+k; i++){
        int a, b;
        long long int c;
        scanf("%d %d %lld", &a, &b, &c);

        if(a == 1)
            update(root, b-1, c);
        else
            printf("%lld\n", getSum(root, b-1, c-1));
    }
    return 0;
}
treePointer createNode(int left, int right){
    treePointer temp = (treePointer)malloc(sizeof(node));
    temp->left = left;
    temp->right = right;
    temp->sun = 0;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;
}
treePointer createTree(int left, int right){
    treePointer temp = createNode(left, right);
    if(left == right){
        temp->sun = input[left];
        return temp;
    }
    int mid = (left + right) / 2;
    temp->leftChild = createTree(left, mid);
    temp->rightChild = createTree(mid+1, right);
    temp->sun = temp->leftChild->sun + temp->rightChild->sun;

    return temp;
}
long long int getSum(treePointer root, int left, int right){
    if(root->left > right || root->right < left)
        return 0;
    if(root->left >= left && root->right <= right)
        return root->sun;
    return getSum(root->leftChild, left, right) + getSum(root->rightChild, left, right);
}
void update(treePointer root, int index, long long int value){
    if(root->left > index || root->right < index)
        return;
    if(root->left == index && root->right == index){
        root->sun = value;
        return;
    }
    update(root->leftChild, index, value);
    update(root->rightChild, index, value);
    root->sun = root->leftChild->sun + root->rightChild->sun;
}