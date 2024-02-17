#define MIN(a, b) (a < b ? a : b)
#include <stdio.h>

typedef struct node* treePointer;
typedef struct node{
    int left, right;
    int min;
    treePointer leftChild, rightChild;
}node;
treePointer root;

treePointer createNode(int left, int right);
treePointer getSeg(int left, int right);
int getMin(treePointer node, int left, int right);

int input[100000];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++) scanf("%d", &input[i]);

    root = getSeg(0, n - 1);

    for(int i = 0; i < m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", getMin(root, a - 1, b - 1));
    }
    return 0;
}
treePointer createNode(int left, int right){
    treePointer temp = (treePointer)malloc(sizeof(node));

    temp->left = left;
    temp->right = right;
    temp->min = 0;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    
    return temp;
}
treePointer getSeg(int left, int right){
    treePointer temp = createNode(left, right);
    if(left == right){
        temp->min = input[left];
        return temp;
    }
    int mid = (left + right) / 2;

    temp->leftChild = getSeg(left, mid);
    temp->rightChild = getSeg(mid + 1, right);

    temp->min = MIN(temp->leftChild->min, temp->rightChild->min);

    return temp;
}
int getMin(treePointer node, int left, int right){
    if(node->left > right || node->right < left) return 1000000001;
    if(node->left >= left && node->right <= right) return node->min;

    int leftMin = getMin(node->leftChild, left, right);
    int rightMin = getMin(node->rightChild, left, right);

    return MIN(leftMin, rightMin);
}
