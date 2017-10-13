#!/bin/bash

if [ "$1" == "" ]; then
	echo "please supply a domain to enummerate e.g ./dnsenum google.co.uk"
        exit
else
	host=$1
fi

for i in $(host -t ns $host |cut -d " " -f 4); do
	host -l $host $i  
done
