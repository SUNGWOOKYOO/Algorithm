#include <string>
#include <cstring>
#include <fstream>
#include <queue>
#include "BP_node.h"

using namespace std;

class BPTree{
    public:
        // member variables
        BPNode* root;

        // constructor & destructor
        BPTree();
        ~BPTree();

        //member functions
        void insert_data(int i_data);
        void insert_data(string s_data);
        void bulk_loading(ifstream* ifs);
        void traverse();

        BPNode* split_node(BPNode* node, bool insert_type, int i_data);
        BPNode* split_node(BPNode* node, bool insert_type, string s_data);
        void h_print(BPNode* BPN);
        BPNode* get_root();
};

BPTree::BPTree(){
    root = new BPNode();
}

BPTree::~BPTree(){
    // TODO
}

void BPTree::insert_data(int i_data){
    BPNode* BPN = root;

    // traverse to proper leaf node
    while(BPN->is_leaf() == NONLEAF){
        bool determined = 0;
        for(int i = 0; i < BPN->numInteger; ++i){
            if(i_data < *(int*)(BPN->data[i])){
                BPN = BPN->childPtr[i];
                determined = 1;
                break;
            }
        }
        if(determined == 0){
            BPN = BPN->childPtr[BPN->numInteger];
            determined == 1;
        }
    }

    // initial insert
    if(BPN == root && BPN->is_empty() == EMPTY){
        BPN->data[0] = new int(i_data);
        (BPN->num)++;
        (BPN->numInteger)++;
        return;
    }

    // not an initial insert
    if(BPN->is_full() == UNFULL){
        // insert data with comparison
        // compare int in range (0, numInteger-1)
        bool inserted = 0;
        /*
           TODO
        */
    }
    else{
        // if the node is full
        split_node(BPN, SINGLY, i_data);
    }
}

void BPTree::insert_data(string s_data){
    BPNode* BPN = root;

    // traverse to proper leaf node
    while(BPN->is_leaf() == NONLEAF){
        bool determined = 0;
        for(int i = BPN->numInteger; i < BPN->num; ++i){
            if(strcmp(s_data.c_str(), (*(string*)(BPN->data[i])).c_str()) < 0){
                BPN = BPN->childPtr[i];
                determined = 1;
                break;
            }
        }
        if(determined == 0){
            BPN = BPN->childPtr[BPN->num];
            determined == 1;
        }
    }

    // initial insert
    if(BPN == root && BPN->is_empty() == EMPTY){
        BPN->data[0] = new string(s_data);
        (BPN->num)++;
        return;
    }

    // not an initial insert
    if(BPN->is_full() == UNFULL){
        // insert data with comparison
        // compare string in range (numInteger, num)
        bool inserted = 0;
        /*
           TODO
        */
    }
    else{
        // if the node is full
        split_node(BPN, SINGLY, s_data);
    }
}

void BPTree::bulk_loading(ifstream* ifs){
    BPNode* BPN = root;
    int numInt = 0;
    int numTotal = 0;
    int rowCount = 0;
    string sBuf;

    // traverse to proper leaf node
    while(BPN->is_leaf() == NONLEAF){
        BPN = BPN->childPtr[BPN->num];
    }

    while(getline(*ifs, sBuf)){
        if(rowCount == 0){
            numInt = stoi(sBuf);
            rowCount++;
        }
        else if(rowCount == 1){
            numTotal = stoi(sBuf);
            rowCount++;
        }
        else{
            if(numInt > 0){
                // insert int data
                numInt--;
                if(BPN->is_full() == UNFULL){
                    BPN->data[BPN->num] = new int(stoi(sBuf));
                    (BPN->num)++;
                    (BPN->numInteger)++;
                }
                else{
                    split_node(BPN, BULK, stoi(sBuf));

                    // traver again to proper leaf node
                    BPN = root;
                    while(BPN->is_leaf() == NONLEAF){
                        BPN = BPN->childPtr[BPN->num];
                    }
                }
            }
            else{
                // insert string data
                if(BPN->is_full() == UNFULL){
                    BPN->data[BPN->num] = new string(sBuf);
                    (BPN->num)++;
                }
                else{
                    split_node(BPN, BULK, sBuf);

                    // traver again to proper leaf node
                    BPN = root;
                    while(BPN->is_leaf() == NONLEAF){
                        BPN = BPN->childPtr[BPN->num];
                    }
                }
            }
        }
    }

}

BPNode* BPTree::split_node(BPNode* node, bool insert_type, int i_data){
    // CASE : inserted data is "INTEGER TYPE"

    BPNode* sNode = new BPNode();       // generated node while splitting
    BPNode* pNode = node->parentPtr;    // parent node of the node will be splitted
    int i_med;          // integer type median
    string s_med;       // string type median
    bool medType = 0;   // 1 for int, o for string

    // generated node and splitted node are same leaf or not
    sNode->set_leaf(node->is_leaf());

    // split_node called by singly insert_node
    // split node 3/3
    if(insert_type == SINGLY){
        if(node->numInteger < 3){
            // median will be string
            // s_data must be in node
            medType = SMED;

            // move data[2-4] of node to data[0-2] of sNode
            // remove data[2-4] of node by decrease num of node
            // set s_med with data[0] of sNode
            /*
               TODO
            */

            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                }
                (sNode->num)--;
            }

            // insert i_data to node
            /*
               TODO
            */
        }
        else{
            // median will be integer
            medType = IMED;

            // find the position of i_data
            int newPos = 0;
            bool determined = 0;
            for(int i = 0; i < node->numInteger; ++i){
                if(i_data < *(int*)(node->data[i])){
                    newPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                newPos = node->numInteger;
                determined = 1;
            }

            // case 1 : i_data remains on node
            if(newPos < 3){
                // move data[2-4] of node to data[0-2] of sNode
                // remove data[2-4] of node by decrease num of node
                // set i_med
                /*
                   TODO
                 */

                //insert i_data to node
                /*
                   TODO
                 */
            }
            // case 2 : i_data moves to sNode
            else{
                // move data[3-4] of node to data[0-1] of sNode
                // remove data[3-4] of node by decrease num of node
                /*
                   TODO
                 */

                //insert i_data to sNode
                //set i_med
                /*
                   TODO
                 */
            }

            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                }
                (sNode->num)--;
                (sNode->numInteger)--;
            }
        }

        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            int medPos = 0;     // position that median will be inserted
            bool determined = 0;
            for(int i = 0; i < pNode->num; ++i){
                if(pNode->childPtr[i] == node){
                    medPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                medPos = pNode->num;
                determined = 1;
            }

            for(int i = pNode->num; i > medPos; --i){
                pNode->childPtr[i+1] = pNode->childPtr[i];
                pNode->data[i] = pNode->data[i-1];
            }
            pNode->childPtr[medPos+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[medPos] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[medPos] = new string(s_med);
            }
            (pNode->num)++;
            pNode->set_leaf(NONLEAF);
        }
        else{
            // if parent node does "NOT" have room for a new data
            // recursively split the parent node
            if(medType == IMED){
                // TODO
            }
            else{
                // TODO
            }
        }
    }
    // split_node called by bulk_loading
    // split node 4/2
    // i_data is always inserted to sNode;
    else{
        // move data[4] of node to data[0] of sNode
        // remove data[4] of node by decrease num of node
        // set i_med
        sNode->data[0] = node->data[4];
        (node->num)--;
        (sNode->num)++;
        if(node->numInteger >= CAPACITY-1){
            // median will be integer
            medType = IMED;
            (node->numInteger)--;
            (sNode->numInteger)++;
            i_med = *(int*)(sNode->data[0]);
        }
        else{
            // median will be string
            medType = SMED;
            s_med = *(string*)(sNode->data[0]);
        }
        // insert i_data to sNode;
        // i_data is always inserted at the end
        sNode->data[sNode->num] = new int(i_data);
        (sNode->num)++;
        (sNode->numInteger)++;

        // if splitted node is "not a leaf node"
        if(node->is_leaf() == NONLEAF){
            sNode->data[0] = sNode->data[1];
            (sNode->num)--;
            (sNode->numInteger)--;
            sNode->childPtr[0] = node->childPtr[5];
            node->childPtr[5] = NULL;
        }

        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            pNode->childPtr[pNode->num+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[pNode->num] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[pNode->num] = new string(s_med);
            }
            (pNode->num)++;
            pNode->set_leaf(NONLEAF);
        }
        else{
            // if parent node does "NOT" have room for a new data
            if(medType == IMED){
                // TODO
            }
            else{
                // TODO
            }
        }
    }

    if(node->is_leaf() == LEAF){
        sNode->childPtr[CAPACITY] = node->childPtr[CAPACITY];
        node->childPtr[CAPACITY] = sNode;
    }
    return sNode;
}

BPNode* BPTree::split_node(BPNode* node, bool insert_type, string s_data){
    // CASE : inserted data is "VARCHAR(STRING) TYPE"

    BPNode* sNode = new BPNode();       // generated node while splitting
    BPNode* pNode = node->parentPtr;    // parent node of the node will be splitted
    int i_med;          // integer type median
    string s_med;       // string type median
    bool medType = 0;   // 1 for int, o for string

    // generated node and splitted node are same leaf or not
    sNode->set_leaf(node->is_leaf());

    // split_node called by singly insert_node
    // split node 3/3
    if(insert_type == SINGLY){
        if(node->numInteger < 4){
            // median will be string
            medType = SMED;

            //find the position of s_data
            int newPos = node->numInteger;
            bool determined = 0;
            for(int i = node->numInteger; i < node->num; ++i){
                if(strcmp(s_data.c_str(), (*(string*)(node->data[i])).c_str()) < 0){
                    newPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                newPos = node->num;
                determined = 1;
            }

            // case 1 : s_data reamins on node
            if(newPos < 3){
                // move data[2-4] of node to data[0-2] of sNode
                // remove data[2-4] of node by decrease num of node
                // set s_med
                /*
                   TODO
                */
            }
            // case 2 : s_data moves to sNode
            else{
                // move data[3-4] of node to data[0-1] of sNode
                // remove data[3-4] of node by decrease num of node
                /*
                   TODO
                */

                //insert s_data to sNode
                //set s_med
                /*
                   TODO
                */
            }

            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                }
                (sNode->num)--;
            }
        }
        else{
            // median will be integer
            // s_data must be in sNode
            medType = IMED;

            // move data[3-4] of node to data[0-1] of sNode
            // remove data[3-4] of node by decrease num of node
            // set i_med
            for(int i = 0; i < 2; ++i){
                sNode->data[i] = node->data[i+3];
                (sNode->num)++;
            }
            sNode->numInteger = node->numInteger - 3;
            node->num = 3;
            node->numInteger = 3;
            i_med = *(int*)(sNode->data[0]);

            // if splitted node is "not a leaf node"
            if(node->is_leaf() == NONLEAF){
                // delete median from sNode
                // copy child pointer from node to sNode
                for(int i = 0; i < sNode->num-1; ++i){
                    sNode->data[i] = sNode->data[i+1];
                    sNode->childPtr[i] = node->childPtr[i+4];
                    node->childPtr[i+4] = NULL;
                }
                (sNode->num)--;
                (sNode->numInteger)--;
            }

            // insert s_data to sNode
            bool inserted = 0;
            /*
               TODO
             */
        }

        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            int medPos = 0;     // position that median will be inserted
            bool determined = 0;
            for(int i = 0; i < pNode->num; ++i){
                if(pNode->childPtr[i] == node){
                    medPos = i;
                    determined = 1;
                    break;
                }
            }
            if(determined == 0){
                medPos = pNode->num;
                determined = 1;
            }

            for(int i = pNode->num; i > medPos; --i){
                pNode->childPtr[i+1] = pNode->childPtr[i];
                pNode->data[i] = pNode->data[i-1];
            }
            pNode->childPtr[medPos+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[medPos] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[medPos] = new string(s_med);
            }
            (pNode->num)++;
        }
        else{
            // if parent node does "NOT" have room for a new data
            if(medType == IMED){
                // TODO
            }
            else{
                // TODO
            }
        }
    }
    // split_node called by bulk_loading
    // split node 4/2
    else{
        // move data[4] of node to data[0] of sNode
        // remove data[4] of node by decrease num of node
        // set i_med
        sNode->data[0] = node->data[4];
        (node->num)--;
        (sNode->num)++;
        if(node->numInteger >= CAPACITY-1){
            // median will be integer
            medType = IMED;
            (node->numInteger)--;
            (sNode->numInteger)++;
            i_med = *(int*)(sNode->data[0]);
        }
        else{
            // median will be string
            medType = SMED;
            s_med = *(string*)(sNode->data[0]);
        }

        // insert i_data to sNode;
        // s_data is always inserted at the end
        sNode->data[sNode->num] = new string(s_data);
        (sNode->num)++;

        // if splitted node is "not a leaf node"
        if(node->is_leaf() == NONLEAF){
            sNode->data[0] = sNode->data[1];
            (sNode->num)--;
            sNode->numInteger = 0;
            sNode->childPtr[0] = node->childPtr[5];
            node->childPtr[5] = NULL;
        }

        // add median and pointer to sNode to parent node
        if(pNode == NULL){
            // if splitted node is the root
            // make a empty node and link it to parent pointer of node
            root = new BPNode();
            if(medType == IMED){
                root->data[0] = new int(i_med);
                (root->numInteger)++;
            }
            else{
                root->data[0] = new string(s_med);
            }
            (root->num)++;
            root->childPtr[0] = node;
            root->childPtr[1] = sNode;
            node->parentPtr = root;
            sNode->parentPtr = root;
            root->set_leaf(NONLEAF);
        }
        else if(pNode->is_full() == UNFULL){
            // if parent node has room for a new data
            pNode->childPtr[pNode->num+1] = sNode;
            sNode->parentPtr = pNode;
            if(medType == IMED){
                pNode->data[pNode->num] = new int(i_med);
                (pNode->numInteger)++;
            }
            else{
                pNode->data[pNode->num] = new string(s_med);
            }
            (pNode->num)++;
            pNode->set_leaf(NONLEAF);
        }
        else{
            // if parent node does "NOT" have room for a new data
            if(medType == IMED){
                // TODO
            }
            else{
                // TODO
            }
        }
    }

    if(node->is_leaf() == LEAF){
        sNode->childPtr[CAPACITY] = node->childPtr[CAPACITY];
        node->childPtr[CAPACITY] = sNode;
    }
    return sNode;;
}

void BPTree::traverse(){
    BPNode* BPN = root;
    // TODO
}

void BPTree::h_print(BPNode* BPN){
    if(BPN == NULL) return;
    queue<BPNode*> q;
    q.push(BPN);
    while(q.empty() == false){
      int nodeCount = q.size();
      while(nodeCount > 0){
        BPNode* node = q.front();
        node->print();
        q.pop();
        int i = 0;
        //if(node->is_leaf() == NONLEAF){
        //for(int i = 0; i < node->num + 1; ++i){
        while(node->childPtr[i] != NULL){
            q.push(node->childPtr[i]);
            i++;
        }
        //}
        nodeCount--;
      }
      cout<<endl;
    }
}

BPNode* BPTree::get_root(){
    return root;
}
