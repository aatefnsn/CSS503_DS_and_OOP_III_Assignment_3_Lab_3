//
// file.cc
//
// Implement the C standard I/O library in C++ style.
//
// Author: Morris Bernstein
// Copyright 2019, Systems Deployment, LLC.
// Implementation: Ahmed Nada

#include "file.h"

File::File(const char *name, const char *mode) {

    if (*mode == 'r') { // open mode for read
        mode++;
        if (*mode == '+') { // if open mode is r+ give r 4 and w 2 writes to all users, groups so 0666
            fd_ = open(name, O_RDWR, 00666);
            this->file_access_mode = READING_AND_WRITING;
            if (fd_ < 0) {
                perror("c1");
                exit(1);
            } else {
                cout << "File opened r+, File Descriptor is " << fd_ << endl;
            }
        } else {
            fd_ = open(name, O_RDONLY, 00444); // give read 4 only rights to all users, groups
            this->file_access_mode = READING_ONLY;
            if (fd_ < 0) {
                perror("c1");
                exit(1);
            } else {
                cout << "File opened r, File Descriptor is " << fd_ << endl;
            }
        }
    } else if (*mode == 'w') {
        mode++;
        if (*mode == '+') {
            fd_ = open(name, O_RDWR | O_CREAT | O_TRUNC, 00666); // w+ give read and write rights to all users, groups
            this->file_access_mode = READING_AND_WRITING;
            if (fd_ < 0) {
                perror("c1");
                exit(1);
            } else {
                cout << "File opened w+, File Descriptor is " << fd_ << endl;
            }
        } else {
            fd_ = open(name, O_WRONLY | O_CREAT | O_TRUNC, 00222); // w give wirte 2 only for all users. groups
            this->file_access_mode = WRITING_ONLY;
            if (fd_ < 0) {
                perror("c1");
                exit(1);
            } else {
                cout << "File opened w, File Descriptor is " << fd_ << endl;
            }
        }
    } else {
        cout << "File operation not allowed" << endl;
    }
}

File::~File() {
    free(buf); // delete memory allocated buffer
    close(fd_); // close file
}

int File::ferror() {
    if (err == true) { // if err flag is set return 1
        return 1;
    } else {
        return 0; // else return 0
    }
}

bool File::feof() {
    int ch = this->fgetc(); // probe the next char
    lseek(this->fd_, -1, SEEK_CUR); //revert back the pointer to the current element
    if (ch == -1) { // if the fgetc is -1 then this is EOF and return true
        return true;
    } else {
        return false; // else return false
    }
}

int File::setvbuf(char *buf, BufferMode mode, size_t size) {
    assert(0); // Not implemented.
}

// Like fpurge but if buffered data is outgoing, write data to
// disk.  Reset the file pointer so it behaves the way the user
// would expect.

int File::fflush() {
    int bytes_written = -1;
    if ((this->file_access_mode == READING_AND_WRITING || this->file_access_mode == WRITING_ONLY) && this->buf_state == WRITING && cur_buf_size > 0) { // try fflush on a file open for reading only
      // check if the file access mode has writing and if the buffer state last activity was used for writing and if the cur buffer size is more than 0
        this->buf = this->buf - cur_buf_size; // scroll back the buffer to where it should start writing
        bytes_written = write(this->fd_, (unsigned char *) this->buf, this->cur_buf_size); // write data and flush
        this->buf = (unsigned char*) malloc(bufsiz * sizeof (unsigned char)); // flush the buffer
        this->cur_buf_size = 0; // set the buffer size to 0
        if (bytes_written >= 0) {
            return 0;
        } else {
            this->err = true; // set err flag is write was not successful
            return bytes_written; // -1
        }
    } else if (this->buf_state == READING && cur_buf_size > 0) { // if the buffer was last used for reading then reposition it
        this->fseek(-(this->cur_buf_size), seek_cur); // re-position file pointer and flush
        this->buf = (unsigned char*) malloc(bufsiz * sizeof (unsigned char)); // flush
        this->cur_buf_size = 0; // set current buffer size to 0
    }
    return bytes_written; // placeholder
}

size_t File::fread(void *ptr, size_t size, size_t nmemb) {
    if (this->file_access_mode == WRITING_ONLY) {
        this->err = true; // set err flag to true if reading from a write only file
        throw "Reading a write only file is not allowed!";
    }

    size_t bytes_read = 0;
    unsigned char* pChar;
    pChar = (unsigned char *) ptr;

    int flush;
    if (this->buf_state == WRITING) { // if buffer was last used for writing then flush
        flush = this->fflush(); // make sure to empty the buffer before starting to read
        if (flush == 0) {
            cout << "Flush successful" << endl;
        } else {
            cout << "Nothing to flush" << endl;
        }
    }
    this->buf_state = READING; // set the buffer state
    if ((nmemb * size) < (size_t) bufsiz) { // if buffer size is greater than the reuested bytes
        if (cur_buf_size == 0) { // if the cur buffer size is 0
            if (lseek(this->fd_, 0, SEEK_CUR) > 0) { // if buf size is 0 and
              //file pointer is greater than zero means that this is not the first time
              //reading so if buffer is empty means it was used before and was emptied so time to reset the pointer
                buf = buf - bufsiz; //reset the pointer
            }

            cur_buf_size = read(this->fd_, this->buf, this->bufsiz); // reading data equal to buffer size
            if ((size_t) cur_buf_size < (nmemb * size)) { // in case no data buffered and the
              //total size of file is less than nmemb re-adjust the amount of requested data
                nmemb = cur_buf_size / size; // re-adjust the requested dta
            }
            if (cur_buf_size < 0) {
                perror("Error Reading File");
                exit(1);
            } else {
                for (size_t i = 0; i < (nmemb * size); i++) {
                    unsigned char c = (unsigned char) buf[i];
                    pChar[i] = c; // copy data into the user buffer
                }
                buf = buf + (nmemb * size); // increment the buffer pointer
                cur_buf_size = cur_buf_size - (nmemb * size); // decrement the buffer size
                return nmemb*size; // return the requested data count
            }
        } else if ((cur_buf_size > 0) && ((nmemb * size) <= (size_t) cur_buf_size)) { // if there is space
          // in the buffer just copy the data, move the buffer forward and decrement the size
            for (unsigned i = 0; i < (nmemb * size); i++) {
                unsigned char c = (unsigned char) buf[i];
                pChar[i] = c;
            }
            buf = buf + (nmemb * size);
            cur_buf_size = cur_buf_size - (size * nmemb);
            return nmemb*size;
        } else if (cur_buf_size > 0 && (nmemb * size) > (size_t) cur_buf_size) { // if there is no
          //enough space in the buffer to read the requested data
            int nmemb2 = nmemb;
            int remaining = cur_buf_size; // get the number of remaining bytes in the buffer
            buf = buf + remaining; // moving buffuer forward to start reading after the remianing chars
            cur_buf_size = read(this->fd_, this->buf, (this->bufsiz - remaining)); // read data equal to the buffer size - remaining
            if (cur_buf_size == 0) { // EOF and no data read
                cur_buf_size = cur_buf_size + remaining;
                buf = buf - remaining; // reverting buffer again to where it was
                if ((size_t) cur_buf_size < (size * nmemb)) {
                    nmemb2 = cur_buf_size / size;
                    for (size_t i = 0; i < (nmemb * size); i++) { // copy data
                        unsigned char c = (unsigned char) buf[i];
                        if (c == ' ') {
                            pChar[i] = ' ';
                        } else {
                            pChar[i] = c;
                        }
                    }
                    buf = buf + (nmemb * size); // increment the buffer
                    cur_buf_size = cur_buf_size - (size * nmemb); // decrement the cur buf size
                    return remaining;
                }
            }

            cur_buf_size = cur_buf_size + remaining; // incrementing the buffer size cur_buf_size should be equal to bufsiz
            buf = buf - remaining; // reverting buffer again to where it was
            if ((size_t) cur_buf_size < (size * nmemb)) { // if after reading the buffer size is
              //less than the requested data, update the requested data size, copy data and return
                nmemb2 = cur_buf_size / size;
                for (size_t i = 0; i < (nmemb * size); i++) { // copy data
                    unsigned char c = (unsigned char) buf[i];
                    if (c == ' ') {
                        pChar[i] = ' ';
                    } else {
                        pChar[i] = c;
                    }
                }
                buf = buf + (nmemb * size);
                cur_buf_size = cur_buf_size - (size * nmemb);
                return nmemb2*size;
            }

            for (size_t i = 0; i < (nmemb * size); i++) { // copy data
                unsigned char c = (unsigned char) buf[i];
                if (c == ' ') {
                    pChar[i] = ' ';
                } else {
                    pChar[i] = c;
                }
            }
            buf = buf + (nmemb * size);
            cur_buf_size = cur_buf_size - (size * nmemb);
            return nmemb2*size;
        }
    } else { // if buffer is smaller than reuested data, then no need for buffering copy into the user buffer right-away
        bytes_read = read(this->fd_, ptr, nmemb * size);
        if (bytes_read < 0) {
            perror("Error Reading File");
            exit(1);
        }
        return bytes_read;
    }
    return bytes_read;
}

size_t File::fwrite(const void *ptr, size_t size, size_t nmemb) {

    if (this->file_access_mode == READING_ONLY) {
        this->err = true; // ser err flag if wrinting into a read only file
        throw "Writing in a read only file is not allowed!";
    }

    size_t bytes_written = 0;
    unsigned char* pChar;
    pChar = (unsigned char *) ptr;
    int flush;
    if (this->buf_state == READING) { //set buff state
        flush = this->fflush(); // make sure to empty the buffer before starting to write
        if (flush == 0) {
            cout << "Flush successful" << endl;
        } else {
            cout << "Nothing to flush" << endl;
        }
    }

    this->buf_state = WRITING;

    if (nmemb < bufsiz) {
        if (cur_buf_size == 0) {
            for (unsigned i = 0; i < nmemb; i++) { // if nbuffer size is 0 then just copy data into the buffer
                unsigned char c = (unsigned char) pChar[i];
                buf[i] = c;
            }
            cur_buf_size = nmemb; // buffer size will be equal to data reuested and returned
            buf = buf + nmemb;
            return nmemb;
        } else if (((unsigned) (bufsiz - cur_buf_size)) > nmemb) { // check if there is enough space in the buffer before copying into buf
            for (unsigned i = 0; i < nmemb; i++) {
                unsigned char c = (unsigned char) pChar[i];
                buf[i] = c;
            }
            cur_buf_size = cur_buf_size + nmemb;
            buf = buf + nmemb;
            return nmemb;
        } else if (((unsigned) (bufsiz - cur_buf_size)) < nmemb) { // if no space then write data to file and flush buffer
            buf = buf - cur_buf_size;
            bytes_written = write(this->fd_, (unsigned char *) this->buf, cur_buf_size);
            this->buf = (unsigned char*) malloc(bufsiz * sizeof (unsigned char));
            for (unsigned i = 0; i < nmemb; i++) { // copy new data into buffer
                char c = (char) pChar[i];
                buf[i] = c;
            }
            cur_buf_size = nmemb;
            buf = buf + nmemb;
            return nmemb;
        }
    } else { // if buffer size is too small then write directly into file
        bytes_written = write(this->fd_, ptr, nmemb);
        if (bytes_written < 0) {
            perror("Error Writing File");
            exit(1);
        }
        return bytes_written;
    }
    return bytes_written; // placeholder
}

int File::fgetc() {
    if (this->buf_state == WRITING && cur_buf_size > 0) {
        this->fflush(); /// flush if needed
    }
    int bytes;
    this->buf_state = READING; // set buffer state
    unsigned char *ubuf = new unsigned char[1];
    bytes = this->fread(ubuf, 1, 1); // use fread with size of 1 and chunk size 1
    if (bytes > 0) {
        return (int) ubuf[0]; // retunr the dec value of the char
    } else {// placeholder
        return -1;
    }
}

int File::fputc(int c) {
    if (this->buf_state == READING && cur_buf_size > 0) {
        this->fflush(); // flush if needed
    }
    int bytes = 0;
    this->buf_state = WRITING; // set buf state
    int chunk_size = 1;
    unsigned char ch = (unsigned char) c;
    unsigned char ubuf2[1] = {ch};
    unsigned char *ubuf = ubuf2;
    bytes = this->fwrite(ubuf, 1, chunk_size); // write into buffer size 1 and chunk size 1
    if (bytes == 1) {
        return c; // if data writeen successfuly .. return the int value of char written
    }
    return 0; // placeholder
}

char *File::fgets(char *s, int size) {
    int flush;
    if (this->buf_state == WRITING) {
        flush = this->fflush(); // make sure to empty the buffer before starting to read
        if (flush == 0) {
            cout << "Flush successful" << endl;
        } else {
            cout << "Nothing to flush" << endl;
        }
    }
    unsigned char * beginning = (unsigned char *) s;
    ssize_t chars_read;
    if (this->file_access_mode == WRITING_ONLY) {
        this->err = true; // set err if needed
    }
    for (int i = 0; i < size - 1; i++) { // read from 0 to size-2
        chars_read = read(this->fd_, s, 1);
        if (chars_read == 0) {
            *s = '\0'; // insert null bytes into string if End of String
            break;
        }
        if ((int) *s == 10) { // if new line then break 10 is equivalent to \n
            break;
        }
        s++; // increment the char pointer
    }
    return (char *) beginning; // placeholder
}

int File::fputs(const char *str) {

    int flush;
    if (this->buf_state == READING) {
        flush = this->fflush(); // make sure to empty the buffer before starting to write
        if (flush == 0) {
            cout << "Flush successful" << endl;
        } else {
            cout << "Nothing to flush" << endl;
        }
    }

    unsigned char * beginning = (unsigned char *) str;
    if (this->file_access_mode == READING_ONLY) {
        this->err = true; // set err if needed
        //exit(0);
    }
    int size = 0;
    while (true) { // loop to get the size of the string
        if (*str == '\0') {
            break;
        } else {
            size++;
        }
        str++;
    }
    ssize_t bytes_written;
    bytes_written = write(this->fd_, (unsigned char*) beginning, size); // write the string using the write and the size calculated

    return (int) bytes_written; // placeholder
}

int File::fseek(long offset, Whence whence) {
    off_t value = 0;
    if (whence == seek_set) {
        value = lseek(this->fd_, offset, SEEK_SET); // seek offset pointer after the pointer is set
    } else if (whence == seek_cur) {
        value = lseek(this->fd_, offset, SEEK_CUR); // seek offset pointer after the current pointer is set
    } else if (whence == seek_end) {
        value = lseek(this->fd_, offset, SEEK_END); // // seek offset pointer after the EOF pointer
    }
    return value; // placeholder
}


static const int ITOA_BUFSIZE = 32; // log10(2**64 < 21) + sign character

static char *itoa(int i, char a[ITOA_BUFSIZE]) {
    char * p = a + (ITOA_BUFSIZE - 1);
    *p = '\0'; // Trailing NUL byte: end-of-string.
    if (i == 0) {
        *--p = '0';
        return p;
    }
    bool negative = (i < 0);
    if (negative) {
        i = -i;
    }
    for (; i > 0; i = i / 10) {
        *--p = '0' + (i % 10);
    }
    if (negative) {
        *--p = '-';
    }
    return p;
}


// Stripped-down version: only implements %d, %s, and %% format codes.

int File::fprintf(const char *format, ...) {
    int n = 0; // Number of characters printed.
    va_list arg_list;
    va_start(arg_list, format);
    for (const char *p = format; *p != '\0'; p++) {
        if (*p != '%') {
            if (fputc(*p) < 0) {
                return -1;
            }
            n++;
            continue;
        }
        switch (*++p) {
            case 's':
            {
                char *s = va_arg(arg_list, char *);
                for (; *s != '\0'; s++) {
                    if (fputc(*s) < 0) {
                        return -1;
                    }
                    n++;
                }
            }
                break;
            case 'd':
            {
                int i = va_arg(arg_list, int);
                char sbuf[ITOA_BUFSIZE];
                char *s = itoa(i, sbuf);
                for (; *s != '\0'; s++) {
                    if (fputc(*s) < 0) {
                        return -1;
                    }
                    n++;
                }
            }
                break;
            default:
                if (fputc(*p) < 0) {
                    return -1;
                }
                n++;
        }
    }
    va_end(arg_list);
    return n;
}
