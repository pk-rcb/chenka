#include <stdio.h>
#include <stdlib.h>

void add(int n, int A[][n], int B[][n], int C[][n]) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[][n], int B[][n], int C[][n]) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            C[i][j] = A[i][j] - B[i][j];
}

void multiply(int n, int A[][n], int B[][n], int C[][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;

    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int T1[k][k], T2[k][k];

    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    multiply(k, A11, B11, C11);
    multiply(k, A12, B21, C12);
    multiply(k, A11, B12, C21);
    multiply(k, A12, B22, C22);

    add(k, C11, C12, T1);
    add(k, C21, C22, T2);

    multiply(k, A21, B11, C11);
    multiply(k, A22, B21, C12);
    multiply(k, A21, B12, C21);
    multiply(k, A22, B22, C22);

    add(k, C11, C12, C11);
    add(k, C21, C22, C21);

    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++) {
            C[i][j] = T1[i][j];
            C[i][j + k] = C21[i][j];
            C[i + k][j] = C11[i][j];
            C[i + k][j + k] = C21[i][j];
        }
}

int main() {
    int n;
    printf("Enter size of matrix (power of 2): ");
    scanf("%d", &n);

    int A[n][n], B[n][n], C[n][n];

    printf("Enter matrix A:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d", &B[i][j]);

    multiply(n, A, B, C);

    printf("\nResult Matrix:\n");
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
