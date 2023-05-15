import random
from random import randint
class Passport:
    def __init__(self, number, series, fio):
        self.number = number
        self.series = series
        self.fio = fio

    def fill(self):
        array = []
        numbers = []
        b = ''
        c = ''
        a = input("Введите h, чтобы заполнить вручную: ")
        if a == 'h':
            for i in range(self.number):
                i = random.randint(0, 9)
                numbers.append(i)
            b = ''.join(str(i) for i in numbers)
            с = input("Введите серию паспорта (6 цифр): ")
            array.append(b)
            array.append(с)
        else:
            series = []
            for i in range(self.number):
                i = random.randint(0, 9)
                numbers.append(i)
            b = ''.join(str(i) for i in numbers)
            for i in range(self.series):
                i = random.randint(0,9)
                series.append(i)
            c = ''.join(str(i) for i in series)
            array.append(b)
            array.append(c)
        return array
