#include <iostream>
#include <cstring>

using namespace std;
const int NAMELENGTH=20;
struct Node{
    bool used;
    char first[NAMELENGTH]; // Our value we are storing in the tree
    int left,right; // Position in array of next elements
//  Node *left,*right;
};
void nodePrint(Node &n){
  if (n.used) cout << "used ";
  else cout << "unused";
  cout << n.first << " l:"<< n.left << " r:"<< n.right << endl;
}

const int MAXNODES=10;
const int ROOTNODE=0;
const int NODENULL=0;
Node Nodes[MAXNODES];

void print(){
  for (int i=0;i<MAXNODES;i++) {
    cout << "Pos:" << i << " ";
    nodePrint(Nodes[i]);
  }
}

void init(){
    for (int i=0;i<MAXNODES;i++)
      Nodes[i].used=false;
}

int getNew(){
    for (int i=0;i<MAXNODES;i++)
      if (!Nodes[i].used) return i;
}

void inorderPrint(int current=ROOTNODE){
  //if (current==NODENULL) return;
  if (Nodes[current].left!=NODENULL)
    inorderPrint(Nodes[current].left);
  nodePrint(Nodes[current]);
  if (Nodes[current].right!=NODENULL)
    inorderPrint(Nodes[current].right);
}

void insert(char *Name,int current=ROOTNODE){
  if(!Nodes[current].used){
    // The node was empty
    strncpy(Nodes[current].first,Name,NAMELENGTH);
    Nodes[current].used=true;
    Nodes[current].left=NODENULL;
    Nodes[current].right=NODENULL;
  } else {  
    if (strcmp(Nodes[current].first,Name)>0) { // first<Name old C string
      if (Nodes[current].left==NODENULL) // There is a node to the left
        Nodes[current].left=getNew();
      insert(Name,Nodes[current].left);  // Recurse 
    } else if (strcmp(Nodes[current].first,Name)<0) { // first>Name  
      if (Nodes[current].right==NODENULL) // There is a node to the right
        Nodes[current].right=getNew();
      insert(Name,Nodes[current].right);
    }
  }
}

void removeNode(char *Name,int current=ROOTNODE){
    if (!Nodes[current].used) return;

    if (strcmp(Nodes[current].first,Name)>0) { // first<Name old C string
        if (Nodes[current].left!=NODENULL) 
          removeNode(Name,Nodes[current].left); 
    } else if (strcmp(Nodes[current].first,Name)<0) { // first>Name  
        if (Nodes[current].right!=NODENULL)
          removeNode(Name,Nodes[current].right);
    } else { // Found the node to remove
        if (Nodes[current].right==NODENULL) { // :-) keep the Nodes[current].left  
          int pos=Nodes[current].left;
          Nodes[current]=Nodes[pos];
          //Nodes[current].first=Nodes[pos].first;
          //Nodes[current].used=Nodes[pos].used;
          //...
          Nodes[pos].used=false;
        }
        else if (Nodes[current].left==NODENULL) { // :-) keep the Nodes[current].right
          int pos=Nodes[current].right;
          Nodes[current]=Nodes[pos];
          Nodes[pos].used=false;
        }
        else {  // :-( because we need to keep both sub-trees
          int leftPos=Nodes[current].left;
          int pos=Nodes[current].right;
          Nodes[current]=Nodes[pos];
          Nodes[pos].used=false;
          //insertLeft(current,leftPos); // Castleton skips recursion
          while (Nodes[current].left!=NODENULL) current=Nodes[current].left;
          Nodes[current].left=leftPos;
        }
    }
}

int main(int argc,char **argv){
  insert("Karl");
  insert("Kim");
  insert("Betty");
  insert("Zak");
  insert("Karla");
  cout << "Before"<< endl;
  print();
  cout << "In Order"<< endl;
  inorderPrint();
  removeNode("Karl");
  cout << "After"<< endl;
  print();
  cout << "In Order"<< endl;
  inorderPrint();
  return 0;
}




