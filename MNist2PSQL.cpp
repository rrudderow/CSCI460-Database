#include <fstream>
#include <iostream>
#include <algorithm>
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

struct __attribute__((packed)) Image{
    //makes 2D array of image data
    //use to read one image at a time
    uint8_t data[28][28];
};

void swap4(uint8_t* p){
    swap(p[0], p[3]);
    swap(p[1], p[2]);
}

int main(int argc,char **argv){
    if(argc<2){
        cerr << "You need to pass the start of the MNist file name like 'train' or 't10k'" << endl;
        return -1;
    }
    // argv[1] == 'train' | 't10k'
    string idx1filename=string(argv[1])+"-labels.idx1-ubyte";
    string idx3filename=string(argv[1])+"-images.idx3-ubyte";
    cout << idx1filename << ' ' << idx3filename << endl;
    fstream idx1,idx3;
    idx1.open(idx1filename);
    idx3.open(idx3filename);

    HeaderIDX1 hidx1;
    HeaderIDX3 hidx3;
    idx1.read((char *)&hidx1,sizeof(HeaderIDX1));
    swap4((uint8_t*)&(hidx1.count));
    swap4((uint8_t*)&(hidx1.magic));

    idx3.read((char *)&hidx3,sizeof(HeaderIDX3));
    swap4((uint8_t*)&(hidx3.count));
    swap4((uint8_t*)&(hidx3.magic));
    swap4((uint8_t*)&(hidx3.rows));
    swap4((uint8_t*)&(hidx3.cols));

    cout << hidx1.magic << ' ' << hidx3.magic << endl;
    if(hidx1.magic==2049 && hidx3.magic==2051 && hidx1.count==hidx3.count){
        cout << "CREATE TABLE " << argv[1] << " (label char,image vector[" << hidx3.rows*hidx3.cols << "])" << endl;
        //insert into images (label,image) values ('0','[1,2,........3]'), ('1','[4,5,.........6]');
        cout << "insert into " << argv[1] << " (label,image) values ";
        for (int i=0;i<10/*hidx1.count*/;i++){
            Image img;
            uint8_t label;
            idx1.read((char *)&label,sizeof(uint8_t));
            idx3.read((char *)&img,sizeof(Image));

            // I have 1 image in img and its label in variable label
            //cout << (char)(label+'0') << ' ' << (int)label << endl;
            //cout << "insert into " << table << " (label,image) values ";

            cout << "('" << (char)(label+'0') << "','[";
            for(int r=0;r<hidx3.rows;r++){
                for (int c=0;c<hidx3.cols;c++){
                    if (r!=0 || c!=0) cout << ',';
                    cout << (int)img.data[r][c];
                }
            }
            cout << "]')" << endl;
        }
    } else {
        cerr << "Wrong file" << endl;
    }
    idx1.close();
    idx3.close();
    return 0;
}