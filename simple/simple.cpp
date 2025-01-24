#include <iostream>
#include <cstring>
using namespace std;

/*
void badFunction() {
    int *p=(int*)10;
    //you don't have permission to talk to memory location 10
    *p=20;
}*/

void badFunction() {
    char *p=(char*)10;
    sprintf(p, "Hello CSCI 460\n");
}

int main(){
    badFunction();
    cout << "Hello World" << endl;
    return 0;
}