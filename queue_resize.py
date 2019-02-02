class queue:
    def __init__(self):
        self.size = 5
        self.array = [None] * self.size
        self.top = 0
        self.button = 0

    def print(self):
        if self.top < self.button:
            f = self.size
            s = self.top
        else:
            s = 0
            f = self.top
        print('=-=-=-=-=-=-=-=-=-=-=-=')
        for i in range(f):
            print(self.array[i], '')
        for j in range(s):
            print(self.array[j], '')
        print('\n=-=-=-=-=-=-=-=-=-=-=-=')

    def resize(self, new_size):
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
        self.top = len(new_array)
        self.array = new_array

    def push(self, item):
        self.array[self.top] = item
        self.top += 1
        if self.top is self.button:
            self.resize(self.size * 2)
        if self.top is self.size:
            if self.button > 0:
                self.top = 0
            else:
                self.resize(self.size * 2)
