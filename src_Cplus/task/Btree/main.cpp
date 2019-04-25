#include "BP_tree.h"

using namespace std;

int main(int argc, char **argv){

    BPTree* sBPT = new BPTree;
    BPTree* bBPT = new BPTree;
    ifstream sIfs, bIfs;
    string sBuf;

    sIfs.open(argv[1]);
    bIfs.open(argv[2]);


    cout << endl << "Singly insert" << endl;

    while(getline(sIfs, sBuf)){
        if(stoi(sBuf.substr(0,1)) == 0){
            sBPT->insert_data(stoi(sBuf.substr(2)));
        }
        else{
            sBPT->insert_data(sBuf.substr(2));
        }
    }

    cout << endl << "Traverse" << endl;
    sBPT->traverse();

    cout << endl << "Hierarchical print" << endl;
    sBPT->h_print(sBPT->get_root());

    cout << endl << "Bulk loading" << endl;
    bBPT->bulk_loading(&bIfs);

    cout << endl << "Traverse" << endl;
    bBPT->traverse();

    cout << endl << "Hierarchical print" << endl;
    bBPT->h_print(bBPT->get_root());

    delete sBPT;
    delete bBPT;


    return 0;
}
