#!/usr/bin/python

import sys
import socket
import re

if len(sys.argv) != 3:
        print "Usage: smtp-enum-vrfy.sh <first_3_octets_of_class_c_ip_address> <username> e.g smtp-enum-vrfy.sh 192.168.1"
        sys.exit(0)

# open socket


# connect to chosen ip range

prog = re.compile("^\d{1,3}\.\d{1,3}\.\d{1,3}$")

if prog.match(sys.argv[1]):

    for i in range(255):
        try:
           ip_string = str(sys.argv[1]) + "." + str(i)
#           sys.stdout = open('ping_sweep_py.log', 'a')
           s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
           con=s.connect((ip_string,25))
	   banner=s.recv(1024) + ip_string
           print banner
           s.send('VRFY ' + sys.argv[2] + '\r\n')
           result=s.recv(1024)
           print result
           s.close()
           
        except socket.error, e:
            pass
else:
    print "Not a valid ip"

