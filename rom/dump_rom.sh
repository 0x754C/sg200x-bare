#!/bin/sh

# slow, 120s

seq 0 24576 | while read line
do
	devmem $(printf "0x%08X" $((0x04418000 + line * 4)))
done
