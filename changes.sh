#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo "Usage: ./changes.sh <file1> <file2> <file3> or <all> for all files"
    exit 0
fi

if [ "$1" == "all" ]; then 
    echo "Please enter a commit message"
    read commit 
    git add --all
    git push
    git commit -m "$commit"
    exit 0
fi

counter=1

while [ $counter -le $# ] ; do
       
    if [ ! -f $(eval "echo \$$counter") ]; then
        eval "echo \$$counter: file not found" 
        exit 1
    fi
    counter=$((counter+1))
done

counter2=1

while [ $counter2 -le $# ] ; do
    file=$(eval "echo \$$counter2")
    file_names="$file_names $file"
    counter2=$((counter2+1))
done

echo "Please enter a commit message"
read commit

git add$file_names
git push
git commit -m "$commit"
