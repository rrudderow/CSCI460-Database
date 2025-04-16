#include <fstream>
#include <iostream>
using namespace std;

struct __attribute__((packed)) HeaderIDX1{
    //packed overwrites compilers default 64 bit in and out of disk
    int32_t magic;
    int32_t count;
};

struct __attribute__((packed)) HeaderIDX3{
    //packed overwrites compilers default 64 bit in and out of disk
    int32_t magic;
    int32_t count;
    int32_t rows;
    int32_t cols;
};

struct __sttribute__((packed)) Image{
    //makes 2D array of image data
    //use to read one image at a time
    uint8_t data[28][28];
}

int main(int argc,char **argv){
    if(argc<2){
        cerr << "You need to pass the start of the MNist file name like 'train' or 't10k'" << endl;
        return -1;
    }
    // argv[1] == 'train' | 't10k'
    string idx1filename=string(argv[1])+"-labels.idx1-ubyte";
    string idx3filename=string(argv[1])+"-images.idx3-ubyte";
    fstring idx1,idx3;
    idx1.open(idx1filename);
    idx3.open(idx3filename);

    HeaderIDX1 hidx1;
    HeaderIDX3 hidx3;
    idx1.read(&hidx1,sizeof(HeaderIDX1));
    idx3.read(&hidx3,sizeof(HeaderIDX3));

    if((hidx1.magic!=2049 || hidx3.magic!=2051) && hidx1.count==hidx3.count){
        for (int 1=0;i<hidx1.count;i++){
            Image img;
            uint8_t label;
            idx1.read(&label.sizeof(uint8_t));
            idx3.read(&img,sizeof(Image));
            // I have 1 image in img and its label in variable label
        }
    } else {
        cerr << "Wrong file" << endl;
    }


    idx1.close();
    idx3.close();
    return 0;
}