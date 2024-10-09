def string_to_binary(st : str):
    return [bin(ord(i))[2:].zfill(8) for i in st]

def binary_to_string(bits):
    return ''.join([chr(int(i, 2)) for i in bits])

st = "ЛЭЕ"
print("Строка: ", st)
b = string_to_binary(st)
bt = "".join(b)
print("Конвертация строки в двоичный код: ", bt)
s = binary_to_string(b)
print("Конвертация двоичного кода обратно в строку: ", s)
