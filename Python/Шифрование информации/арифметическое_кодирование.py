def get_dict_from_singal():
    singal_dict = {}
    singal_dict['Л'] = (0, 0.04)
    singal_dict['Е'] = (0.04, 0.32)
    singal_dict['Б'] = (0.32, 0.36)
    singal_dict['Д'] = (0.36, 0.4)
    singal_dict['В'] = (0.4, 0.52)
    singal_dict[' '] = (0.52, 0.6)
    singal_dict['Э'] = (0.6, 0.64)
    singal_dict['Р'] = (0.64, 0.68)
    singal_dict['Н'] = (0.68, 0.76)
    singal_dict['С'] = (0.76, 0.8)
    singal_dict['Т'] = (0.8, 0.84)
    singal_dict['Г'] = (0.84, 0.88)
    singal_dict['Ь'] = (0.88, 0.92)
    singal_dict['И'] = (0.92, 0.96)
    singal_dict['Ч'] = (0.96, 1)
    return singal_dict
 
 
def encoder(singal, singal_dict):
    Low = 0
    High = 1
    for s in singal:
        CodeRange = High - Low
        High = Low + CodeRange * singal_dict[s][1]
        Low = Low + CodeRange * singal_dict[s][0]
    return Low
 
 
def decoder(encoded_number, singal_dict, singal_length):
    singal = []
    while singal_length:
        for k, v in singal_dict.items():
            if v[0] <= encoded_number < v[1]:
                singal.append(k)
                range = v[1] - v[0]
                encoded_number -= v[0]
                encoded_number /= range
                break
        singal_length -= 1
    return singal
 
 
def main():
    singal_dict = get_dict_from_singal()
    singal = 'ЛЕБЕДЕВ ЭРНЕСТ ЕВГЕНЬЕВИЧ'
    ans = encoder(singal, singal_dict)
    print(ans)
    singal_rec = decoder(ans, singal_dict, len(singal))
    print(singal_rec)
 
 
if __name__ == '__main__':
    main()
