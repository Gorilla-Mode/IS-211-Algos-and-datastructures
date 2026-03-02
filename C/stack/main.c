#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct int32Stack Int32Stack;

struct int32Stack
{
    int32_t *data;
    int32_t size;
    int32_t ptr;

    void (*push)(Int32Stack *s, int32_t value);
    void (*pop)(Int32Stack *s);
    void (*clear)(Int32Stack *s);
    int32_t (*peek)(const Int32Stack *s);
    bool (*isEmpty)(const Int32Stack *s);
    bool (*isFull)(const Int32Stack *s);
};


void int32StackPush(Int32Stack *s, int32_t value)
{
    if (s->ptr + 1 == s->size)
    {
        fprintf(stderr,"\nError: Stack Overflow, exceeding capacity: %d", s->size);
        return;
    }
    s->data[s->ptr + 1] = value;
    s->ptr++;
}

void int32StackPop(Int32Stack *s)
{
    if (s->ptr == -1)
    {
        fprintf(stderr,"\nError: Stack is empty");
        return;
    }
    s->ptr--;
}

void int32StackClear(Int32Stack *s)
{
    if (s->ptr == -1)
    {
        fprintf(stderr,"\nError: Stack is empty");
        return;
    }
    s->ptr = -1;
}

int32_t int32StackPeek(const Int32Stack *s)
{
    if (s->ptr == -1)
    {
        fprintf(stderr,"\nError: Stack is empty");
        return -1;
    }
    return s->data[s->ptr];
}
bool int32StackIsEmpty(const Int32Stack *s)
{
    if (s->ptr == -1)
    {
        return true;
    }
    return false;
}

bool int32StackIsFull(const Int32Stack *s)
{
    if (s->ptr + 1 == s->size)
    {
        return true;
    }
    return false;
}

void int32_stack_init(Int32Stack *s, int32_t size)
{
    s->data = calloc(size, sizeof(int32_t));
    s->size = size;
    s->ptr = -1;

    s->push = int32StackPush;
    s->pop = int32StackPop;
    s->peek = int32StackPeek;
    s->clear = int32StackClear;
    s->isEmpty = int32StackIsEmpty;
    s->isFull = int32StackIsFull;
}


int main(void)
{
    Int32Stack stack;
    int32_stack_init(&stack, 6);

    stack.push(&stack, 1);
    stack.push(&stack, 2);
    stack.push(&stack, 3);
    printf("%d\n", stack.peek(&stack));

    stack.push(&stack, 4);
    stack.push(&stack, 5);
    stack.push(&stack, 6);
    printf("%d\n", stack.peek(&stack));
    if (stack.isFull(&stack))
    {
        printf("Stack is full\n");
    }

    stack.push(&stack, 7);

    stack.pop(&stack);
    stack.push(&stack, 7);
    printf("%d\n", stack.peek(&stack));

    stack.clear(&stack);
    if (stack.isEmpty(&stack))
    {
        printf("Stack is empty\n");
    }

    stack.push(&stack, 1);
    stack.push(&stack, 2);
    stack.push(&stack, 3);
    printf("%d\n", stack.peek(&stack));

    return 0;
}