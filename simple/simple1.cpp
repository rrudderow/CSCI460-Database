#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
/*
ostream & operator <<(ostream &out, bool &b){
    if(b) return out << "True";
    else return out << "False";
}*/

class __attribute__ ((packed)) Data {
    public:
    int b;
    double a;
    bool c;
    void write(ostream &out, long pos){
        //seekp = seek to put some stuff at position(in bytes)
        out.seekp(pos*sizeof(Data));
        out.write((char *)this, sizeof(Data));
    }
    void read(ifstream &in, long pos){
        //seekg = seek to get some stuff from given position(in bytes)
        in.seekg(pos*sizeof(Data));
        in.read((char *)this, sizeof(Data));
    }
    friend ostream & operator <<(ostream &out, Data &item){
        out << "a: " << item.a << ", b: " << item.b << ", c: ";
        if(item.c) out << "True" << endl;
        else out << "False" << endl;
        return out;
    }
};

int main() {
    Data d, e;
    d.a=-1.0;
    d.b=-1;
    d.c=true;
    ofstream fout;
    ifstream fin;
    fout.open("Data.bin");
    d.write(fout,0);
    d.b+=2;
    d.a+=2;
    d.c=true;

    d.write(fout,4);
    //second parameters of write() is block - 
        //must read out same block you wrote to to get same value

    fout.close();
    fin.open("Data.bin");
    e.read(fin,4);
    cout << e << endl;
    fin.close();
    return 0;
}