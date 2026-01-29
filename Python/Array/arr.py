from array import array

#Actual array
arr = array('i',[1,2,3,4])

for i in arr:
    print(i)

#Implementation

class Array(object):

    def __init__(self, buffer):
        self.arr = [None] * buffer
        self.items = 0

    def insert(self, item):
        self.arr[self.items] = item
        self.items += 1

    def search(self, item):
        for j in range(self.items):
            if self.arr[j] == item:
                return self.arr[j]

        return None

    def index_of(self, item):
        for j in range(self.items):
            if self.arr[j] == item:
                return j

        return None

    def delete(self, item):
        for j in range(self.items):
            if self.arr[j] == item:
                for k in range(j, self.items):
                    self.arr[k] = self.arr[k + 1]
                self.items -= 1
                return True
        return False

    def traverse(self, function=print):
        for j in range(self.items):
            function(self.arr[j])

buff = 15

print("\ninserting:")
arr = Array(buff)
arr.insert(1)
arr.insert(2)
arr.insert(3)
arr.insert(4)
arr.traverse()

print("\nSearch:")
print(arr.search(3))
print(arr.search(7))

print("\nIndex of:")
print(arr.index_of(2))

print("\nDeletion:")
arr.delete(2)
arr.traverse()