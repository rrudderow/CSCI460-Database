#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
/*
ostream & operator <<(ostream &out, bool &b){
    if(b) return out << "True";
    else return out << "False";
}*/

class __attribute__ ((packed)) DataItems{
    public:
    int b;
    double a;
    bool c;
    // char first[20];
    // char last[20];
    // char address[100];
    friend ostream & operator <<(ostream &out, Data &item){
        out << "a: " << item.a << ", b: " << item.b << ", c: ";
        if(item.c) out << "True" << endl;
        else out << "False" << endl;
        return out;
    }
};

const int MAXBYTES=32;
const long FILENULL=0;
class __attribute__ ((packed)) Data {
    //attributes(packed) makes it so only use as many bytes as you need - instead of 8 bytes for everything
    public:
    union dataList{
    //union takes up the same memory location - variables are laying on top of each other
    //struct makes a memory pattern of the variables, so variables are one right after the otehr
    //class = struct with members that are functions
        DataItems data;
        long next;
        //null pointer = 0 and can never access
    }
    bool used;
    //true if memory block is being used fro data
    //use to determine if using dataitems or the next
    //look at it as only one of the two

    //assumes size of dataitems is larger than long
    char gap[MAXBYTES-sizeof(DataItems)-1];
    //maxbytes minus size of union minus one for used bool
    //min and max are macros


    friend ostream & operator <<(ostream &out, Data &item){
        if(item.used)
            out << "Data Node: " << item.dataList.data << endl;
        else
            out << "Link List Node: " << item.dataList.next << endl;
        return out;
    }

    static long getSize(istream &in){
        //bc static use Data::getSize() instead of d.getSize() - use class name as this pointer
        in.seekg(0,ios_base::end);
        return in.tellg()/sizeof(Data)-1;
        //subtract one bc first memory location for linked list

    }
    void write(ostream &out, long pos, bool setUsed=true){
        //seekp = seek to put some stuff at position(in bytes)
        out.seekp(pos*sizeof(Data));
        if(setUsed) used=true;
        out.write(reinterpret_cast<char *>(this), sizeof(Data));
        out.flush(); //makes computer write to file immediately - instead of waiting
        //otherwise won't flush until after newline char so need space between write and read
    }

    void read(istream &in, long pos){
        //seekg = seek to get some stuff from given position(in bytes)
        in.seekg(pos*sizeof(Data));
        in.read(reinterpret_cast<char *>(this), sizeof(Data));
    }

    static void createDB(string fname){
        //file location zero should not be used for data - just for linked list
        Data d;
        d.used=false;
        d.dataList.next=FILENULL;
        ofstream fout;
        fout.open(fname);
        write(fout,FILENULL,false);
        fout.close();
    }

    static long dataNew(istream &in){
        long n=getSize(in);
        //this for loop makes On, but if use linked list would be constant time
        for(long i=0;i<n;i++){
            Data d;
            d.read(in,i);
            if(d.used==false) return i;
        }
        return n;
    }

    static void dataDelete(ostream &out,long pos){
        //doesn't actually delete - just marks space as avaliable for something else
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
    //constructor should open database file and keep the file handle for us
    Database(string fname){
        file.open(fname);
    }
    void write(long pos,Data d){
        d.write(file,pos,true);
    }
    Data read(long pos){
        Data d;
        d.read(file,pos);
        return d;
    }
    ~Database(){
        file.flush();
        file.close();
    }
};

int main() {
    Data d, e;

    ofstream fout;
    ifstream fin;
    fout.open("Data.bin");
    fin.open("Data.bin");

    d.data.a=-1.0;
    d.data.b=-1;
    d.data.c=true;

    d.write(fout,0);
    //need a flush here to make sure data makes it to disk before you read
    //otherwise computer will wait to write until convenient and info will not be there when you read
    e.read(fin,0);
    cout << e;

    d.data.b+=2;
    d.data.a+=2;
    d.data.c=true;

    cout << Data::getSize(fin) << endl;
    d.write(fout,4);
    //second parameters of write() is block - 
        //must read out same block you wrote to to get same value
    cout << Data::getSize(fin) << endl;
    Data::dataDelete(fout,0);
    long pos=Data::dataNew(fin);
    cout << "pos: " << pos << endl;

    fout.close();
    fin.close();
    return 0;
}