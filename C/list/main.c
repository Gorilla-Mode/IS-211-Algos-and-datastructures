#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct int32List int32List;

struct int32List
{
    int32_t length;
    int32_t capacity;
    int32_t *items;

    void (*add)(int32List *self, int32_t value);
};



void int32ListAdd (int32List *self, int32_t value)
{
    if (self->length != self->capacity)
    {
        self->items[self->length] = value;
        self->length++;
    }
}

void int32ListInit(int32List *self, int32_t capacity)
{
    self->add = int32ListAdd;

    self->length = 0;
    self->capacity = capacity;
    self->items = calloc(capacity, sizeof(int32_t));
    if (self->items == NULL)
    {
        setbuf(stdout, nullptr);
        fprintf(stderr, "Memory not allocated!\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    printf("hello\n");
    int32List list;
    int32ListInit(&list, 50);

    list.add(&list, 3);
    list.add(&list, 2);
    list.add(&list, 1323);
    list.add(&list, 1322);
    list.add(&list, 154334);

    setbuf(stdout, nullptr);
    printf("List item at index 0: %d\n", list.items[0]);
    printf("List item at index 0: %d\n", list.items[1]);
    printf("List item at index 0: %d\n", list.items[4]);
    printf("length: %d\n", list.length);
    printf("Size: %llu\n", sizeof(list));

    return 0;
}
