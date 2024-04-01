#!/bin/bash

while read line
do
	echo -ne "\x$(echo -n "$line" | head -c 2 | tail -c 2)"
	echo -ne "\x$(echo -n "$line" | head -c 4 | tail -c 2)"
	echo -ne "\x$(echo -n "$line" | head -c 6 | tail -c 2)"
	echo -ne "\x$(echo -n "$line" | head -c 8 | tail -c 2)"
done
