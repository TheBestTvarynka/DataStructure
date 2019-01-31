class Stack:
    array = list()
    # top - count of elements (not last index)

    def push(self, key):
        self.array.append(key)

    def print(self):
        for i in range(len(self.array)):
            print(self.array[i], end=' ')
        print('')

    def pop(self):
        if len(self.array) is 0:
            print("Error: Stack is empty!")
            return
        self.array.pop(len(self.array) - 1)
        # return self.array[self.top]

    def size(self):
        return len(self.array)


print('apple')
a = Stack()
a.pop()
a.push(5)
a.push(2)
a.push(8)
print('Current size of stack', a.size())
a.push(1)
a.print()
a.pop()
a.pop()
a.pop()
# print(a.pop())
# print(a.pop())
# print(a.pop())
# print(a.pop())
a.print()
