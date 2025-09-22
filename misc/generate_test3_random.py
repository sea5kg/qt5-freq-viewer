#!/usr/bin/python3

import random

with open("../testdata/test3_random.txt", "wt", encoding="utf-8", newline="\n") as _file:
    _file.write("# Test3 Random. Hz S RI R 50\n")
    _file.write("! Date: 05/02/2024 10:16:28 am\n")
    _file.write("! Freq            S11\n")
    _maximal = 270291000
    freq = 300000
    step = (_maximal - freq) / 10000
    while freq < _maximal:
        freq += step
        _file.write(f'{freq:.11E}')
        s11_real = random.uniform(-10.0, 10.0)
        _file.write(f' {s11_real:.11E}')
        s11_imag = random.uniform(-10.0, 10.0)
        _file.write(f' {s11_imag:.11E}')
        # -4.87396999163E-01 7.84601373270E-01

        _file.write("\n")
