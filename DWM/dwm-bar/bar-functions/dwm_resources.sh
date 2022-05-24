#!/bin/sh

# A dwm_bar function to display information regarding system memory, CPU temperature, and storage
# Joe Standring <git@joestandring.com>
# GNU GPLv3

dwm_resources () {
	free_output=$(free -h | grep Speicher)
	MEMUSED=$(echo $free_output | awk '{print $3}')
	MEMTOT=$(echo $free_output | awk '{print $2}')
	CPU=$(top -bn1 | grep CPU | awk 'NR==1{print $2}')
	temp=$(sensors -u k10temp-pci-00c3 | grep temp1 | awk '{print $2}')
	newTemp=${temp%.*}

	printf "  %s| %s| %sC" "$MEMUSED" "$CPU" "$newTemp"
	printf "|"
}

dwm_resources
