class stack:
    def __init__(self, capasity):
        if capasity < 1:
            print("Error: capacity is wrong")
            return
        self.top = 0
        self.size = capasity
        self.array = [None] * capasity

    def print(self):
        for i in range(self.top):
            print(self.array[i], end=' ')
        print('')

    def resize(self, nsize):
        narray = [None] * nsize
        for i in range(self.top):
            narray[i] = self.array[i]
        self.array = narray
        self.size = nsize

    def push(self, item):
        if self.size is self.top:
            self.resize(self.size * 2)
        self.array[self.top] = item
        self.top += 1

    def pop(self):
        if self.top is 0:
            print('Error: Stack is empty')
            return
        self.top -= 1
        result = self.array[self.top]
        if self.top > 1 and self.top < self.size // 2:
            self.resize(self.size // 2)
        return result


s = stack(5)
s.push(5)
s.push(4)
s.push(2)
s.push(7)
s.push(6)
s.push(90)
s.print()
s.pop()
s.pop()
s.pop()
s.pop()
s.pop()
s.pop()
s.pop()
s.print()
