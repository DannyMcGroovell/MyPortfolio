from GoodCart import GoodCart
from Good import Good
from User import User

class Cart:
    def __init__(self,goods_cart):
        self.goods_cart = goods_cart

    def show_cart(self):
        print("\nКорзина покупок\n")
        for i,item in enumerate(self.goods_cart):
            print(f"{i + 1}) {item.title} стоит {item.price},"
                  f" общая стоимость товара "
                  f"с учетом количества: {item.price * item.quantity}, {item.quantity}шт")

    def add_good(self, good, user_id):
        if(len(self.goods_cart) == 0):
            self.add_good_first_time(good, user_id)
        else:
            is_find = False
            for item in self.goods_cart:
                if item.id == good.id:
                    item.quantity += 1
                    is_find = True
                    break
            if not is_find:
                self.add_good_first_time(good, user_id)

    def add_good_first_time(self, good, user_id):
        cart_item = GoodCart(good.id, good.title, good.price, good.category, 1, user_id)
        self.goods_cart.append(cart_item)


    def remove_good_in_cart(self, good, login):
        try:
            if login == 'ADMIN':
                self.goods_cart.remove(good)
        except ValueError:
            print("Нельзя удалить несуществующий товар")
        if len(self.goods_cart) == 0:
            print("Корзина пуста")
        self.show_cart()


    def update_good_in_cart(self, login, id_good):
        if login == 'ADMIN':
            good_id = int(input('Введите id товара (изначальный), который хотите изменить (от 1 до 5): '))
            if good_id != id_good:
                print("Добавленный id машины не совпадает с id, который хотите изменить")
                return False
            a = int(input("Введите, что хотите поменять (1 - количество, 2 - цена, 3 - название: "))
            if a == 1:
                a1 = int(input("Введите количество: "))
                for i in self.goods_cart:
                    if i.id == good_id:
                        i.quantity = a1
                        print(i.quantity)
                        print(a1)
            if a == 2:
                a2 = int(input("Введите цену: "))
                for i in self.goods_cart:
                    if i.id == good_id:
                        i.price = a2
                        print(i.price)
                        print(a2)
            if a == 3:
                a3 = input("Введите название товара: ")
                for i in self.goods_cart:
                    if i.id == good_id:
                        i.title = a3
                        print(i.title)
                        print(a3)
        print("Товар изменен")
        self.show_cart()
