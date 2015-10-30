#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void)
{
    printf("Test funcselect:%c\n",funcselect());

    printf("Test inputsize: \n");
    int size = inputsize();
    int *arr;
    arr = (int *) input1darr(size);
    for (int i = 0;i < size; i++)
    {
        printf("A[%d]:%d",i,arr[i]);
    }
    return 0;
}