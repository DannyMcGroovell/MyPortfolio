import csv

wares = {
    "1": {
        "название": "Золотая нить",
        "цена": "35",
        "описание": "Прядение нити из чистого золота - очень долгий и трудоемкий процесс."
    },
    "2": {
        "название": "Волшебные бобы",
        "цена": "20",
        "описание": "Волшебные бобы подозрительно похожи на обычные... или наоборот?"
    },
    "3": {
        "название": "Песок времени",
        "цена": "30",
        "описание": "Не предназначен для игр, строительства и бросков в лица окружающих."
    },

    "4": {
        "название": "Масло",
        "цена": "10",
        "описание": "Самый обыкновенный брусок сливочного масла."
    }
}

def update(wares):
    with open('wares.csv', 'w') as file:
        columns = ['wares', 'title', 'price', 'description']
        obj = csv.DictWriter(file, fieldnames=columns)
        obj.writeheader()
        for i in wares.keys():
            file.write('%s,%s,%s, %s\n' % (i, wares[i]['название'], wares[i]['цена'], wares[i]['описание']))

def list(wares):
    update(wares)
    with open('wares.csv', 'r') as file:
        a = csv.reader(file)
        for row in a:
            print(' '.join(row))

def add(wares):
    update(wares)
    name = input('Введите название товара: ')
    price = input('Введите цену товара: ')
    description = input('Введите описание товара: ')
    numberOfGoods = input('Введите номер товара: ')
    for i in wares.keys():
        if numberOfGoods == i:
            print('Такой товар уже есть.')
            numberOfGoods = input('Введите другой номер товара: ')
    new = {}
    new['название']=name
    new['цена']=price
    new['описание']=description
    goods[numberOfGoods] = new
    print(wares)
    update(wares)

def delete(wares):
    update(wares)
    a = input("Введите номер товара, который хотите удалить: ")
    wares2 = wares.copy()
    for i in wares2.keys():
        if a == i:
            print(f"Товар № {i} удален.", wares.pop(i))
    print(wares)
    update(wares)

def search(wares):
    a = input("Введите название товара, который хотите найти: ")
    for i in wares.values():
        if a == i['название']:
            print(i.values())

while True:
    menu = input("Введите:\n - LIST, чтобы отобразить все имеющиеся товары;\n - ADD, чтобы добавить товар;\n - DELETE, чтобы удалить товар;\n - SEARCH, чтобы найти товар по имени;\n - EXIT, чтобы выйти.\n\n")
    if menu.upper() == "LIST":
        list(wares)
    if menu.upper() == "ADD":
        add(wares)
    if menu.upper() == "DELETE":
        delete(wares)
    if menu.upper() == "SEARCH":
        search(wares)
    if menu.upper() == "EXIT":
        break
