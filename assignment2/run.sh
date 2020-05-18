for s in images/*input.bmp
do
    # echo ${s}
    for i in {1..8}
    do
        ./main ${i} ${s} ${s}_o.bmp >> ${s}.txt
    done
    echo "######## trial end #######" >> ${s}.txt

done
    # ./main 1 logo.bmp logo_out.bmp >> log.txt
    # ./main 2 logo.bmp logo_out.bmp >> log.txt
    # ./main 3 logo.bmp logo_out.bmp >> log.txt
    # ./main 4 logo.bmp logo_out.bmp >> log.txt
    # ./main 5 logo.bmp logo_out.bmp >> log.txt
    # ./main 7 logo.bmp logo_out.bmp >> log.txt
    # ./main 8 logo.bmp logo_out.bmp >> log.txt
