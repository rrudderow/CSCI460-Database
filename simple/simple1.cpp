#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class Data {
    public:
    long b;
    double a;
    void write(ostream &out, long pos){
        //seekp = seek to put at position
        out.seekp(pos);
        out.write((char *)this, sizeof(Data));
    }
    void read(ifstream &in, long pos){

    }
    friend ostream & operator <<(ostream &out, Data &item){
        return out << "a: " << item.a << ", b: " << item.b << endl;
    }
};

int main() {
    Data d, e;
    d.a=-1.0;
    d.b=-1;
    ofstream fout;
    ifstream fin;
    fout.open("Data.bin");
    d.write(fout,0);
    fout.close();
    fin.open("Data.bin");
    e.read(fin,0);
    cout << e << endl;
    fin.close();
    return 0;
}