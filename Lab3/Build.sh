#! /bin/bash
cd Assignment_3
g++ -std=c++14 file.cpp -O3 -pedantic -Wall -Werror -c
cd ..
g++ -std=c++14 -pedantic -Wall -Werror -O3 -I./Assignment_3 ./main.cpp ./Assignment_3/file.o
