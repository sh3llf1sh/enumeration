#!/usr/bin/python

import sys
import socket

if len(sys.argv[1]) != 2:
    print "Usage: vrfy.py <usernames_file>"
    sys.exit(0) 

# Create a Socket

users_file = open("users.txt", "r")

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the Server

connect=s.connect(('10.11.1.215',25))

# Receive the banner

banner=s.recv(1024)

print banner

# VRFY a user

for line in users_file:

    s.send('VRFY ' + line + '\r\n')
    result=s.recv(1024)
    print result

# Close the socket

s.close()

users_file.close()
