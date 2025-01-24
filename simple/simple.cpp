#include <iostream>
#include <cstring>
using namespace std;

/*
void badFunction() {
    int *p=(int*)10;
    //you don't have permission to talk to memory location 10
    *p=20;
}

void badFunction() {
    char *p=(char*)10;
    sprintf(p, "Hello CSCI 460\n");
}*/

struct data {
    //reserves memory for all of the following for each instance of data
    //K.a, K.b, and K.c all have different memory addresses - sequential
    int a;
    float b;
    bool c;
};

enum Types {Cat,Dog,Mouse};
//enum is an int type - make different types of ints
    //Cat=0, Dog=1, Mouse=2 - or can set yourself

union data2 {
    int a;
    float b;
    bool c;
};

data2 J;
//J.a J.b and J.c all have the same memory address
//as much memory as the biggest of a b c - not all combined

union dataBlock {
    data d;
    char a[sixeof(d)];
};

dataBlock L;
/*
L.d.a -> will get to element a of a data
L.d.b -> will get to float
L.a -> is an array of chars suitable for sending to another location or for writing to a file, etc.
char array and data structure in one
*/

struct E1{
    float a;
    int b;
};

struct E2{
    int b;
    float a;
};

union Both {
    E1 e1;
    E2 e2;
};

Both b;

int main(){
    badFunction();
    cout << "Hello World" << endl;
    return 0;
}