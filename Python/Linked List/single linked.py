class Node:
    """A node in the singly linked list."""

    def __init__(self, data):
        self.data = data
        self.next = None

    def __repr__(self):
        return f"Node({self.data!r})"

class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self._size = 0

    def __len__(self):
        return self._size

    def __bool__(self):
        return self.head is not None

    def is_empty(self):
        """Return True if the list has no elements."""
        return self.head is None

    def __getitem__(self, index):
        """Get element at *index* (supports negative indexing)."""
        if index < 0:
            index += self._size
        if index < 0 or index >= self._size:
            raise IndexError("list index out of range")
        current = self.head
        for _ in range(index):
            current = current.next
        return current.data

    def __setitem__(self, index, value):
        """Set element at *index* (supports negative indexing)."""
        if index < 0:
            index += self._size
        if index < 0 or index >= self._size:
            raise IndexError("list index out of range")
        current = self.head
        for _ in range(index):
            current = current.next
        current.data = value

    def __contains__(self, data):
        """Return True if *data* is in the list."""
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False

    def index(self, data):
        """Return the index of the first occurrence of *data*, or -1."""
        current = self.head
        idx = 0
        while current:
            if current.data == data:
                return idx
            current = current.next
            idx += 1
        return -1

    def count(self, data):
        """Count occurrences of *data* in the list."""
        total = 0
        current = self.head
        while current:
            if current.data == data:
                total += 1
            current = current.next
        return total

    def prepend(self, data):
        """Insert *data* at the beginning of the list."""
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
        self._size += 1

    def append(self, data):
        """Insert *data* at the end of the list."""
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node
        self._size += 1

    def insert(self, index, data):
        """Insert *data* before the element at *index*."""
        if index <= 0:
            self.prepend(data)
            return
        if index >= self._size:
            self.append(data)
            return
        new_node = Node(data)
        current = self.head
        for _ in range(index - 1):
            current = current.next
        new_node.next = current.next
        current.next = new_node
        self._size += 1

    def pop_front(self):
        """Remove and return the first element."""
        if self.head is None:
            raise IndexError("pop from empty list")
        data = self.head.data
        self.head = self.head.next
        self._size -= 1
        return data

    def pop(self, index=-1):
        """Remove and return the element at *index* (default last)."""
        if self.head is None:
            raise IndexError("pop from empty list")
        if index < 0:
            index += self._size
        if index < 0 or index >= self._size:
            raise IndexError("list index out of range")
        if index == 0:
            return self.pop_front()
        current = self.head
        for _ in range(index - 1):
            current = current.next
        data = current.next.data
        current.next = current.next.next
        self._size -= 1
        return data

    def remove(self, data):
        """Remove the first occurrence of *data*. Raises ValueError if not found."""
        if self.head is None:
            raise ValueError(f"{data!r} not in list")
        if self.head.data == data:
            self.head = self.head.next
            self._size -= 1
            return
        current = self.head
        while current.next:
            if current.next.data == data:
                current.next = current.next.next
                self._size -= 1
                return
            current = current.next
        raise ValueError(f"{data!r} not in list")

    def clear(self):
        """Remove all elements from the list."""
        self.head = None
        self._size = 0

    def reverse(self):
        """Reverse the list in place."""
        prev = None
        current = self.head
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        self.head = prev

    def copy(self):
        """Return a shallow copy of the list."""
        new_list = SinglyLinkedList()
        current = self.head
        while current:
            new_list.append(current.data)
            current = current.next
        return new_list


if __name__ == "__main__":
    ll = SinglyLinkedList()

    ll.append(1)
    ll.append(2)
    ll.append(3)
    ll.append(4)
    ll.append(5)
    print("Length:", len(ll))
    print("ll[2]:", ll[2])

    ll.prepend(0)
    print("After prepend 0, head:", ll.head)

    ll.insert(3, 99)
    print("After insert 99 at index 3, ll[3]:", ll[3])

    ll.remove(99)
    print("After remove 99, ll[3]:", ll[3])

    ll.reverse()
    print("After reverse, head:", ll.head)

    print("Pop last:", ll.pop())
    print("Contains 3:", 3 in ll)
    print("Index of 3:", ll.index(3))