class Stack:
    def __init__(self, size):
        self.size = size
        self.stack = [None] * size
        self.top = -1

    def push(self, item):
        if self.top + 1 >= self.size:
            return
        self.stack[self.top + 1] = item
        self.top += 1

    def pop(self):
        if self.top == -1:
            return
        self.stack[self.top] = None
        self.top -= 1

    def peek(self):
        return self.stack[self.top]

    def is_empty(self):
        if self.top == -1:
            return True
        return False

    def is_full(self):
        if self.top + 1 == self.size:
            return True
        return False

test = Stack(5)

test.push(2)
print(test.peek())

test.push(5)
print(test.peek())

test.pop()
print(test.peek())

test.push(3)
test.push(4)
test.push(6)
test.push(7)
test.push(8)

print(test.peek())
print("Is full:",test.is_full(),"\nIs empty:", test.is_empty())