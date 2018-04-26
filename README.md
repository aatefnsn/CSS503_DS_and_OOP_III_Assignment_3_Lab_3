UWB Bothell

Professor Name: Morris Bernstein

Course: CSS-503

Assignment #3

Read me file

Student Name: Ahmed Nada

***Assignment#3 description:***

Assignment 3 is testing my implementation of standard library functions
for reading, writing and seeking within a file.

- **ferror**

- **feof**

- **fflush**

- **fputc**

- **fgetc**

- **fgets**

- **fputs**

- **fseek**

and then verifying the numbers of reading the same JPEG file from lab3
versus the standard library and the Unix System calls.

***Output:***

anada@ubuntu:\~\$ cd Desktop/

anada@ubuntu:\~/Desktop\$ cd Lab3/

anada@ubuntu:\~/Desktop/Lab3\$ cd Assignment_3/

anada@ubuntu:\~/Desktop/Lab3/Assignment_3\$

anada@ubuntu:\~/Desktop/Lab3/Assignment_3\$ g++ -std=c++14 -pedantic -O3
file.cpp -Wall -Werror -c

anada@ubuntu:\~/Desktop/Lab3/Assignment_3\$

anada@ubuntu:\~/Desktop/Lab3/Assignment_3\$ cd ..

anada@ubuntu:\~/Desktop/Lab3\$ ./Build.sh

anada@ubuntu:\~/Desktop/Lab3\$ ./Run.sh

Unix system calls, chunk size 1 elapsed time:

2.714656115 seconds

bytes read: 4264394

C standard library I/O, block size 1 elapsed time:

0.045647144 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 1 elapsed time:

0.202258825 seconds

bytes read: 4264394

Unix system calls, chunk size 2 elapsed time:

1.327872992 seconds

bytes read: 4264394

C standard library I/O, block size 2 elapsed time:

0.053229094 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 2 elapsed time:

0.023648024 seconds

bytes read: 4264394

Unix system calls, chunk size 4 elapsed time:

0.594949961 seconds

bytes read: 4264394

C standard library I/O, block size 4 elapsed time:

0.030324936 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 4 elapsed time:

0.013355017 seconds

bytes read: 4264394

Unix system calls, chunk size 8 elapsed time:

0.296664000 seconds

bytes read: 4264394

C standard library I/O, block size 8 elapsed time:

0.015608788 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 8 elapsed time:

0.008538961 seconds

bytes read: 4264394

Unix system calls, chunk size 16 elapsed time:

0.149739981 seconds

bytes read: 4264394

C standard library I/O, block size 16 elapsed time:

0.006325960 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 16 elapsed time:

0.007472992 seconds

bytes read: 4264394

Unix system calls, chunk size 32 elapsed time:

0.085978031 seconds

bytes read: 4264394

C standard library I/O, block size 32 elapsed time:

0.003695011 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 32 elapsed time:

0.004395962 seconds

bytes read: 4264394

Unix system calls, chunk size 64 elapsed time:

0.046988010 seconds

bytes read: 4264394

C standard library I/O, block size 64 elapsed time:

0.002542019 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 64 elapsed time:

0.004448175 seconds

bytes read: 4264394

Unix system calls, chunk size 128 elapsed time:

0.030085087 seconds

bytes read: 4264394

C standard library I/O, block size 128 elapsed time:

0.003417969 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 128 elapsed time:

0.004558086 seconds

bytes read: 4264394

Unix system calls, chunk size 256 elapsed time:

0.017894983 seconds

bytes read: 4264394

C standard library I/O, block size 256 elapsed time:

0.001758099 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 256 elapsed time:

0.004844904 seconds

bytes read: 4264394

Unix system calls, chunk size 512 elapsed time:

0.006620884 seconds

bytes read: 4264394

C standard library I/O, block size 512 elapsed time:

0.010009050 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 512 elapsed time:

0.003854990 seconds

bytes read: 4264394

Unix system calls, chunk size 1024 elapsed time:

0.005126953 seconds

bytes read: 4264394

C standard library I/O, block size 1024 elapsed time:

0.002159834 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 1024 elapsed time:

0.006078005 seconds

bytes read: 4264394

Unix system calls, chunk size 2048 elapsed time:

0.003192186 seconds

bytes read: 4264394

C standard library I/O, block size 2048 elapsed time:

0.003128767 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 2048 elapsed time:

0.003908873 seconds

bytes read: 4264394

Unix system calls, chunk size 4096 elapsed time:

0.001308918 seconds

bytes read: 4264394

C standard library I/O, block size 4096 elapsed time:

0.001291037 seconds

bytes read: 4264394

File opened r+, File Descriptor is 3

My library I/O, block size 4096 elapsed time:

0.003822088 seconds

bytes read: 4264394

anada@ubuntu:\~/Desktop/Lab3\$ ./Run-2.sh

anada@ubuntu:\~/Desktop/Lab3\$

Putting this into a graph using GNUPLOT:

![A screenshot of a cell phone Description automatically
generated](./media/image1.png){width="6.5in"
height="4.378472222222222in"}

Data points:

Chunck-size Unix system-time-elapsed standard-I /O Library My library
implementation

anada@ubuntu:\~/Desktop/Lab3\$ cat data.dat

1 2.518743992 0.026169062 0.220435858

2 1.113156796 0.038650036 0.015634060

4 0.614616871 0.020211935 0.009725094

8 0.295335054 0.010317087 0.006893158

16 0.145519972 0.006082058 0.005203009

32 0.070276976 0.003705978 0.004252195

64 0.034284115 0.002553940 0.004171133

128 0.020128012 0.002133131 0.004345894

256 0.010396004 0.001663923 0.003934860

512 0.004832983 0.002927065 0.003950119

1024 0.002965927 0.002077103 0.003590107

2048 0.001786947 0.001739979 0.003717184

4096 0.001271963 0.001379967 0.003504992

anada@ubuntu:\~/Desktop/Lab3\$ gnuplot -p gnuplot.sh
