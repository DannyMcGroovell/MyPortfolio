import random
import numpy as np
 
def Change_Type(num_list):
  num_list_new = [int(i) for i in num_list]
  return num_list_new
 
def Sequence_adjustment(list_created):
  M=np.mat((np.array([list_created])))
  print(M)
 
def matrix_multi(lista, listb):
  return [a*b for a,b in zip(lista,listb)]
 
def flip_bit(message, location):
    message[location] = 1 - message[location]
    return message
 
def binlist_to_int(list):
  result = 0
  for digit in list:
    result = (result << 1) | digit
  return result
 
def flip_random_bit(message):
  e = random.randint(1, len(message))
  print("Flipping bit (=introducing error) at location: " + str(e))
  message= flip_bit(message, e - 1)
 
 
def hamming_find_error(hamming):
  error_location_in_Ht_list = []
  for i in H:
    parity = matrix_multi(i, hamming).count(1) % 2
    error_location_in_Ht_list.append(parity)
  error_location_in_Ht = binlist_to_int(error_location_in_Ht_list) - 1
  if error_location_in_Ht >= 0:
    error_location_in_hamming = binlist_to_int(Ht[error_location_in_Ht])
  else:
    error_location_in_hamming = 0
  print('Where did we find an error? ' + str(error_location_in_hamming))
  return error_location_in_hamming
 
def hamming_correct(hamming):
  error_location = hamming_find_error(hamming)
  if error_location > 0:
    flip_bit(hamming, error_location - 1)
 
  return hamming
 


message=input('Input the message: ')
 
y=len(message)
print('the length of message y is: ', y)
 
p=0
while 2**p<p+1+y:
    p=p+1
print('the number of parity bits are: ', p)
 
x=y+p
print('the total length of hamming code is: ', x)
 
m = Change_Type(message)
print('the message is: ', m)
print('\n')


 
Ht=[]
for i in range(1,x+1):
 
  DEC_to_BIN = bin(i)[2:].zfill(p)
  L = list(reversed(Change_Type(DEC_to_BIN)))
  Ht.append(L)
 
Ht_tool=[]
for i in range(1,x+1):
 
  DEC_to_BIN = bin(i)[2:].zfill(p)
  L = list(reversed(Change_Type(DEC_to_BIN)))
  Ht_tool.append(L)

np.transpose(Ht_tool)
H=np.transpose(Ht_tool).tolist() 
H_tool=H

Parity_bit_list=[]
for j in range(0,p):
    Parity_bit_list.append(2**j)
 
Parity_bit_list.reverse()
for i in Parity_bit_list:
    del Ht_tool[i-1]
 
import numpy as np
np.transpose(Ht_tool)
H_tool=np.transpose(Ht_tool).tolist()
h=H_tool
 
print("The Ht matrix of the message is: ")
Sequence_adjustment(Ht)
print('\n')
print("The H matrix of the message is: ")
Sequence_adjustment(H)
print(type(H))
print('\n')
print("The h matrix of the message is: ")
Sequence_adjustment(h)
print('\n')


 
Parity = []
for i in h:
  message_and_h = matrix_multi(i, m)
  bit = message_and_h.count(1) % 2
  Parity.append(bit)
 
Parity_bit_list.reverse()
# print(Parity_bit_list)
encode=m
k=0
for i in Parity_bit_list:
  encode.insert(i-1,Parity[k])
  k+=1

print('The hamming encode message is: ',encode) 
encode_with_error=encode
flip_random_bit(encode_with_error)
print('The hamming code with error is: ',encode_with_error)
corrected_message=hamming_correct(encode_with_error)
print('The corrected message is: ', corrected_message)

Parity_bit_list.reverse()
for i in Parity_bit_list:
    del corrected_message[i-1]
print('The corrected message is: ', corrected_message)
