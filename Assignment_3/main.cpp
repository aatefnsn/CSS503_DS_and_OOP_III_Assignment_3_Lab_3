/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: ahmed_nada
 *
 * Created on May 24, 2019, 12:37 AM
 */

#include <cstdlib>
#include "file.h"

using namespace std;

/*
 *
 */
int main(int argc, char** argv) {
    size_t bytes;
    size_t total_bytes_read = 0;
    const char *name = "Ahmed.txt";
    int chunk_size = 5;
    unsigned char *ubuf = new unsigned char[chunk_size];
    const char * mode = "r";
    File * f = new File(name, mode);
    //******************************** WRITEEEEEEEEEEEEEEEEEEEE first ******
    while (true) {
        bytes = f->fread(ubuf, 1, chunk_size);
        //cout << bytes << endl;
        if (bytes < 0) {
            perror("Error Reading File");
            exit(1);
        }
        if (bytes == 0) {
            cout << "Total Bytes Read is: " << total_bytes_read << endl;
            total_bytes_read=0;
            break;
        } else {
                cout << ubuf;
            cout << endl;
        }
        total_bytes_read = total_bytes_read + bytes;
    }


    ubuf = new unsigned char[chunk_size];
    cout << "Testing Reading and Writing" << endl;
    const char *name2 = "Ahmed-write.txt";
    int chunk_size2 = 9;
    unsigned char ubuf2[] = "ABCDEFGHI";
    //unsigned char *ubuf2 = ubuf22;
    const char * mode2 = "r+";
    File * f2 = new File(name2, mode2);
    //f2->fwrite(ubuf2, 1 ,chunk_size2);

    f2->fread(ubuf, 1, 3); // fread will perform the flush
    cout << ubuf << endl;

    unsigned char ubuf33[] = "XYZ";

    f2->fwrite(ubuf33, 1, 3); // fread will perform the flush
    cout << ubuf << endl;

    ubuf = new unsigned char[chunk_size];
    f2->fread(ubuf, 1, 3); // fread will perform the flush
    cout << ubuf << endl;

    //unsigned char ubuf3[] = "XYZ";
    //ubuf2 = ubuf23;
    //f2->fwrite(ubuf3, 1 ,chunk_size2); // expected output is that it will write the strings into buffer but not into the file
    //f2->fflush(); // after calling flush, the strings will be written to file

    //f2->fread(ubuf, 1, 10); // fread will perform the flush
    //cout << ubuf << endl;

    //unsigned char ubuf44[] = " Testing after write --> read --> write";
    //ubuf2 = ubuf23;
    //f2->fwrite(ubuf44, 1 ,chunk_size2);
    //cout << ubuf44 << endl;
    //f2->fflush();

  int fgetcval;
  /*int fputval;
  const char *name3 = "Ahmed-fgetc.txt";
  const char * mode3 = "r+";
  File * f3 = new File(name3, mode3);
  fgetcval = f3->fgetc();
  cout << "****fgetc return is " << fgetcval << endl;
  fgetcval = f3->fgetc();
  cout << "*****fgetc return is " << fgetcval << endl;

  fputval = f3->fputc(68);
  cout << "--------------fputc return is " << fputval <<  endl;

  fputval = f3->fputc(69);
  cout << "----------fputc return is " << fputval <<  endl;

  fgetcval = f3->fgetc();
  cout << "*****fgetc return is " << fgetcval << endl;

  fputval = f3->fputc(70);
  cout << "***********fputc return is " << fputval <<  endl;

  fputval = f3->fputc(71);
  cout << "*****fputc return is " << fputval <<  endl;

  fgetcval = f3->fgetc();
  cout << "*****fgetc return is " << fgetcval << endl;

  fgetcval = f3->fgetc();
  cout << "fgetc return is " << fgetcval << endl;
  fgetcval = f3->fgetc();
  cout << "fgetc return is " << fgetcval << endl;
  fgetcval = f3->fgetc();
  cout << "fgetc return is " << fgetcval << endl;*/

total_bytes_read = 0;
int chunk_size4 = 1024;
const char *name4 = "20190211_070835.jpg";
const char * mode4 = "r";
File * f4 = new File(name4, mode4);
unsigned char *ubuf4 = new unsigned char[chunk_size4];

while (true) {
    bytes = f4->fread(ubuf4, 1, chunk_size4);
    //cout << bytes << endl;
    if (bytes < 0) {
        perror("Error Reading File");
        exit(1);
    }
    if (bytes == 0) {
      //lseek(f4->fd_, 1 , SEEK_CUR);
    //  bytes = f4->fread(ubuf4, 1, chunk_size4);
      //if (bytes == 0) {
        cout << "Total Bytes Read is: " << total_bytes_read << endl;
        total_bytes_read=0;
        break;
    //  }
    } else {
        for (int i = bytes-1; i < bytes; i++) {
            //cout << (ubuf4[i]);
        }
        //cout << endl;
    }
    total_bytes_read = total_bytes_read + bytes;
}

total_bytes_read = 0;
//int chunk_size4 = 1024;
const char *name5 = "20190211_070835.jpg";
const char * mode5 = "r";
File * f5 = new File(name5, mode5);
//int a;
//unsigned char *ubuf5 = new unsigned char[chunk_size4];
while (true) {
                f5->fgetc();
                //if (bytes_read == EOF) {
                if (f5->feof()) {
                    break;
                }
                total_bytes_read++;
            }
cout << "fgetc Total Bytes Read is: " << total_bytes_read << endl;

const char *name6 = "Ahmed-fgetc.txt";
const char * mode6 = "r+";
File * f6 = new File(name6, mode6);

if( !f6->ferror() ) {
      printf("No Error yet for file : Ahmed-fgetc.txt\n");
   }

fgetcval = f6->fputc(46);

if( f6->ferror() ) {
      printf("Error writing into file : Ahmed-fgetc.txt\n");
   }

   const char *name7 = "Ahmed-fgets.txt";
   const char * mode7 = "r";
   int read_size=10;
   File * f7 = new File(name7, mode7);
    char * result = new char [read_size];
    f7->fgets(result,read_size);
    cout << result;
  //for (int i =0; i< read_size; i++){
    //cout << result[i];
  //}
  //cout << endl;

  const char *name8 = "Ahmed-fputs.txt";
  const char * mode8 = "w+";
  File * f8 = new File(name8, mode8);
  const char test[] = "I love CSS-503";
  char * result2 = new char [read_size];
  int b=0;
  b = f8->fputs(test);
  cout << "bytes written are " << b << endl;
  f8->fgets(result2,read_size);
  cout << "Test" << endl;
  cout << result2;


  const char *name9 = "Test.txt";
  const char * mode9 = "w+";
  File * f9 = new File(name9, mode9);
  const char test2[] = "I love CSS-503";


  const char *name10 = "Test2.txt";
  const char * mode10 = "w";
  File * f10 = new File(name10, mode10);
  //int chunk_size10 = 10;
  //unsigned char ubuf10[] = "A";
  unsigned char *ubuf10 = new unsigned char[10];
  //unsigned char *ubuf2 = ubuf22;
  //f2->fwrite(ubuf2, 1 ,chunk_size2);
  try{
  f10->fread(ubuf10, 1, 3); // fread will perform the flush
}catch(const char * e ) {
  cout << e << endl;
}
return 0;
}
//printf("\tbytes read: %d\n", total_bytes_read);
