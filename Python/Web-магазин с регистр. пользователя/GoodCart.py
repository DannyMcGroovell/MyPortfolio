from Good import Good


class GoodCart(Good):

    def __init__(self, id, title, price, category,quantity,user_id):
        super().__init__(id, title, price, category)
        self.user_id = user_id
        self.quantity = quantity

    def __str__(self):
        return f"id:{self.id}, title:{self.title}," \
               f"price:{self.price},quantity: {self.quantity}"
