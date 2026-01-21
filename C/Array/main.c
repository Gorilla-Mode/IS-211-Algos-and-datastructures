#include <complex.h>
#include <stdio.h>

int linSearch(int val, const int arr[], int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (arr[i] == val)
        {
           return i; 
        }
    }
    return -1;
}

int countOccurrence(int val, const int arr[], int len)
{
    int count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (arr[i] == val)
        {
            count++;
        }
    }
    return count;
}

int main(void)
{
    //fr easier in c than python (skull emoji, skull emoji)
    int arr[] = {1,3,2,90,9,4,5,6,7,8,9};

    for (int i = 0; i < (sizeof(arr)/sizeof(int)); ++i)
    {
        printf("%d\n", arr[i]);
    }

    int searchVal = 9;
    int index = linSearch(searchVal, arr, (sizeof(arr)/sizeof(arr[0])));

    printf("\n%d is stored at: %d\n",searchVal, index);

    int occurences = countOccurrence(searchVal, arr, (sizeof(arr)/sizeof(arr[0]))); 

    printf("\nOccurences of %d is: %d\n",searchVal, occurences);
    return 0;
}
