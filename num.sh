#!/bin/bash -x

reg="^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$"

if ! [[ "$1" =~ $reg ]] ; then
    echo "not aNumber";
fi
