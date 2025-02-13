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
    friend ostream & operator <<(ostream &out, DataItems &item){
        out << "a: " << item.a << ", b: " << item.b << ", c: ";
        if(item.c) out << "True" << endl;
        else out << "False" << endl;
        return out;
    }
};

union DataList{
    //union takes up the same memory location - variables are laying on top of each other
    //struct makes a memory pattern of the variables, so variables are one right after the otehr
    //class = struct with members that are functions
        DataItems data;
        long next;
        //null pointer = 0 and can never access
    };

const int MAXBYTES=32;
const long FILENULL=0;
class __attribute__ ((packed)) Data {
    //attributes(packed) makes it so only use as many bytes as you need - instead of 8 bytes for everything
    public:
    DataList dataList;
    bool used;
    //true if memory block is being used from data
    //use to determine if using dataitems or the next
    //look at it as only one of the two

    //assumes size of dataitems is larger than long
    char gap[MAXBYTES-sizeof(DataItems)-1];
    //maxbytes minus size of union minus one for used bool
    //min and max are macros

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
        out.flush(); 
        //need a flush here to make sure data makes it to disk before you read
        //otherwise computer will wait to write until convenient and info will not be there when you read
        //makes computer write to file immediately - instead of waiting
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
        d.write(fout,FILENULL,false);
        fout.close();
    }

    static long dataNew(istream &in){
        long n=getSize(in);
        //this for loop makes big O of n time, but if use linked list would be constant time
        for(long i=0;i<n;i++){
            Data d;
            d.read(in,i);
            if(d.used==false) return i;
        }
        return n;
    }

    static void dataDelete(ostream &out,long pos){
        //doesn't actually delete - just marks space as avaliable for something else
        //probably add to linked list here - mark as unused - move info to head?
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
    //constructor should open database file and keep the file handle for us
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
        //returning something that is on stack - so may not return properly
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
    //first parameter of write() is memory block - 
    //must read out same block you wrote to to get same value

    e=db.read(1);
    cout << e;

    d.a+=2;
    d.b+=2;
    d.c=true;

    db.write(3,d);
    cout << db.getSize() << endl;
    db.dataDelete(1);
    //so now dataNew will return pos one - or whatever is passed into dataDelete bc mem now avaliable
    long pos=db.dataNew();
    cout << "Pos of new element: " << pos << endl;

    return 0;
}