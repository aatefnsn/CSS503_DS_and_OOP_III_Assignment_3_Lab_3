//
// lab-03.cc
//
// Author: Morris Bernstein
// Copyright 2019, Systems Deployment, LLC.
//
// Based on work by Thread Management
//Implementation: Ahmed Nada UWB


#include <fcntl.h>  // open
#include <unistd.h>  // read
#include <sys/types.h>  // read
#include <sys/uio.h>  // read
#include <stdio.h>  // fopen, fread
#include <sys/time.h>  // gettimeofday
#include <string>
#include <iostream>

#include "file.h"

using namespace std;

const char *PROG_NAME = "none";

void usage();

class Timer {
public:

    Timer(const string& message) : message(message) {
        gettimeofday(&start, nullptr);
    }

    ~Timer() {
        struct timeval end;
        gettimeofday(&end, nullptr);
        double elapsed =
                ((double) end.tv_sec + (double) end.tv_usec / 1e6) -
                ((double) start.tv_sec + (double) start.tv_usec / 1e6);
        printf("%s elapsed time:\n\t%12.9f seconds\n", message.c_str(), elapsed);
    }

private:
    string message;
    struct timeval start;
};

class Unix_Reader {
public:

    Unix_Reader(char *filename) {
        // TODO(lab): open the file using the Unix system call; exit
        // program with failure if file cannot be opened.
        //cout << "Inside Unix_Reader about to open the file" << endl;
        fd_ = open(filename, O_RDONLY);
        if (fd_ < 0) {
            perror("c1");
            exit(1);
        }
        //cout << "File opened" << endl;
        //cout << "opened the fd: " << fd_ << endl;
        //printf("opened the fd = % d\n", fd_);
    }

    ~Unix_Reader() {
        // TODO(lab): close the file.
        //cout << "Closing File Descriptor" << endl;
        close(fd_);
    }

    int fd() {
        return fd_;
    }

private:
    int fd_;
};

class Stdio_Reader {
public:

    Stdio_Reader(char *filename) {
        // TODO(lab): open the file using the C standard I/O; exit
        // program with failure if file cannot be opened.
        f_ = fopen(filename, "r");
        if (f_ == nullptr) {
            printf("Error! opening file");
            exit(1);
        }
    }

    ~Stdio_Reader() {
        // TODO(lab): close the file.
        fclose(f_);
    }

    FILE *f() {
        return f_;
    }

private:
    FILE *f_;
};

void usage() {
    fprintf(stderr, "usage: %s filename chunk_size\n", PROG_NAME);
    fprintf(stderr, "   where chunk_size > 0\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    PROG_NAME = argv[0];
    if (argc != 3) {
        usage();
    }

    int chunk_size = atoi(argv[2]);
    if (chunk_size < 1) {
        usage();
    }

    char *filename = argv[1];
    char *buf = new char[chunk_size];

    int total_bytes_read = 0;
    int bytes_read = 0;
    {
        // Unix I/O
        Unix_Reader r{filename};
        int fd = r.fd();
        Timer t(string("Unix system calls, chunk size ") + to_string(chunk_size));
        // TODO(lab): read the file in chunks of chunk_size using Unix
        // File I/O.  Count the number of bytes read.  Exit the loop on
        // EOF.  Print error message and terminate the program if there is
        // an error reading the file.
        if (fd < 0) {
            perror("r1");
            exit(1);
        }
        while (true) {
            bytes_read = read(fd, buf, chunk_size);
            if (bytes_read < 0) {
                perror("Error Reading File");
                exit(1);
            }
            if (bytes_read == 0) {
                break;

            }
            //cout << total_bytes_read << endl;
            total_bytes_read = total_bytes_read + bytes_read;
        }
    }
    printf("\tbytes read: %d\n", total_bytes_read);

    total_bytes_read = 0;
    bytes_read = 0; // make sure bytes_read is reset, it should be equal to 0 as it break from the previous loop
    {
        // C standard library  I/O.
        Stdio_Reader r{filename};
        FILE *file = r.f();

        // TODO(lab): read the file in chunks of chunk_size using C
        // standard I/O.  If chunk_size is 1, use fgetc. Count the number
        // of bytes read.  Exit the loop on EOF.  Print error message and
        // terminate the program if there is an error reading the file.
        if (chunk_size == 1) {
            Timer t(string("C standard library I/O, block size ") + to_string(chunk_size));
            //cout << "Chunk_size is 1" << endl;
            while (true) {
                fgetc(file);
                //if (bytes_read == EOF) {
                if (feof(file)) {
                    break;
                }
                total_bytes_read++;
            }
        } else {
            Timer t(string("C standard library I/O, block size ") + to_string(chunk_size));
            while (true) {
                //bytes_read = fread(&buf, chunk_size, 1, file);
                bytes_read = fread(buf, 1, chunk_size, file);
                if (bytes_read < 0) {
                    perror("Error Reading File");
                    exit(1);
                }
                if (bytes_read == 0) {
                    break;
                }
                total_bytes_read = total_bytes_read + bytes_read;
            }
        }
    }
    printf("\tbytes read: %d\n", total_bytes_read);


    total_bytes_read = 0;
    bytes_read = 0; // make sure bytes_read is reset, it should be equal to 0 as it break from the previous loop
    {
        // my implementation of C library
        //File myFile{filename};
        File * myFile = new File(filename, "r+");
        //FILE *file = r.f();

        if (chunk_size == 1) {
            Timer t(string("My library I/O, block size ") + to_string(chunk_size));
            //cout << "Chunk_size is 1" << endl;
            int f;
            while (true) {
                f=myFile->fgetc();

                if (f ==-1) {
                    break;
                }
                total_bytes_read++;
            }
        } else {
            Timer t(string("My library I/O, block size ") + to_string(chunk_size));
            while (true) {
                //bytes_read = fread(&buf, chunk_size, 1, file);
                bytes_read = myFile->fread(buf, 1, chunk_size);
                if (bytes_read < 0) {
                    perror("Error Reading File");
                    exit(1);
                }
                if (bytes_read == 0) {
                    break;
                }
                total_bytes_read = total_bytes_read + bytes_read;
            }
        }
    }
    printf("\tbytes read: %d\n", total_bytes_read);


    exit(EXIT_SUCCESS);
}
