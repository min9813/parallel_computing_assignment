rm log/*.txt
for s in 10 100 1000 10000 100000 1000000 10000000 100000000
do
    echo s
    touch log/${s}.txt
done