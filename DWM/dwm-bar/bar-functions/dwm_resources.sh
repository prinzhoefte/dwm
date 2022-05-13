#!/bin/sh

# A dwm_bar function to display information regarding system memory, CPU temperature, and storage
# Joe Standring <git@joestandring.com>
# GNU GPLv3

dwm_resources () {
	free_output=$(free -h | grep Mem)
	MEMUSED=$(echo $free_output | awk '{print $3}')
	MEMTOT=$(echo $free_output | awk '{print $2}')
	CPU=$(top -bn1 | grep Cpu | awk '{print $2}')%

	printf " %s| %s" "$MEMUSED" "$CPU"
	printf "|"
}

dwm_resources
