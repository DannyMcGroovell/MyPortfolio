import requests
import json

url = 'https://www.cbr-xml-daily.ru/daily_json.js'

def Exchange():
    response = requests.get(url)   
    json_data = json.loads(response.text)
    price = json_data['Valute']
    dollar = price['USD']
    a = round(dollar['Value'], 2)
    euro = price['EUR']
    b = round(euro['Value'], 2)
    c = round(b / a, 2)
    line = f"Курс доллара США:\t\t{a}\nКурс евро:\t\t\t{b}\nКурс доллара к евро:\t\t{c}"
    return line

result = Exchange()
print(result)
