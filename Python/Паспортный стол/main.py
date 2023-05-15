from passport import Passport
from passport_list import Passport_list

name_1 = Passport(4, 6, 'Семенов Константин Егорович')
fil1_1 = name_1.fill()
name_2 = Passport(4, 6, 'Шевелев Кирилл Георгиевич')
fil1_2 = name_2.fill()
name_3 = Passport(4, 6, 'Спиридонова Ксения Ивановна')
fil1_3 = name_3.fill()
name_4 = Passport(4, 6, 'Воронин Тихон Матвеевич')
fil1_4 = name_4.fill()
name_5 = Passport(4, 6, 'Максимова Виктория Михайловна')
fil1_5 = name_5.fill()
name_6 = Passport(4, 6, 'Максимова Виктория Михайловна')
fil1_6 = name_6.fill()
array_1 = []
array_2 = {}

array_1.append(name_1)
array_1.append(name_2)
array_1.append(name_3)
array_1.append(name_4)
array_1.append(name_5)
array_1.append(name_6)

array_2[name_1.fio] = fil1_1
array_2[name_2.fio] = fil1_2
array_2[name_3.fio] = fil1_3
array_2[name_4.fio] = fil1_4
array_2[name_5.fio] = fil1_5
array_2[name_6.fio] = fil1_6

ps = Passport_list(array_1,array_2)
ps.check()
ps.search(4573, 932731)
