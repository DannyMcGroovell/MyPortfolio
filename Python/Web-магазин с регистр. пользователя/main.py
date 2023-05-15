from Category import Category
from Good import Good
from Catalog import Catalog
from Cart import Cart
from Users import Users

cat1 = Category(1, "Европейские автомобили")
cat2 = Category(2, "Японские автомобили")

good1 = Good(1, "Skoda", 1000, cat1)
good2 = Good(2, "Audi", 1000, cat1)
good3 = Good(3, "BMW", 1000, cat1)
good4 = Good(4, "Lexus", 1000, cat2)
good5 = Good(5, "Toyota", 1000, cat2)

goods = [good1, good2, good3, good4, good5]

catalog = Catalog(goods)

users = Users()
user = users.start()
if user:
    cart = Cart([])
    catalog.show_catalog()

    while True:
        good_id = int(input("Введите id товара, который желаете добавить в корзину "
                            "или введите -1 для перехода в корзину покупок: "))
        if good_id > 0:
            good = catalog.get_good_by_id(good_id)
            if good:
                cart.add_good(good,user.id)
                cart.show_cart()
        else:
            cart.show_cart()
            break

    cart.remove_good_in_cart(good2, 'ADMIN')

    cart.update_good_in_cart('ADMIN', 3)
