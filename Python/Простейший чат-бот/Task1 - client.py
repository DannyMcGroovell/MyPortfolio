from socket import *

s = socket(AF_INET, SOCK_STREAM)
s.connect(("localhost", 8004))

while True:
    msg = input("\nВы зашли на страницу чат-бота! Что бы вы хотели узнать?(для выхода введите 'выход')\n")
    if msg == "выход":
        break
    s.send(msg.encode("UTF-8"))
    answer = s.recv(1000000000)
    print("\nОтвет от сервера: ", answer.decode("UTF-8"))

s.close()
