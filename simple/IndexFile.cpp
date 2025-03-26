#include <iostream>
#include <fstream>

using namespace std;

struct LLNode {
    bool used;
    long next;
}

struct IndexDataNode {
    bool used;
    long left,right; //this is the position in the indexfile of the left and right nodes
    long datapos; //position in the data file
    char first[20];
}

union IndexBlock {
    LLNode ll;
    IndexDataNode data;
}

int main(){


    return 0;
}