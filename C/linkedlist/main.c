#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct singleLinked singleLinked;

struct singleLinked
{
    int32_t value;
    int32_t size;
    struct singleLinked *next;
    struct singleLinked *tail;

    void (*append)(singleLinked *singleLinked, int32_t value);
    void (*insert)(singleLinked *singleLinked, int32_t value, int32_t position);
    void (*remove)(singleLinked *singleLinked, int32_t position);
    int32_t (*last)(const singleLinked *singleLinked);
    int32_t (*first)(const singleLinked *singleLinked);
    int32_t* (*toArray)(const singleLinked *singleLinked);
};

void singleLinkedAppend(singleLinked *s, int32_t value)
{
    singleLinked *node = malloc(sizeof(*node));

    node->value = value;
    node->next = nullptr;
    node->append = s->append;
    node->last = s->last;

    if (s->tail == nullptr)
    {
        s->next = node;
        s->tail = node;
        s->size++;
        return;
    }

    s->tail->next = node;
    s->tail = node;
    s->size++;
}

int32_t singleLinkedLastNode(const singleLinked *s)
{
    return s->tail->value;
}

int32_t singleLinkedFirstNode(const singleLinked *s)
{
    return s->next->value;
}

void singleLinkedInsert(singleLinked *s, int32_t value, int32_t position)
{
    if (position < 0 || position > s->size)
    {
        fprintf(stderr, "Position out of range\n");
        return;
    }

    singleLinked *node = malloc(sizeof(*node));
    node->value = value;
    node->next = s->next;

    singleLinked *cur = s;
    for (int i = 0; i < position; i++)
    {
        cur = cur->next;
    }

    node->next = cur->next;
    cur->next = node;

    if (node->next == nullptr)
    {
        s->tail = node;
    }

    s->size++;
}

int32_t* singleLinkedToArray(const singleLinked *s)
{
    int32_t *array = malloc(sizeof(int32_t) * s->size);

    const singleLinked *node = s->next;
    for (int32_t i = 0; node != nullptr; ++i)
    {
        array[i] = node->value;
        node = node->next;
    }
    return array;
}

void singleLinkedRemove(singleLinked *s, int32_t position)
{
    if (position >= s->size)
    {
        fprintf(stderr, "Position out of range\n");
        return;
    }

    singleLinked *cur = s;
    for (int i = 0; i < position; i++)
    {
        cur = cur->next;
    }

    if (cur->next == nullptr)
    {
        s->tail = cur;
    }

    singleLinked *node = cur->next;
    cur->next = node->next;
    free(node);
    s->size--;
}

void initSingleLinked(singleLinked *singleLinked)
{
    singleLinked->next = nullptr;
    singleLinked->tail = nullptr;
    singleLinked->size = 0;

    singleLinked->insert = singleLinkedInsert;
    singleLinked->append = singleLinkedAppend;
    singleLinked->last = singleLinkedLastNode;
    singleLinked->first = singleLinkedFirstNode;
    singleLinked->toArray = singleLinkedToArray;
    singleLinked->remove = singleLinkedRemove;
}

int main(void)
{
    singleLinked singleLinked;
    initSingleLinked(&singleLinked);

    singleLinked.append(&singleLinked, 1);
    printf("Last item at size 1: %d\n", singleLinked.last(&singleLinked));

    singleLinked.append(&singleLinked, 3);
    singleLinked.append(&singleLinked, 3);
    singleLinked.insert(&singleLinked, 5, 0);
    printf("Last item at size 2: %d\n", singleLinked.last(&singleLinked));
    printf("First item after insert: %d\n", singleLinked.first(&singleLinked));
    printf("Size: %d\n", singleLinked.size);

    int32_t *arrayInitial = singleLinked.toArray(&singleLinked);
    printf("\nItems in list:\n");
    for (int i = 0; i < singleLinked.size; ++i)
    {
        printf("Array item %d: %d\n", i, arrayInitial[i]);
    }

    singleLinked.insert(&singleLinked, 10, 1);
    singleLinked.insert(&singleLinked, 11, 5);
    int32_t *arrayAfter = singleLinked.toArray(&singleLinked);
    printf("\nSize: %d\n", singleLinked.size);
    printf("Items in list:\n");
    for (int i = 0; i < singleLinked.size; ++i)
    {
        printf("Array item %d: %d\n", i, arrayAfter[i]);
    }

    singleLinked.remove(&singleLinked, 0);
    int32_t *arrayAfter2 = singleLinked.toArray(&singleLinked);
    printf("\nSize: %d\n", singleLinked.size);
    printf("Items in list:\n");
    for (int i = 0; i < singleLinked.size; ++i)
    {
        printf("Array item %d: %d\n", i, arrayAfter2[i]);
    }

    printf("\nSize: %d\n", singleLinked.size);
    printf("first: %d\n", singleLinked.last(&singleLinked));

    return 0;
}