#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct int32List int32List;

struct int32List
{
    int32_t length;
    int32_t capacity;
    int32_t *items;
    int32_t reallocChuck;
    bool *usedIndex;

    bool (*add)(int32List *self, int32_t value);
    int32_t (*get)(const int32List *self, uint32_t index);
    bool (*insert)(int32List *self, uint32_t index, int32_t value);
    bool (*fill)(int32List *self, int32_t value);
    bool (*remove)(int32List *self, uint32_t index);
};

bool int32ListAdd (int32List *self, int32_t value)
{
    if (self->length < self->capacity)
    {
        self->items[self->length] = value;
        self->usedIndex[self->length] = true;
        self->length++;
        return true;
    }

    int32_t oldCap = self->capacity;
    int32_t newSize = oldCap + self->reallocChuck;
    size_t newItemsBytes = (size_t)newSize * sizeof(int32_t);
    size_t newUsedBytes  = (size_t)newSize * sizeof(bool);

    int32_t *ItemsTemp = realloc(self->items, newItemsBytes);
    if (ItemsTemp == nullptr)
    {
        fprintf(stderr,"Memory allocation failed\n");
        return false;
    }

    bool *UsedTemp = realloc(self->usedIndex, newUsedBytes);
    if (UsedTemp == nullptr)
    {
        fprintf(stderr,"Memory allocation failed\n");
        return false;
    }

    self->usedIndex = UsedTemp;
    self->items = ItemsTemp;
    self->capacity = newSize;
    size_t newCount = newSize - oldCap;
    if (newCount > 0)
    {
        memset(self->usedIndex + oldCap, 0, newCount * sizeof(bool));
        memset(self->items + oldCap, 0, newCount * sizeof(int32_t));
    }

    self->items[self->length] = value;
    self->usedIndex[self->length] = true;
    self->length++;

    return true;
}

int32_t int32ListGet(const int32List *self, uint32_t index)
{
    if (index >= self->capacity)
    {
        fprintf(stderr, "ERROR: Accessing out of bounds\n\tBounds of list: %d\n\tIndex of attempted to access: %d\n",
            self->capacity, index);
        return false;
    }
    if (index >= self->length)
    {
        fprintf(stderr, "ERROR: Accessing unused values\n\tLength of list: %d\n\tIndex of attempted access: %d\n",
            self->length, index);
        return false;
    }

    return self->items[index];
}

bool int32ListInsert(int32List *self, uint32_t index, int32_t value)
{
    if (index >= self->capacity)
    {
        fprintf(stderr, "ERROR: Inserting out of bounds\n\tBounds of list: %d\n\tIndex of attempted to insert: %d\n",
            self->capacity, index);
        return false;
    }

    self->items[index] = value;
    if (index > self->length)
    {
        self->length += ((int32_t)index - self->length + 1);
    }
    return true;
}

bool int32ListFill(int32List *self, int32_t value)
{
    return true;
}

bool int32ListRemove(int32List *self, uint32_t index)
{
    return true;
}

bool int32ListInit(int32List *self, int32_t Capacity)
{
    self->add = int32ListAdd;
    self->get = int32ListGet;
    self->insert = int32ListInsert;
    self->fill = int32ListFill;
    self->remove = int32ListRemove;

    self->length = 0;
    self->capacity = Capacity;
    self->reallocChuck = 25;

    self->items = calloc((size_t)Capacity, sizeof(int32_t));
    self->usedIndex  = calloc((size_t)Capacity, sizeof(bool));
    if (!self->items || !self->usedIndex)
    {
        free(self->items);
        free(self->usedIndex);
        fprintf(stderr, "Memory not allocated!\n");
        return false;
    }
    memset(self->usedIndex, false, (size_t)self->capacity * sizeof(bool));

    return true;
}

int main(void)
{
    int32List list;
    int32ListInit(&list, 4);
    setbuf(stdout, nullptr);
    printf("Initial Cap: %d\n", list.capacity);
    list.add(&list, 3);
    list.add(&list, 2);
    list.add(&list, 1323);
    list.add(&list, 343);
    list.add(&list, 43343);

    if (!list.add(&list, 653))
    {
        fprintf(stderr, "Value not added\n");
    }

    list.insert(&list,28, 540);

    for (int i = 0; i < list.length; ++i)
    {
        printf("List item at index %d: %d\n", i, list.get(&list, i));
    }
    for (int i = 0; i < list.length; ++i)
    {
        printf("Is index %d used: %hhd\n", i, list.usedIndex[i]);
    }

    list.get(&list, 600);
    list.get(&list, 29);

    printf("Current Cap: %d\n", list.capacity);
    printf("length: %d\n", list.length);
    printf("Size: %llu\n", sizeof(int32_t) * (size_t)list.capacity);
    printf("First val: %d\n", list.get(&list, 0));

    return 0;
}