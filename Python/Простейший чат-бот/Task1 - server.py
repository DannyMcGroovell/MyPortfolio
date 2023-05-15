from socket import *
from datetime import datetime

s = socket(AF_INET, SOCK_STREAM)
s.bind(('', 8004))
s.listen(5)

while True:
    client, adrr = s.accept()
    print(f"\nУстановлено соединение с {adrr}")
    while True:
        data = client.recv(10000000)
        if not data:
            print(f"\nСоединение с {adrr} разорвано")
            break
        msg = data.decode("utf-8")
        answer = ""
        if "время" in msg:
            now = datetime.now()
            answer = now.strftime('%H:%M:%S')
        elif "день" in msg:
            now = datetime.now()
            answer = now.strftime('%A')
        elif "месяц" in msg:
            now = datetime.now()
            answer = now.strftime('%B')
        elif "год" in msg:
            now = datetime.now()
            answer = now.strftime('%Y')
        elif "неделя" in msg:
            now = datetime.now()
            answer = now.strftime('%W')
        elif "дата" in msg:
            now = datetime.now()
            answer = now.strftime('%x')
        else:
            answer = "\nВопрос задан некорректно. Попробуйте еще раз"
        client.send(answer.encode('utf-8'))
        print(f"\nВопрос: {msg.strip()}\nОтвет: {answer}")
    client.close()
