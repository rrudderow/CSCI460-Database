#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Node {
    int data;  
    Node* next; 
};

class LinkedList {
    Node* head; //pointer to the first node
    public:
    LinkedList() {
        head = nullptr;
    }

    void insertLL(int value) {
        Node* newNode = new Node(); 
        newNode->data = value;      
        newNode->next = head;      
        head = newNode;            
    }

    void insertAll(long n) {
        for (int i = 1; i <= n; ++i) {
            insertLL(i);
        }
    }

    int getFirst() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return -1;  // Returning -1 to indicate that the list is empty
    }
    return head->data;
    }

    void deleteLL() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head; 
        head = head->next; 
        delete temp;      
    }

    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> "; 
            temp = temp->next;
        }
        cout << "NULL" << endl; 
    }
};


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

union DataList{
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
        // long n=getSize(in);
        // for(long i=0;i<n;i++){
        //     Data d;
        //     d.read(in,i);
        //     if(d.used==false) return i;
        // }
         return -2;
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
    LinkedList ll;
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
        ll.insertAll(getSize());
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
        ll.insertLL(pos);
    }
    long dataNew(){
        int n = ll.getFirst();
        ll.deleteLL();
        return n;
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
    //so now dataNew will return pos one - or whatever is passed into dataDelete bc mem now avaliable
    long pos=db.dataNew();
    cout << "Pos of new element: " << pos << endl;

    return 0;
}
