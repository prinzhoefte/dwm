LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

export IDENTIFIER="unicode"

. "$DIR/bar-functions/dwm_resources.sh"

while true
do
    upperbar=""
    upperbar="$upperbar$(dwm_resources)"
   
    lowerbar=""

    xsetroot -name "$upperbar"
    
    sleep 1
done
