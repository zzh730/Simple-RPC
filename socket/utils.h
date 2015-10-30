#ifndef GLOBAL_UTILS_H
#define GLOBAL_UTILS_H

int cmpfunc(const void *a, const void *b);
void multiply(int n, int m, int l, int A[n][m], int B[m][l], int C[l][n], int res[n][n]);
int *sort(int size, int *array);
int min(int size, int *array);
int max(int size, int *array);
int wc(char *str);


#endif