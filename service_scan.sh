#!/bin/bash

if [ $# -ne 2 ]; then
   echo "usage: $0 -p <port_number> -i <class_c_ip_range> i.e $0 80 192.168.1.0-255" ; exit 1
fi

port_to_check=$1

ip_range=$2

re="^[0-9]+$"

if ! [[ "$port_to_check" =~ $re ]] ; then
   echo "error: Not a number" >&2; exit 1
fi

if [ $port_to_check -gt 65535 ] || [ $port_to_check -lt 1 ] ; then
   echo "error: invalid number" >&2; exit 1
fi

ip_add=$(echo "$ip_range" |cut -d"-" -f1)
ip_range_address=$(echo "$ip_range" |cut -d"-" -f2)

re2="^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$"

if ! [[ "$ip_add" =~ $re2 ]] ; then
   echo "error: Please enter a valid class c ip range i.e 10.10.10.0-254" >&2; exit 1
fi

if ! [[ "$ip_range_address" =~ $re ]] ; then
   echo "error: Please enter a valid range for a class c address i.e 10.10.10.0-254" >&2; exit 1
fi

if [ $ip_range_address -gt 255 ] || [ $ip_range_address -lt 1 ] ; then
   echo "error: Please enter a valid range for a class c address i.e 10.10.10.0-254" ; exit 1
fi   

filename=$(cat /dev/urandom |tr -dc '[0-9A-Za-z]' |fold -w 10 |head -n 1)

/usr/bin/nmap -sn -oG /tmp/$filename $ip_range > /dev/null 2>&1

echo "Number of hosts up: $(wc -l /tmp/$filename)"   

filename2=$(cat /dev/urandom |tr -dc '[0-9A-Za-z]' |fold -w 10 |head -n 1)


for line in $(cat /tmp/$filename |grep "Host" |cut -d" " -f2); do
    nmap -sT -p 445 --append-output -oG /tmp/$filename2 $line > /dev/null 2>&1
done

echo "Number of hosts with open SMB ports: $(cat /tmp/$filename2 |grep 'Host' |grep 'open'|cut -d ' ' -f2 |wc -l) "

for host in $(cat /tmp/$filename2 |grep 'Host' |grep 'open'|cut -d ' ' -f2); do
    nmap --append-output -oG smb-os.txt --script smb-os-discovery $host
done

rm /tmp/$filename /tmp/$filename2
