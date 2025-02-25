#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class __attribute__ ((packed)) DataItems{
    public:
    int b;
    double a;
    bool c;

    friend ostream & operator <<(ostream &out, DataItems &item){
        out << "a: " << item.a << ", b: " << item.b << ", c: ";
        if(item.c) out << "True" << endl;
        else out << "False" << endl;
        return out;
    }
};

union DataList{ //this will act as Node
        DataItems data;
        long next;
    };

const int MAXBYTES=32;
const long FILENULL=0;

class __attribute__ ((packed)) Data {

    public:
    DataList dataList;
    bool used;
    char gap[MAXBYTES-sizeof(DataItems)-1];

    Data(DataItems &d) {
        dataList.data=d;
    }
    Data() {
        used=false;
        dataList.next=FILENULL;
    }


    friend ostream & operator <<(ostream &out, Data &item){
        if(item.used)
            out << "Data Node: " << item.dataList.data << endl;
        else
            out << "Link List Node: " << item.dataList.next << endl;
        return out;
    }

    static long getSize(istream &in){
        in.seekg(0,ios_base::end);
        return in.tellg()/sizeof(Data)-1;

    }
    void write(ostream &out, long pos, bool setUsed=true){
        out.seekp(pos*sizeof(Data));
        if(setUsed) used=true;
        out.write(reinterpret_cast<char *>(this), sizeof(Data));
        out.flush(); 
    }

    void read(istream &in, long pos){
        in.seekg(pos*sizeof(Data));
        in.read(reinterpret_cast<char *>(this), sizeof(Data));
    }

    static void createDB(string fname){
        Data d;
        d.used=false;
        d.dataList.next=FILENULL;
        ofstream fout;
        fout.open(fname);
        d.write(fout,FILENULL,false);
        fout.close();
    }

    static long dataNew(istream &in){
        long n=getSize(in);
        for(long i=0;i<n;i++){
            Data d;
            d.read(in,i);
            if(d.used==false) return i;
        }
        return n;
    }

    static void dataDelete(ostream &out,long pos){
        Data d;
        d.used=false;
        d.write(out,pos,false);
    }
};

class Database{
    public:
    fstream file;
    static void createDB(string fname){
        Data::createDB(fname);
    }
    long getSize() {
        return Data::getSize(file);
    }
    Database(string fname){
        ifstream test;
        test.open(fname);
        if(!test.good())
            Database::createDB(fname);
        else
            test.close();
        file.open(fname);
    }
    void write(long pos,DataItems &d){
        Data(d).write(file,pos,true);
    }
    DataItems read(long pos){
        Data d;
        d.read(file,pos);
        return d.dataList.data;
    }
    void dataDelete(long pos){
        Data::dataDelete(file,pos);
    }
    long dataNew(){
        return Data::dataNew(file);
    }
    ~Database(){
        file.flush();
        file.close();
    }
};

int main() {
    DataItems d,e;
    Database db("Data.bin");

    d.a=-1.0;
    d.b=-1;
    d.c=true;
    db.write(1,d);

    e=db.read(1);
    cout << e;

    d.a+=2;
    d.b+=2;
    d.c=true;

    db.write(3,d);
    cout << db.getSize() << endl;
    db.dataDelete(1);
    long pos=db.dataNew();
    cout << "Pos of new element: " << pos << endl;

    return 0;
}