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
        out.write(reinterpret_cast<char *>(this), sizeof(Data));
        out.flush();
    }
    void read(ifstream &in, long pos){
        //seekg = seek to get some stuff from given position(in bytes)
        in.seekg(pos*sizeof(Data));
        in.read(reinterpret_cast<char *>(this), sizeof(Data));
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

    ofstream fout;
    ifstream fin;
    fout.open("Data.bin");
    fin.open("Data.bin");

    d.a=-1.0;
    d.b=-1;
    d.c=true;

    d.write(fout,0);
    //need a flush here to make sure data makes it to disk before you read
    //otherwise computer will wait to write until convenient and info will not be there when you read
    e.read(fin,0);
    cout << e;

    d.b+=2;
    d.a+=2;
    d.c=true;

    d.write(fout,4);
    //second parameters of write() is block - 
        //must read out same block you wrote to to get same value

    fout.close();
    fin.close();
    return 0;
}