#!/bin/bash

for i in $(cat common_sub.txt); do host $i.megacorpone.com |grep "has address"; done
