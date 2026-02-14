#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct map map;

struct map
{
    int32_t *keys;
    char *values;
    int64_t size;

    void (*add)(map *self, int32_t key, char value);
};

void mapAdd(map *self, int32_t key, char value)
{

}

void mapInit (map *self, int64_t size)
{
    self->keys = malloc(sizeof(int32_t) * size);
    self->values =  malloc(sizeof(char) * size);
    self->size = size;

    self->add = mapAdd;
}

int main(void)
{
    map map;
    mapInit(&map, 10);
    return 0;
}