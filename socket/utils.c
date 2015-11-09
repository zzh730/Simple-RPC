#include <stdio.h>
#include <string.h>
#include <ctype.h>

void swap ( int *a, int *b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int *arr, int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}
 
/* A[] --> Array to be sorted, l  --> Starting index, h  --> Ending index */
void quickSort(int *A, int l, int h)
{
    if (l < h)
    {        
        int p = partition(A, l, h); /* Partitioning index */
        quickSort(A, l, p - 1);  
        quickSort(A, p + 1, h);
    }
}

int *sort(int size, int * array)
{
    quickSort(array, 0, size);
    return array;
}

int min(int size, int *array)
{
    int temp = 32767;
    for(int i=0;i < size;i++)
    {
        if (array[i] < temp)
            temp = array[i];
    }
    return temp;
}

int max(int size, int *array)
{
    int temp = -32768;
    for(int i=0;i < size;i++)
    {
        if (array[i] > temp)
            temp = array[i];
    }
    return temp;
}

int wc(char *str)
{
    int inWord = 0;
    int wordCount = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (!inWord && isalpha(str[i])) 
        {
            inWord = 1;
            wordCount++;
        }
        else if (inWord && str[i] == ' ') 
        {
            inWord = 0;
        }
    }
    return wordCount;
}
void multiply(int n, int m, int l, int p, int A[n][m], int B[m][l], int C[l][p], int res[n][p])
{
    int temp[n][l];
    memset(temp, 0, sizeof(temp));
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < l; j++)
        {
            for (int k = 0; k < m; k++)
            {
                temp[i][j] += A[i][k]*B[k][j]; 
            }
        }
    }
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < l; k++)
            {
                res[i][j] += temp[i][k]*C[k][j]; 
            }
        }
    }

}
