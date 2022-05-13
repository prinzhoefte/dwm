#!/bin/sh

# A dwm_bar function to read the battery level and status
# Joe Standring <git@joestandring.com>
# GNU GPLv3

dwm_battery () {
    # Change BAT1 to whatever your battery is identified as. Typically BAT0 or BAT1
    CHARGE=$(cat /sys/class/power_supply/BAT0/capacity)%

    printf " %s" "$CHARGE"
    printf "|"
}

dwm_battery

