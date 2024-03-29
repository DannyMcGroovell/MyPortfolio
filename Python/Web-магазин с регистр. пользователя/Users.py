from User import User
from GoodCart import GoodCart
from Good import Good


class Users:
    def __init__(self):
        user = User(1, "admin", "12345", "ADMIN")
        self.users = [user]

    def start(self):
        while True:
            answer = int(input("Введите 1 для регистрации, либо 2 - для авторизации: "))
            if answer == 1:
               return self.reg()
            elif answer == 2:
                return self.auth()

    def get_max_id(self):
        list_id = []
        for user in self.users:
            list_id.append(user.id)
        return max(list_id)

    def is_validate(self, login):
        for user in self.users:
            if user.login == login:
                return False
        return True

    def reg(self):
        print("Регистрация в системе\n")
        login = input("Введите логин\n")
        if self.is_validate(login):
            my_pass = input("Введите пароль\n")
            user = User(self.get_max_id() + 1, login, my_pass, 'CLIENT')
            self.users.append(user)
            return self.auth()

    def auth(self):
        print("Авторизация в системе\n")
        login = input("Введите логин\n")
        pass_temp = input("Введите пароль\n")
        for user in self.users:
            if user.login == login and user.password == pass_temp:
                return user
        print("Нет такого пользователя в системе")
        return None

