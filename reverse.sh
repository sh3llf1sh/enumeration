#!/bin/bash

for i in {72..91}; do host 38.100.193.$i |grep "megacorp" |cut -d" " -f1,5; done

