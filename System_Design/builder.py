class A:
    def __init__(self):
        self.a = 10

class B(A):
    def __init__(self):
        #self.a = 20
        self.b = 99
b = B()
print(b.a, b.b)