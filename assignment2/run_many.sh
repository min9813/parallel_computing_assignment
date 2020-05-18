for i in {1..100}
do
    echo "start " ${i}
    ./main 1 100 >> log/100.txt
    ./main 1 1000 >> log/1000.txt
    ./main 1 10000 >> log/10000.txt
    ./main 1 100000 >> log/100000.txt
    ./main 1 1000000 >> log/1000000.txt
    ./main 1 10000000 >> log/10000000.txt
    ./main 1 100000000 >> log/100000000.txt

    echo "finish " ${i}

done