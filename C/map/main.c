#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mapElement
{
    int32_t key;
    char value;
    bool wasInserted;
} mapElement;

typedef struct map map;

struct map
{
    int32_t *keys;
    char *values;
    int32_t size;

    mapElement (*add)(map *self, int32_t key, char value);
};

mapElement mapAdd(map *self, int32_t key, char value)
{
    int32_t existsAt = -1;
    for (int i = 0; i < self->size; ++i)
    {
        if (key == self->keys[i])
        {
            existsAt = i;
            break;
        }
    }

    int32_t index;
    mapElement result;
    if (existsAt >= 0)
    {
        index = existsAt;
        result.wasInserted = false;
        result.key = self->keys[index];
        result.value = self->values[index];

        return result;
    }

    index = self->size;
    self->keys = (int32_t *) realloc(self->keys, sizeof(int32_t) * (self->size + 1));
    self->size++;
    self->keys[index] = key;

    self->values = (char *) realloc(self->values,self->size);
    self->values[index] = value;

    result.key = self->keys[index];
    result.value = self->values[index];
    result.wasInserted = true;

    return result;
}

void mapInit (map *self, int32_t size)
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

    mapAdd(&map, 1, 'a');
    return 0;
}