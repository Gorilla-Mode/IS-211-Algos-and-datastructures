#include <stdio.h>
#include <stdint-gcc.h>
#include <string.h>

typedef struct
{
    int32_t length;
    int32_t capacity;
    int32_t *items;
}Int32array;

int32_t Int32arrayGet (Int32array array, int32_t i)
{
    if (array.capacity < i)
    {
        return 0; 
    }
    
    return array.items[i];
}


int32_t linSearch(int32_t val, const Int32array arr)
{
    for (int32_t i = 0; i < arr.length; ++i)
    {
        if (arr.items[i] == val)
        {
           return i; 
        }
    }
    return -1;
}

int countOccurrence(int32_t val, const Int32array arr)
{
    
    int32_t count = 0;
    for (int32_t i = 0; i < arr.length; ++i)
    {
        if (arr.items[i] == val)
        {
            count++;
        }
    }
    return count;
}

int main(void)
{
    //fr easier in c than python (skull emoji, skull emoji)
    int32_t stack_buf[16];
    Int32array arr = {
        .capacity = sizeof(stack_buf) / sizeof(stack_buf[0]),
        .items =  stack_buf
    };

   int32_t seedVals[] = {1,3,5,9,9,2,3,43,1,3};

    memcpy(arr.items, seedVals, sizeof(seedVals));
    arr.length = sizeof(seedVals) / sizeof(seedVals[0]);
    

    for (int32_t i = 0; i < arr.length; ++i)
    {
        printf("%d\n", arr.items[i]);
    }

    int32_t searchVal = 9;
    int32_t index = linSearch(searchVal, arr);

    printf("\narray contains: %d values\n", arr.length);
    printf("\n%d is stored at: %d\n",searchVal, index);
    
    int32_t occurences = countOccurrence(searchVal, arr); 
    
    printf("\nOccurences of %d is: %d\n",searchVal, occurences);
    

    printf("\n%d", Int32arrayGet(arr, 10));
    return 0;
}