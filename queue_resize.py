class queue:
    def __init__(self):
        self.size = 5
        self.array = [None] * self.size
        self.top = 0
        self.button = 0

    def print(self):
        if self.top < self.button:
            f = self.size - self.button
            s = self.top
        else:
            s = 0
            f = self.top - self.button
        print('=-=-=-=-=-=-=-=-=-=-=-=')
        print(self.button, self.top, self.size)
        for i in range(f):
            print(self.array[i + self.button], end=' ')
        for j in range(s):
            print(self.array[j], end=' ')
        print('\n=-=-=-=-=-=-=-=-=-=-=-=')

    def show(self):
        for i in range(self.size):
            print(self.array[i], end=' ')
        print('')

    def resize(self, new_size):
        print('resize', new_size)
        new_array = [None] * new_size
        if self.top <= self.button:
            f = self.size - self.button
            s = self.top
        else:
            s = 0
            f = self.top - self.button
        for i in range(f):
            new_array[i] = self.array[i + self.button]
        for j in range(s):
            new_array[j + f] = self.array[j]
        self.size = new_size
        self.button = 0
        self.top = f + s
        self.array = new_array

    def push(self, item):
        self.array[self.top] = item
        self.top += 1
        if self.top == self.button:
            self.resize(self.size * 2)
        if self.top == self.size:
            if self.button > 0:
                self.top = 0
            else:
                self.resize(self.size * 2)

    def pop(self):
        s = self.size
        if self.top == self.button:
            print('Error: Queue is empty')
            return 0
        result = self.array[self.button]
        self.button += 1
        if self.top < self.button:
            if self.button == self.size:
                self.button = 0
            s = self.top + self.size - self.button
        if self.top > self.button:
            s = self.top - self.button
        if s <= self.size // 4:
            self.resize(self.size // 2)
        return result


A = queue()
A.push(6)
A.push(7)
A.push(8)
A.push(9)
A.push(0)
A.push(10)
A.push(11)
A.push(12)
A.print()
print(A.pop())
print(A.pop())
print(A.pop())
print(A.pop())
print(A.pop())
A.print()
A.push(21)
A.push(22)
A.push(23)
A.push(24)
A.push(25)
A.print()
# A.show()
print(A.pop())
A.print()
print(A.pop())
print(A.pop())
print(A.pop())
print(A.pop())
A.print()
