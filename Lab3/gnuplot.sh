#!/usr/bin/gnuplot
set grid xtics ytics

set logscale y

set xrange[0:4500]

set ylabel "runtime (seconds)"
set xlabel "buffer size"

plot \
"data.dat" u 1:2 t "Unix Syscalls" w lines,\
"data.dat" u 1:3 t "C Standard I/O" w lines,\
"data.dat" u 1:4 t "My Library implementation" w lines

reset session
