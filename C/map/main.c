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

    mapElement (*add)(map *self, const int32_t key, char value);
    char (*get)(const map *self, const int32_t key);
    bool (*exists)(const map *self, const char value);
    int32_t (*find)(const map *self, const char value);
};

mapElement mapAdd(map *self, const int32_t key, char value)
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

    int32_t index = 0;
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

    size_t newKeyBytes = sizeof(int32_t) * (self->size + 1);
    int32_t *KeysTemp = realloc(self->keys, newKeyBytes);
    if (KeysTemp == nullptr)
    {
        fprintf(stderr, "Failed to allocate memory for keys\n");
        result.wasInserted = false;
        result.key = self->keys[index];
        result.value = self->values[index];
        return result;
    }
    self->keys = KeysTemp;
    self->size++;
    self->keys[index] = key;

    size_t newValueBytes = sizeof(char) * (self->size + 1);
    char *ValuesTemp = realloc(self->values, newValueBytes);
    if (ValuesTemp == nullptr)
    {
        fprintf(stderr, "Failed to allocate memory for values\n");
        result.wasInserted = false;
        result.key = self->keys[index];
        result.value = self->values[index];
        return result;
    }
    self->values = ValuesTemp;
    self->values[index] = value;

    result.key = self->keys[index];
    result.value = self->values[index];
    result.wasInserted = true;

    return result;
}

char mapGet(const map *self, const int32_t key)
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

    if (existsAt < 0)
    {
        fprintf(stderr, "Error: Key not found\n");
        return '\0';
    }
    return self->values[existsAt];
}

bool mapExists(const map *self, const char value)
{
    for (int i = 0; i < self->size; ++i)
    {
        if (value == self->values[i])
        {
            return true;
        }
    }
    return false;
}

int32_t mapFind(const map *self, const char value)
{
    for (int i = 0; i < self->size; ++i)
    {
        if (value == self->values[i])
        {
            return self->keys[i];
        }
    }
    fprintf(stderr, "Error: Key not found\n");
    return -1;
}

void mapInit (map *self, int32_t size)
{
    self->keys = malloc(sizeof(int32_t) * size);
    self->values =  malloc(sizeof(char) * size);
    self->size = size;

    self->add = mapAdd;
    self->get = mapGet;
    self->exists = mapExists;
    self->find = mapFind;
}

int main(void)
{
    map map;
    mapInit(&map, 10);

    map.add(&map, 1, 'a');
    map.add(&map, 2, 'b');
    map.add(&map, 1, 'c');

    if (map.add(&map, 3, 'd').wasInserted)
    {
        printf("Inserted\n");
    }

    if (!map.add(&map, 1, 'e').wasInserted)
    {
        printf("Not inserted\n");
    }

    printf("%c\n", map.get(&map, 1));
    printf("%c\n", map.get(&map, 2));
    printf("%c\n", map.get(&map, 3));
    printf("%c\n", map.get(&map, 12));

    bool exists = map.exists(&map, 'x');

    if (exists)
    {
        printf("Exists\n");
    }
    else
    {
        printf("Does not exist\n");
    }

    bool exists2 = map.exists(&map, 'a');

    if (exists2)
    {
        printf("Exists\n");
    }
    else
    {
        printf("Does not exist\n");
    }


    int32_t key = map.find(&map, 'a');
    printf("%d\n", key);

    return 0;
}