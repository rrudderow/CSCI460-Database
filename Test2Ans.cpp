// Struct D
// Still need some way to know whether a record is used or not

struct Record {
    D data;
    bool used;
};

iostream &open(string filename){
    iostream io;
    io.open(filename);
    return io;
}

void close(iostream &io){
    io.close();
}

Record read(iostream &io,Record &r,long pos){
    io.seekg(pos*sizeof(Record));
    io.read((char *)&r, sizeof(Record));
}

void write(iostream &io,const Record &r,long pos){
    io.seekp(pos*sizeof(Record));
    io.write((char *)&r,sizeof(Record));
    io.flush();
}