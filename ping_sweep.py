#!/usr/bin/python

import ping,socket,sys,re

#ping every ip address in the 10.11.1.0/24 range

cidr = raw_input("\n Would you like to ping sweep a /16 or /24 network? (16) or (24)? ") 

if str(cidr) == "16" or str(cidr) == "/16":
     while True:
         ip_set1 = raw_input("\n Please enter the first octet desired ip set within the /16 CIDR, e.g 192: ")
     
         if int(ip_set1) >= 0 and int(ip_set1) <= 255:
              ip_set2 = raw_input("\n Please enter the second octet desired ip set within the /16 CIDR, e.g 168: ")

              if int(ip_set2) >= 0 and int(ip_set2) <= 255:

                  try: 
                      for i in range(255):
                          f = 0
                          while f < 255:
                              ip_string = str(ip_set1) + "." + str(ip_set2) + "." + str(f) + "." + str(i)  
#                              sys.stdout = open('ping_sweep_py.log', 'a')
                              ping.verbose_ping(ip_string, count=1)
                              f += 1

                  except socket.error, e:
                      print "ping error:",e


elif str(cidr) == "24" or cidr == "/24":
     
    ip_set = raw_input("\n Please enter the first three octets desired ip set within the /24 CIDR, e.g 192.168.1: ")

    prog = re.compile("^\d{1,3}\.\d{1,3}\.\d{1,3}$")

    if prog.match(ip_set):

        try: 
           for i in range(255):
               ip_string = str(ip_set) + "." + str(i)
#              sys.stdout = open('ping_sweep_py.log', 'a')
               ping.verbose_ping(ip_string, count=1)

        except socket.error, e:
            print "ping error:",e
    else:
        print "Not a valid ip"
else:
    print("Please enter either 16 or 24 ")
