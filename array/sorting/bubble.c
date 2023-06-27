#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 6
int main()
{
    int array_int[ARRAY_SIZE] = {4,2,1,2,5,-3};

    printf("           old array: ");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%2d ", array_int[i]);
    }
    printf("\n");

    for (int  k = 0; k < ARRAY_SIZE - 1; k++)
    {

        for (int i = 0; i < ARRAY_SIZE - 1; i++)
        {
            if (array_int[i] > array_int[i+1])
            {
                int temp;
                temp = array_int[i];
                array_int[i] = array_int[i+1];
                array_int[i+1] = temp;

            };
        }
        printf("\narray on iteration %d: ", k+1);
        for (int i = 0; i < ARRAY_SIZE; i++)
        {

            printf("%2d ", array_int[i]);
        }

    }

    printf("\n\n        sorted array: ");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {

        printf("%2d ", array_int[i]);
    }

    return 0;
}
