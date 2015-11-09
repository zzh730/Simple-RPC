//
//  multiply.c
//  simplerpc
//
//  Created by Zihao  Zhao on 11/8/15.
//  Copyright © 2015 Zihao  Zhao. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

void print1darr(int size, int *arr)
{
    for (int i = 0; i < size; i++)
    {
        printf("ARR[%d]:%d",i,arr[i] );
    }
}

void printarr(int m, int n, int *arr)
{
    for (int i = 0;i < m;i++)
    {
        for (int j = 0; j < n; j++)
            {
                printf("Arr[%d][%d]:%d",i,j,arr[i*n+j]);
            }
    }
}



void multiply(int n, int m, int l, int A[n*m], int B[m*l], int C[l*n], int res[n*n])
{
    int temp[n*l];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            int sum = 0;
            for (int k = 0; k < m; k++)
                sum = sum + A[i * m + k] * B[k * l + j];
            temp[i * n + j] = sum;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < l; k++)
                sum = sum + temp[i * l + k] * C[k * n + j];
            res[i * n + j] = sum;
        }
    }
    printarr(n,n,res);
    print1darr(n*n,res);
}
int inputsize()
{
    int size;
    printf("Please enter the size of the array\n");
    scanf("%d", &size);
    return size;
}

int *input1darr(int size)
{
    int arr[size];
    printf("Please enter the array\n");
    for (int i = 0;i < size;i++)
    {
        scanf("%d", &arr[i]);
        
    }
    return arr;
    
}

int *input2darr(int m, int n)
{
    int arr[m*n];
    printf("Please the element of array\n");
    for (int i = 0; i < m*n; i++)
    {
        scanf("%d", &arr[i]);
        
    }
    return arr;
}

void trans(int m, int n, int arr[m*n], int res[m][n])
{
    for (int i = 0; i < m*n;i++)
    {
        res[(int)i/n][(int)i%n]= arr[i];
        
    }
}

int main()
{
    
    int m1,n1,m2,n2,m3,n3;
    int *arr1, *arr2,*arr3;
    // int A[m1][n1],B[m2][n2],C[m3][n3],res[m1][n3];
    printf("Please enter the size of the row\n");
    scanf("%d", &m1);
    printf("Please enter the size of the column\n");
    scanf("%d", &n1);
    arr1 = input2darr(m1,n1);
    // trans(m1,n1,arr1,A);
    
    printf("Please enter the size of the row\n");
    scanf("%d", &m2);
    printf("Please enter the size of the column\n");
    scanf("%d", &n2);
    arr2 = input2darr(m2,n2);
    // trans(m2,n2,arr2,B);
    
    printf("Please enter the size of the row\n");
    scanf("%d", &m3);
    printf("Please enter the size of the column\n");
    scanf("%d", &n3);
    arr3 = input2darr(m3,n3);
    // trans(m3,n3,arr3,C);
    int res[m1*n3];
    // multiply(m1,n1,n3,A[m1][n1],B[m2][n2],C[m3][n3],res[m1][n3]);
    multiply(m1,n1,n3,arr1,arr2,arr3,res);
    
    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            printf("Arr[%d][%d]:%d", i,j,res[i*m1+j]);
        }
    }

}