#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class Data {
    public:
    long b;
    double a;
};

int main() {
    Data d;
    d.a=-1.0;
    d.b=-1;
    ofstream fout;
    fout.open("Data.bin");
    fout.write((char *)&d,sizeof(Data));
    fout.close();
    return 0;
}