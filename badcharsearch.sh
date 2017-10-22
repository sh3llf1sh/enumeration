#!/bin/bash

shellcode=`for i in $( cat bad_payload.txt ); do echo $i |cut -d"\"" -f2 ; done`

shellcode_formatted=$(echo $shellcode |tr -d " ")

IFS='\x'
read -r -a code <<< "$shellcode_formatted"

counter=0

for i in "${code[@]}"
do
    if [ "$i" == "" ]
    then
           :
    else 
           if [ "$i" == "0d" ] || [ "$i" == "0a" ] || [ "$i" == "00" ]
           then
                  counter=$((counter + 1))
           else
                  :
           fi
    fi
done


if [ $counter -gt 0 ] 
then
      echo "shellcode contains $counter bad characters. Adjust code and try again"
      exit 0 
else
      echo "Shellcode is all clean. Happy pwning"
      exit 0
fi
