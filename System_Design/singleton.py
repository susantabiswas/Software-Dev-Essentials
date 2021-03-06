
"""
    Simple Singleton using decorator
"""
def singleton(cls):
    instances = {}
    # When we use instances var inside the closure, it gets
    # binded to the inner function, so the next time when the same 
    # class object creation is requested, instances var will still be 
    # alive untill the previously created object is alive
    def get_instance(*args, **kwargs):
        if cls not in instances:
            # create an instance
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]

    return get_instance

@singleton
class Dummy:
    def __init__(self, name="sam"):
        self.name = name
        print("Dummy object created!")

d1 = Dummy()
print(id(d1))
print(d1.name)
print(d1.__dict__)
del d1
d2 = Dummy("timothy")
print(id(d2))
print(d2.name)