#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Int32Set Int32Set;

struct Int32Set
{
    int *data;
    size_t capacity;
    int32_t (*get)(const Int32Set *set, int32_t index);
    void (*add)(const Int32Set *set, int32_t value);
    bool (*contains)(const Int32Set *set, int32_t value);
};

int32_t int32SetGet(const Int32Set *self, int32_t value)
{
    if (value >= self->capacity || value < 0)
    {
        fprintf(stderr,"ERROR: index %d out of range\n", value);
    }

    return self->data[value];
}

void int32SetAdd(const Int32Set *self, int32_t value)
{
    if (self->data[value] == value)
    {
        fprintf(stderr,"ERROR: value %d already exists\n", value);
        return;
    }

    self->data[value] = value;
}

bool int32SetContains(const Int32Set *self, int32_t value)
{
    if (value >= self->capacity || value < 0)
    {
        fprintf(stderr,"ERROR: index %d out of range\n", value);
        return false;
    }

    if (self->data[value] == value)
    {
        return true;
    }

    return false;
}

void int32SetInit(Int32Set *self)
{
    self->data = calloc(INT32_MAX, sizeof(int32_t));
    self->capacity = INT32_MAX;
    memset(self->data, 0, self->capacity * sizeof(int32_t));

    self->get = int32SetGet;
    self->add = int32SetAdd;
    self->contains = int32SetContains;
}

int main(void)
{
    Int32Set set;
    int32SetInit(&set);

    set.add(&set, 5);
    set.add(&set, 10);
    set.add(&set, 20);
    set.add(&set, 20);

    return 0;
}