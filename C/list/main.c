#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct int32List int32List;

struct int32List
{
    int32_t length;
    int32_t capacity;
    int32_t *items;
    int32_t reallocChuck;

    bool (*add)(int32List *self, int32_t value);
};

bool int32ListAdd (int32List *self, int32_t value)
{
    if (self->length < self->capacity)
    {
        self->items[self->length] = value;
        self->length++;
        return true;
    }

    int32_t newSize = self->capacity + self->reallocChuck;
    int32_t *temp = realloc(self->items, sizeof(int32_t) * newSize);
    if (temp == nullptr)
    {
        fprintf(stderr,"Memory allocation failed\n");
        return false;
    }
    self->items = temp;

    self->items[self->length] = value;
    self->length++;
    self->capacity = newSize;

    return true;
}

bool int32ListInit(int32List *self, int32_t Capacity)
{
    self->add = int32ListAdd;

    self->length = 0;
    self->capacity = Capacity;
    self->reallocChuck = 25;

    self->items = calloc(Capacity, sizeof(int32_t));
    if (self->items == nullptr)
    {
        setbuf(stdout, nullptr);
        fprintf(stderr, "Memory not allocated!\n");
        return false;
    }

    return true;
}

int main(void)
{
    int32List list;
    int32ListInit(&list, 4);
    setbuf(stdout, nullptr);
    printf("Initial Cap: %d\n", list.capacity);
    list.add(&list, 3), list.add(&list, 2), list.add(&list, 1323);

    if (!list.add(&list, 653))
    {
        fprintf(stderr, "Value not added\n");
    }

    for (int i = 0; i < list.capacity; ++i)
    {
        printf("List item at index %d: %d\n", i, list.items[i]);
    }

    printf("Current Cap: %d\n", list.capacity);
    printf("length: %d\n", list.length);
    printf("Size: %llu\n", sizeof(int32_t) * (size_t)list.capacity);

    return 0;
}