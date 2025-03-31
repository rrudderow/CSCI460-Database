#include <iostream>
using namespace std;
const int NAMELENGTH=20;
struct Node{
    bool used;
    char first[NAMELENGTH]; //value storing in binary tree
    int left,right; //position in array of next elements
//  Node *left,*right;
};

const int MAXMODES=1000;
const int ROOTNODE=0;
const int NODENULL=0;
Node Nodes[MAXNODES];

void init(){
    for(int i=0;i<MAXNODES;i++){
        Nodes[i].used=false;
    }
}

int getNew(){
    for(int i=0;i<MAXNODES;i++){
        if (!Nodes[i].used) return i;
    }
}

void insert(char *Name,int current=ROOTNODE){
    if(!Nodes[current].used){
        strncpy(Nodes[current].first,Name,NAMELENGTH);
        Nodes[current].used=true;
        Nodes[current].left=NODENULL;
        Nodes[current].right=NODENULL;
    }else {
        if(strcmp(Nodes[current].first,Name)<0) { //First < Name
            if(Nodes[current].left==NODENULL){
                //find a free node if one does not exist
                Nodes[current].left=getNew();
            } //then always will recurse
            insert(Name,Nodes[current].left);
        } else if (strcmp(Nodes[current].first,Name)>0) { //first > Name
            if (Nodes[current].right==NODENULL){
                //find a free node if one does not exist
                Nodes[current].right=getNew();
            } //then always will recurse
            insert(Name,Nodes[current].right);
        }
    }
}

void remove(char *Name,int current=ROOTNODE){
    if(!Nodes[current].used) return;
    if(strcmp(Nodes[current].first,Name)<0) { //First < Name
        if(Nodes[current].left!=NODENULL)
            remove(Name,Nodes[current].left);
    } else if (strcmp(Nodes[current].first,Name)>0) { //first > Name
        if(Nodes[current].right!=NODENULL)
            remove(Name,Nodes[current].right);
    } else { //found the node to remove
        if (Nodes[current].right==NODENULL) //happy
            int pos=Nodes[current].left;
            Nodes[current]=Nodes[pos];
            Nodes[pos].used=false;
        else if (Nodes[current].left==NODENULL) //happy
            int pos=Nodes[current].right;
            Nodes[current]=Nodes[pos];
            Nodes[pos].used=false;
        else { //sad bc work

        }
        Nodes[current].used=false;
    }
}

int main(){
    init();
    return 0;
}