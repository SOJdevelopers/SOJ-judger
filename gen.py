#!/usr/bin/python3

import random

ip = input('judger ip: ')
name = input('judger name: ')
passw = ''.join(random.choice('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ') for i in range(32))

print('password = {}\n'.format(passw));
print('please modify the database after getting the judger server ready:\n```')
print("insert into judger_info (judger_name, password, ip) values ('{}', '{}', '{}');".format(name, passw, ip))
print('```')

