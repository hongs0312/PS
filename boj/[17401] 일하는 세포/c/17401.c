#define MOD 1000000007
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int n;
    long long int **matrix;
}Matrix;

long long int getMod(long long int n);
void initMatrix(Matrix* m, int n);
void multMatrix(Matrix* m1, Matrix* m2, Matrix* m3);
void powMatrix(Matrix* m, int n, Matrix* result);
void printMatrix(Matrix* m);

int main(){
    int t, n;
    long long int d;
    scanf("%d %d %lld", &t, &n, &d);

    Matrix* m = (Matrix*)malloc(sizeof(Matrix)*t);

    for(int i = 0; i < t; i++){
        int k;
        scanf("%d", &k);
        initMatrix(&m[i], n);
        for(int j = 0; j < k; j++){
            int row, col, way;
            scanf("%d %d %d", &row, &col, &way);
            m[i].matrix[row-1][col-1] = way;
        }
    }
    Matrix result;
    initMatrix(&result, n);
    if(d == 0){
        printMatrix(&result);
    }
    else if (d >= t){
        for(int i = 0; i < n; i++)
            result.matrix[i][i] = 1;
        
        for(int i = 0; i < t; i++)
            multMatrix(&result, &m[i], &result);
        
        powMatrix(&result, d/t, &result);

        for(int i = 0; i < d%t; i++)
            multMatrix(&result, &m[i], &result);

        printMatrix(&result);
    }
    else{
        for(int i = 0; i < n; i++)
            result.matrix[i][i] = 1;
            
        for(int i = 0; i < d; i++)
            multMatrix(&result, &m[i], &result);
        
        printMatrix(&result);
    }
    return 0;
}
long long int getMod(long long int n){
    return n % MOD;
}
void initMatrix(Matrix* m, int n){
    m->n = n;
    m->matrix = (long long int**)malloc(sizeof(long long int*)*n);
    for(int i = 0; i < n; i++){
        m->matrix[i] = (long long int*)malloc(sizeof(long long int)*n);

        for(int j = 0; j < n; j++)
            m->matrix[i][j] = 0;
    }
}
void freeMatrix(Matrix* m){
    for(int i = 0; i < m->n; i++)
        free(m->matrix[i]);
    free(m->matrix);
}
void multMatrix(Matrix* m1, Matrix* m2, Matrix* m3){    //m3 = m1 * m2
    int n = m1->n;
    Matrix temp;
    initMatrix(&temp, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                temp.matrix[i][j] += getMod(m1->matrix[i][k])*getMod(m2->matrix[k][j]);
                temp.matrix[i][j] %= MOD;
            }
        }
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            m3->matrix[i][j] = temp.matrix[i][j];
    
    freeMatrix(&temp);
}
void powMatrix(Matrix* m, int n, Matrix* result){
    if(n == 1){
        for(int i = 0; i < m->n; i++)
            for(int j = 0; j < m->n; j++)
                result->matrix[i][j] = getMod(m->matrix[i][j]);
            
        return;
    }
    Matrix temp;
    initMatrix(&temp, m->n);
    powMatrix(m, n/2, &temp);
    if(n % 2 == 0){
        multMatrix(&temp, &temp, result);
    }
    else{
        multMatrix(&temp, &temp, &temp);
        multMatrix(&temp, m, result);
    }
    freeMatrix(&temp);
}
void printMatrix(Matrix* m){
    for(int i = 0; i < m->n; i++){
        for(int j = 0; j < m->n; j++){
            printf("%d ", m->matrix[i][j]);
        }
        printf("\n");
    }
}