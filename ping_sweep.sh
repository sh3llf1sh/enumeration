#!/bin/bash
for i in {1..255}; do ping -c1 10.11.1.$i; done >> ping.log

