//
// file.h
//
// Implement the C standard I/O library in C++ style.
//
// Author: Morris Bernstein
// Copyright 2019, Systems Deployment, LLC.

#if !defined(FILE_H)
#define FILE_H

#include <cstddef> // for size_t
#include <exception>
#include <sys/types.h>// for mode_t
#include <unistd.h>
#include <cassert>
#include <cstdarg>
#include <fcntl.h>  // open
//#include <stdlib.h>
#include <iostream>

using namespace std;


class File {
public:
    //char *buf = (char*)malloc(bufsiz * sizeof(char));
    //char *buf = new char[bufsiz];

    class File_Exception : public std::exception {
      virtual const char* what() const throw()
  {
    return "My exception happened";
  }
} myex;

    enum BufferMode {
        NO_BUFFER,
        LINE_BUFFER,
        FULL_BUFFER
    };

    enum BufferState {
        UNDECIDED,
        READING,
        WRITING
    };

    enum FileAccessMode { // file open status
        READING_ONLY,
        READING_AND_WRITING,
        WRITING_ONLY
    };

    // Use lowercase because system header files #define the uppercase
    // names.

    enum Whence {
        seek_set,
        seek_cur,
        seek_end
    };

    static const int bufsiz = 8192;
    //static const int bufsiz = 6;
    static const int eof = -1;

    // Open a file.
    // Mode can be "r", "r+", "w", "w+",
    // Modes "a", and "a+" are unsupported.
    // Use default buffering: FULL_BUFFER.
    File(const char *name, const char *mode = "r");

    // Close the file.  Make sure any buffered data is written to disk,
    // and free the buffer if there is one.
    ~File();

    // Return non-zero value if the file is in an error state.
    // When the file is in an error state, I/O operations are not
    // performed and appropriate values are returned.
    int ferror();

    // Return true if end-of-file is reached.  This is not an error
    // condition.  Reading past eof is an error.
    bool feof();

    // Add a user-defined buffer and set the buffering mode.  If
    // non-null, the buffer must have been created by malloc and will be
    // freed by the destructor (or by another call to setvbuf).
    // LINE_BUFFER mode need not be supported.
    int setvbuf(char *buf, BufferMode mode, size_t size);

    // Like fpurge but if buffered data is outgoing, write data to
    // disk.  Reset the file pointer so it behaves the way the user
    // would expect.
    int fflush();

    // If the amount of data to be read or written exceeds the buffer,
    // avoid double-buffering by reading/writing data directly to/from
    // the source/destination.
    size_t fread(void *ptr, size_t size, size_t nmemb);
    size_t fwrite(const void *ptr, size_t size, size_t nmemb);

    int fgetc();
    int fputc(int c);

    char *fgets(char *s, int size);
    int fputs(const char *str);

    // Flush any buffered data and reset the file pointer.
    int fseek(long offset, Whence whence);

    // Stripped-down version: only implements %d and %s format codes.
    int fprintf(const char *format, ...);

private:
    int fd_;
    BufferState buf_state = UNDECIDED;
    FileAccessMode file_access_mode;

    //unsigned char *buf = (unsigned char*) malloc(bufsiz * sizeof (unsigned char));
    int cur_buf_size = 0;
    unsigned char *buf = new unsigned char[bufsiz];
    bool err=false;
    //unsigned char *reading_buf = buf;
    //char *buf = (char*)malloc(bufsiz * sizeof(char));
    // Disallow copy & assignment.
    File(File const&) = delete;
    File& operator=(File const&) = delete;
};

#endif
