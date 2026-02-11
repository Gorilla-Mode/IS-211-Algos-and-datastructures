#include <math.h>
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
    bool (*remove)(const Int32Set *set, int32_t value);
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

bool int32SetRemove(const Int32Set *self, int32_t value)
{
    if (value >= self->capacity || value < 0)
    {
        fprintf(stderr,"ERROR: index %d out of range\n", value);
        return false;
    }

    if (self->data[value] != value)
    {
        fprintf(stderr,"ERROR: value %d does not exist\n", value);
        return false;
    }

    self->data[value] = 0;
    return true;
}

void int32SetInit(Int32Set *self)
{
    self->data = calloc(INT32_MAX, sizeof(int32_t)); //A fucking memory hog
    self->capacity = INT32_MAX;
    memset(self->data, 0, self->capacity * sizeof(int32_t));

    self->get = int32SetGet;
    self->add = int32SetAdd;
    self->contains = int32SetContains;
    self->remove = int32SetRemove;
}

int main(void)
{
    Int32Set set;
    int32SetInit(&set);

    set.add(&set, 5);
    set.add(&set, 10);
    set.add(&set, 20);
    set.add(&set, 20);

    if (set.contains(&set, 5))
    {
        printf("set contains %d\n", set.get(&set, 5));
    }

    if (!set.contains(&set, 1000))
    {
        printf("set does not contain %d\n", 1000);
    }

    set.remove(&set, 5);

    if (!set.contains(&set, 5))
    {
        printf("Set does not contain %d it was removed\n", 5);
    }

    set.add(&set, 5);

    printf("Size of set in Gb: %f\n", (double)(set.capacity * sizeof(int32_t)) / (pow(1024, 3)));
    return 0;
}