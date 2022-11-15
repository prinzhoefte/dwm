LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

export IDENTIFIER="unicode"

export SEP1="["
export SEP2="]"

xcompmgr -c &

. "$DIR/bar-functions/dwm_resources.sh"
. "$DIR/bar-functions/dwm_battery.sh"
. "$DIR/bar-functions/dwm_date.sh"

while true
do
    upperbar=""
    upperbar="$upperbar$(dwm_resources)"
    upperbar="$upperbar$(dwm_battery)"
    upperbar="$upperbar$(dwm_date)"

    lowerbar=""

    xsetroot -name "$upperbar"

    sleep 1
done
