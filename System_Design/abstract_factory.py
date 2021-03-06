"""
    Abstract factory: Useful to create variants of multiple 
    related loosely coupled objects.

    We create two kinds of vehicles: Budget and Luxury.
    We have abstract classes for Bike and Car, for each of the categories luxury and budget
    we create a derived class from Bike and Car.

    Finally we have a factory class which creates vehicles for those catgories using an
    abstract class.
"""
from __future__ import annotations
from abc import ABC, abstractmethod

######### Base Automobile class
class Automobile(ABC):
    """
        Base class of automobile vehicles
    """
    @abstractmethod
    def create_bike(self) -> Bike:
        pass

    @abstractmethod 
    def create_car(self) -> Car:
        pass

    
######### Base class for Bike
class Bike(ABC):
    @abstractmethod
    def bike_stats(self) -> str:
        pass

######## Base class for Car
class Car(ABC):
    def car_stats(self) -> str:
        pass

########## Budget and Luxury classes for bike and car
class BudgetBike(Bike):
    def __init__(self) -> None:
        print('Created budget Bike')

    def bike_stats(self) -> str:
        return "Budget Bike"

class BudgetCar(Car):
    def __init__(self) -> None:
        print('Created budget car')
    def car_stats(self) -> str:
        return "Budget Car"

class LuxuryBike(Bike):
    def __init__(self) -> None:
        print('Created luxury bike')
    def bike_stats(self) -> str:
        return "Luxury Bike"

class LuxuryCar(Car):
    def __init__(self) -> None:
        print('Created luxury car')

    def car_stats(self) -> str:
        return "Luxury Car"


########## Budget category automobile vehicles 
class BudgetAutomobile(Automobile):
    """
        Budget category automobile vhicles.
    """
    def create_bike(self) -> BudgetBike:
        return BudgetBike()

    def create_car(self) -> BudgetCar:
        return BudgetCar()


########### Luxury category automobile vehicles    
class LuxuryAutomobile(Automobile):
    """
        Luxury category automobile vehciles
    """
    def create_bike(self) -> LuxuryBike:
        return LuxuryBike()

    def create_car(self) -> LuxuryCar:
        return LuxuryCar()


def driver(factory: Automobile):
    """
        Driver function for creating autombile of given type
    """
    bike = factory.create_bike()
    car = factory.create_car()


if __name__ == "__main__":
    # create budget category vehicles
    driver(BudgetAutomobile())
    print()
    # create luxury category vehicles
    driver(LuxuryAutomobile())

