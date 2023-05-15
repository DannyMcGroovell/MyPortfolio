from passport import Passport

class Passport_list:
    def __init__(self,passports,data):
        self.passports = passports
        self.data = data

    def check(self):
        a = {}
        for passport in self.passports:
            if a.get(passport.fio) == None:
                a[passport.fio] = 1
            else:
                a[passport.fio] += 1
        for i,j in a.items():
            if j >=2:
                print(f"Паспорт '{i}' является дубликатом (повторяется {j} раз(а))")

    def search(self, ps_number, ps_series):
        s = False
        for i,k in self.data.items():
            if k[0] == str(ps_number) and k[1] == str(ps_series):
                s = True
                print(f"Паспорт найден: {ps_fio}\nНомер:\t{ps_number}\nСерия:\t{ps_series}")
        if not s:
            print("Паспорт не найден.")
