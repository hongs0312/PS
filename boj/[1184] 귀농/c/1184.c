#define MAX_BUCKET 1000
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sum;
    int cnt;
}element;

typedef struct node* nodePointer;
typedef struct node{
    element data;
    nodePointer link;
}node;
nodePointer ht[MAX_BUCKET];

int farm[51][51];

int get_key(int x);
int h(int x);
void intsert(int sum);
element* search(int sum);
void reset_ht();

int main(){
    int n;
    scanf("%d", &n);

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &farm[i][j]);
            farm[i][j] += farm[i-1][j] + farm[i][j-1] - farm[i-1][j-1];
        }
    }
    int cnt = 0;
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            for(int ulr = 0; ulr < i; ulr++){
                for(int ulc = 0; ulc < j; ulc++){
                    int sum = farm[i][j] - farm[ulr][j] - farm[i][ulc] + farm[ulr][ulc];
                    intsert(sum);
                }
            }
            for(int drr = i+1; drr <= n; drr++){
                for(int drc = j+1; drc <= n; drc++){
                    int sum = farm[drr][drc] - farm[i][drc] - farm[drr][j] + farm[i][j];
                    
                    element* item = search(sum);
                    if(item) cnt += item->cnt;
                }
            }
            reset_ht();
            for(int urr = 0; urr < i; urr++){
                for(int urc = j+1; urc <= n; urc++){
                    int sum = farm[i][urc] - farm[urr][urc] - farm[i][j] + farm[urr][j];
                    intsert(sum);
                }
            }
            for(int dlr = i+1; dlr <= n; dlr++){
                for(int dlc = 0; dlc < j; dlc++){
                    int sum = farm[dlr][j] - farm[i][j] - farm[dlr][dlc] + farm[i][dlc];
                    
                    element* item = search(sum);
                    if(item) cnt += item->cnt;
                }
            }
            reset_ht();
        }
    }
    printf("%d", cnt);

    return 0;
}
int get_key(int x){
    return x + 2500000;
}
int h(int x){
    return x % MAX_BUCKET;
}
void intsert(int sum){
    int key = get_key(sum);
    int homeBucket = h(key);
    nodePointer post = NULL, temp = ht[homeBucket];
    while(temp != NULL){
        if(temp->data.sum == sum){
            temp->data.cnt++;
            return;
        }
        post = temp;
        temp = temp->link;
    }
    nodePointer slot = (nodePointer)malloc(sizeof(node));
    slot->data.sum = sum;
    slot->data.cnt = 1;
    slot->link = NULL;

    if(post) post->link = slot;
    else ht[homeBucket] = slot;
}
element* search(int sum){
    int key = get_key(sum);
    int homeBucket = h(key);
    nodePointer temp = ht[homeBucket];
    while(temp != NULL){
        if(temp->data.sum == sum)
            return &temp->data;
        temp = temp->link;
    }
    return NULL;
}
void reset_ht(){
    for(int i = 0; i < MAX_BUCKET; i++){
        nodePointer temp = ht[i];
        while(temp != NULL){
            nodePointer next = temp->link;
            free(temp);
            temp = next;
        }
        ht[i] = NULL;
    }
}