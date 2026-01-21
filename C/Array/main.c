#include <stdio.h>

int main(void)
{
    //fr easier in c than python (skull emoji, skull emoji)
    int arr[] = {1,2,3,4,5,6,7,8};

    for (int i = 0; i < (sizeof(arr)/sizeof(int)); ++i)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}
