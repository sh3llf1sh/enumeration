#!/usr/bin/python

import socket

ip = str(raw_input("What IP adddress would you like to connect to: \n"))
port = int(raw_input("What port would you like to connect to: \n"))

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

try:
    print "\nConnection evil buffer..."
    sock.connect((ip, port))
    data = sock.recv(1024)
    print data

except:
    print "Could not connect to POP3!"

