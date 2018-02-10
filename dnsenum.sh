#!/bin/bash

if [ "$1" == "" ]; then
	echo "please supply a domain to enummerate e.g ./dnsenum google.co.uk"
        exit
elif [ "$1" == "-r" ]; then
     
     echo "Please provide the first three octets of the ip \n" 
     read cidr
     for ip in $(seq 1 254); do host 10.11.1.$ip |grep -v "not found"; done
       exit 0
else
	host=$1
fi

for i in $(host -t ns $host |cut -d " " -f 4); do
	host -l $host $i  
done
