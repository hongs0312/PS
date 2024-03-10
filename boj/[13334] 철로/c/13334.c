#define MAX 100001
#include <stdio.h>
#include <stdlib.h>

typedef struct element{
    int tag;
    int point
}element;
typedef struct {
    element heap[MAX];
    int heapSize;
}HeapType;
HeapType startHeap, endHeap;

typedef struct{
    int start;
    int end;
}line;

void init(HeapType* h);
void push(HeapType* h, element item);
element pop(HeapType* h);

int compare(const void* a, const void* b);

int chk[MAX];
int main(){
    int n;
    scanf("%d", &n);
    init(&startHeap); init(&endHeap);

    line arr[MAX];

    for(int i = 0; i < n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        if(a > b){
            int temp = a;
            a = b;
            b = temp;
        }
        arr[i].start = a;
        arr[i].end = b;
    }
    qsort(arr, n, sizeof(line), compare);

    int d;
    scanf("%d", &d);

    int idx = 0, cnt = 0, max_cnt = 0;
    for(int i = -100000000; i+d <= 100000000; i++){
        element temp;
        while(idx < n && arr[idx].start <= i+d){ //시작점이 범위의 끝보다 왼쪽에 있는 경우 push
            temp.tag = idx;

            temp.point = arr[idx].start;
            push(&startHeap, temp);

            temp.point = arr[idx].end;
            push(&endHeap, temp);
            
            idx++;
        }
        while(endHeap.heapSize && endHeap.heap[1].point <= i+d){
            int tag = pop(&endHeap).tag;
            if(chk[tag] == 0){     //startHeap에 포함돼 있을 경우
                chk[tag] = 1;      // cnt에 포함됨 표시
                cnt++;
            }
        }
        while(startHeap.heapSize && startHeap.heap[1].point < i){
            int tag = pop(&startHeap).tag;
            if(chk[tag] == 1)      // cnt에 포함되어있는 경우
                cnt--;
            
            chk[tag] = -1;
        }
        if(cnt > max_cnt) max_cnt = cnt;
    }
    printf("%d\n", max_cnt);

    return 0;
}
int compare(const void* a, const void* b){
    line* x = (line*)a;
    line* y = (line*)b;
    if(x->start < y->start) return -1;
    else if(x->start > y->start) return 1;
    else{
        if(x->end < y->end) return -1;
        else if(x->end > y->end) return 1;
        else return 0;
    }
}
void init(HeapType* h){
    h->heapSize = 0;
}
void push(HeapType* h, element item){ // min heap
    int i = ++(h->heapSize);
    while(i != 1 && item.point < h->heap[i/2].point){
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}
element pop(HeapType* h){
    int parent = 1, child = 2;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[h->heapSize--];
    while(child <= h->heapSize){
        if(child < h->heapSize && h->heap[child].point > h->heap[child+1].point)
            child++;
        if(temp.point <= h->heap[child].point) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}