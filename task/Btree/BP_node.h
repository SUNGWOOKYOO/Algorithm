#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define CAPACITY    5
#define LEAF        1
#define NONLEAF     0
#define FULL        1
#define UNFULL      0
#define EMPTY       1
#define NOTEMPTY    0
#define BULK        1
#define SINGLY      0
#define IMED        1
#define SMED        0

class BPNode{
    public:
        // member variables
        void** data;
        BPNode** childPtr;
        BPNode* parentPtr;
        bool isLeaf;
        int num;
        int numInteger;

        // constructor & destructor
        BPNode();
        ~BPNode();

        // member functions
        bool is_leaf();
        void set_leaf(bool isLeaf);
        bool is_full();
        bool is_empty();
        void print();
};

BPNode::BPNode(){
    data = new void*[CAPACITY];
    childPtr = new BPNode*[CAPACITY+1];
    parentPtr = NULL;
    isLeaf = LEAF;
    num = 0;
    numInteger = 0;
    for(int i = 0; i < CAPACITY + 1; ++i){
        childPtr[i] = NULL;
    }
}

BPNode::~BPNode(){
    // TODO
}

bool BPNode::is_leaf(){
    return isLeaf;
}

void BPNode::set_leaf(bool isLeaf){
    this->isLeaf = isLeaf;
}

bool BPNode::is_full(){
    if(num == CAPACITY) return FULL;
    else                return UNFULL;
}

bool BPNode::is_empty(){
    if(num == 0)    return EMPTY;
    else            return NOTEMPTY;
}

void BPNode::print(){
    cout<<" |";
    for(int i = 0; i < numInteger; i++){
      cout<<(*(int*)data[i])<<" ";
    }
    for(int i = numInteger; i < num; i++){
      cout<<(*(string*)data[i]).c_str()<<" ";
    }
    cout<<"| ";
}
