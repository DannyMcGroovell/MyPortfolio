from typing import List
from math import log2, ceil
from random import randrange


def __hamming_common(src: List[List[int]], s_num: int, encode=True) -> None:
    s_range = range(s_num)

    for i in src:
        sindrome = 0
        for s in s_range:
            sind = 0
            for p in range(2 ** s, len(i) + 1, 2 ** (s + 1)):
                for j in range(2 ** s):
                    if (p + j) > len(i):
                        break
                    sind ^= i[p + j - 1]

            if encode:
                i[2 ** s - 1] = sind
            else:
                sindrome += (2 ** s * sind)

        if (not encode) and sindrome:
            i[sindrome - 1] = int(not i[sindrome - 1])


def hamming_encode(msg: str, mode: int=8) -> str:
    result = ""

    msg_b = msg.encode("utf-8")
    s_num = ceil(log2(log2(mode + 1) + mode + 1))  
    bit_seq = []
    for byte in msg_b:
        bit_seq += list(map(int, f"{byte:08b}"))

    res_len = ceil((len(msg_b) * 8) / mode)
    bit_seq += [0] * (res_len * mode - len(bit_seq))

    to_hamming = []

    for i in range(res_len):
        code = bit_seq[i * mode:i * mode + mode]
        for j in range(s_num):
            code.insert(2 ** j - 1, 0)
        to_hamming.append(code)

    __hamming_common(to_hamming, s_num, True)

    for i in to_hamming:
        result += "".join(map(str, i))

    return result


def hamming_decode(msg: str, mode: int=8) -> str:
    result = ""

    s_num = ceil(log2(log2(mode + 1) + mode + 1))
    res_len = len(msg) // (mode + s_num)
    code_len = mode + s_num

    to_hamming = []

    for i in range(res_len):
        code = list(map(int, msg[i * code_len:i * code_len + code_len]))
        to_hamming.append(code)

    __hamming_common(to_hamming, s_num, False)

    for i in to_hamming:
        for j in range(s_num):
            i.pop(2 ** j - 1 - j)
        result += "".join(map(str, i))

    msg_l = []

    for i in range(len(result) // 8):
        val = "".join(result[i * 8:i * 8 + 8])
        msg_l.append(int(val, 2))

    result = bytes(msg_l).decode("utf-8")

    return result


def noizer(msg: str, mode: int) -> str:
    seq = list(map(int, msg))
    s_num = ceil(log2(log2(mode + 1) + mode + 1))
    code_len = mode + s_num
    cnt = len(msg) // code_len
    result = ""

    for i in range(cnt):
        to_noize = seq[i * code_len:i * code_len + code_len]
        noize = randrange(code_len)
        to_noize[noize] = int(not to_noize[noize])
        result += "".join(map(str, to_noize))

    return result


if __name__ == "__main__":
    MODE = 8    # count of signifed bits
    msg = "ЛЭЕ"
    print("Строка:", msg)

    enc_msg = hamming_encode(msg, MODE)
    print("Закодированная строка:", enc_msg)

#    noize_msg = noizer(enc_msg, MODE)
#    print("nz: ", noize_msg)

#    dec_msg = hamming_decode(noize_msg, MODE)
#    print("dec:", dec_msg)
