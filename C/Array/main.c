#include <stdio.h>
#include <stdint-gcc.h>
#include <string.h>

typedef struct Int32array Int32array;

struct Int32array {
    int32_t length;
    int32_t capacity;
    int32_t *items;
    void (*push)(Int32array *self, int32_t value);
    void (*insert)(Int32array *self, int32_t value, int32_t index);
};

static void Int32arrayPush(Int32array *self, int32_t value)
{
    if (self->length >= self->capacity)
    {
        return;
    }
    self->items[self->length++] = value;
}

static void Int32arrayInsert(Int32array *self, int32_t value, int32_t index)
{
    if (self->length >= self->capacity)
    {
        return;
    }
    if (self->capacity < index)
    {
        return;
    }
    if (self->items[index] == 0)
    {
        self->items[index] = value;
        self->length += index - self->length + 1;
    }
}

void Int32arrayInit(Int32array *self, int32_t *buffer, int32_t capacity)
{
    self->length = 0;
    self->capacity = capacity;
    self->items = buffer;
    memset(self->items, 0, (size_t)capacity * sizeof(int32_t)); //Replace garbage with 0
    self->push = Int32arrayPush;
    self->insert = Int32arrayInsert;
}

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
    Int32array arr;
    Int32arrayInit(&arr, stack_buf, (sizeof(stack_buf) / sizeof(stack_buf[0])));

    arr.push(&arr, 10);
    arr.push(&arr, 20);
    
    printf("%d\n", arr.items[2]);
    arr.insert(&arr, 9, 16);
    printf("%d\n", arr.items[2]);

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