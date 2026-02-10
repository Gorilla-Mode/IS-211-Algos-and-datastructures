#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct int32Set Int32Set;

struct int32Set
{
    int *data;
    size_t size;
    size_t capacity;
    int32_t (*get)(const Int32Set *set, int32_t index);
};

int32_t int32SetGet(const Int32Set *self, int32_t index)
{
    if (index >= self->capacity || index < 0)
    {
        fprintf(stderr,"index out of range\n");
    }

    if (self->size <= index)
    {
        fprintf(stderr,"Accessing unused values\n");
    }

    return self->data[index];
}

void int32SetInit(Int32Set *self, int32_t *buf, int32_t capacity )
{
    self->data = buf;
    self->size = 0;
    self->capacity = capacity;
    memset(self->data, 0, capacity * sizeof(int32_t));
    self->get = int32SetGet;
}

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}