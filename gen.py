#!/usr/bin/python3

import random

ip = input('judger ip: ')
name = input('judger name: ')
sojip = input('soj server ip: ')
sojpas = input('soj socket password: ')

passw = ''.join(random.choice('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ') for i in range(32))

print('password = {}\n'.format(passw))
print('please modify the database after getting the judger server ready:\n```')
print("insert into judger_info (judger_name, password, ip, enabled) values ('{}', '{}', '{}', '{}');".format(name, passw, ip, 1))
print('```')

fconf = open(".conf.json", "w")

print('''{}
	"uoj_protocol": "http",
	"uoj_host": "{}",
	"judger_name": "{}",
	"judger_password": "{}",
	"socket_port": 2333,
	"socket_password": "{}"
{}'''.format('{', sojip, name, passw, sojpas, '}'), file = fconf)

fconf.close()