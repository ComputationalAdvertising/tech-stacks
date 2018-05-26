#!/usr/bin/env python
#-*- coding: utf-8 -*-

import ctypes

so = ctypes.cdll.LoadLibrary
lib = so("./libpycallclass.so")

print('lib.display:')
lib.display()
print('lib.display_int')
result = lib.display_int(10000)
print ('result: {}'.format(result))
