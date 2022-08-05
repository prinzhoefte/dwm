path=/home/justin/code/dwm/DWM/animatedWallpaper/JapaneseShop
frames=$(cd $path/ && ls | wc -l)

while [ true ]
do
    for ((i = 1; i <= $frames; i++)); do
        img=$path/BG$i.jpg
        feh --bg-scale $img
        sleep 0.05
    done
done