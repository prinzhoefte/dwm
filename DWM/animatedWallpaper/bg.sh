path=/home/justin/code/dwm/DWM/animatedWallpaper/feh
frames=$(cd $path/ && ls | wc -l)

while [ true ]
do
    for ((i = 1; i <= $frames; i++)); do
        img=$path/BG$i.jpg
        feh --bg-scale $img
        sleep 0.02
    done
done