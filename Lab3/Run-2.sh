#! /bin/bash
for ((i=1; i<=4096; i*=2))
do
printf $i >> data.dat
./a.out 20190211_070835.jpg $i | grep -A 1 "size" | grep "seconds" | tr -d "seconds" | tr -d '\n' >> data.dat
printf '\n' >> data.dat
done
