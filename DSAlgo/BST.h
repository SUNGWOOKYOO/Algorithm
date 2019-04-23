#include <iostream>

using namespace std;

template <class T>
class BSTNode
{
    public:
        BSTNode();
        ~BSTNode();
        BSTNode(T data);
        void print();

        T data;
        BSTNode* left;
        BSTNode* right;

};

template <class T>
class BST
{
    public:
        BST();
        ~BST();

        BSTNode<T>* find(T data);

        void insertion(T data)
        {
            insertion_slave(data, root);
        }

        void deletion(T data)
        {
            deletion_slave(data, root);
        }

        void print_inorder()
        {
            cout << "PRINTING TREE" << endl;
            print_slave(root);
            cout << endl << endl;
        }

    private:
        BSTNode<T>* find_slave(T data, BSTNode<T>* node);
        BSTNode<T>* findmin(BSTNode<T>* node);
        BSTNode<T>* findmax(BSTNode<T>* node);
        BSTNode<T>* insertion_slave(T data, BSTNode<T>* &node);
        BSTNode<T>* deletion_slave(T data, BSTNode<T>* node);
        void print_slave(BSTNode<T>* node);
        void dtor_slave(BSTNode<T>* node);
        BSTNode<T>* root;
};

template <class T>
BSTNode<T>::BSTNode(){
    data = -1.0;
    left = NULL;
    right = NULL;
}

template <class T>
BSTNode<T>::~BSTNode(){
    left = NULL;
    right = NULL;
}

template <class T>
BSTNode<T>::BSTNode(T data) : data(data), left(NULL), right(NULL){

}

template <class T>
void BSTNode<T>::print(){
    cout << data << " ";
}

template <class T>
BST<T>::BST(){
    root = NULL;
}

template <class T>
BST<T>::~BST(){
    dtor_slave(root);
}

template <class T>
BSTNode<T>* BST<T>::find(T data){
    return find_slave(data, root);
}

template <class T>
BSTNode<T>* BST<T>::find_slave(T data, BSTNode<T>* node){
    if (node == NULL){
        return NULL;
    }
    if (data < node->data){
        return find_slave(data, node->left);
    } else if (data > node->data){
        return find_slave(data, node->right);
    } else {
        return node;
    }
}

template <class T>
BSTNode<T>* BST<T>::findmin(BSTNode<T>* node){
    if (node == NULL){
        return NULL;
    } else if (node->left == NULL){
        return node;
    } else {
        return findmin(node->left);
    }
}

template <class T>
BSTNode<T>* BST<T>::findmax(BSTNode<T>* node){
    if (node == NULL){
        return NULL;
    } else if (node->right == NULL){
        return node;
    } else {
        return findmax(node->left);
    }
}

template <class T>
BSTNode<T>* BST<T>::insertion_slave(T data, BSTNode<T>* &node){
    if (node == NULL){
        node = new BSTNode<T>(data);
    } else if (data < node->data){
        node->left = insertion_slave(data, node->left);
    } else if (data > node->data){
        node->right = insertion_slave(data, node->right);
    } else {
        cout<<"data alread exists!"<<endl;
    }
    return node;
}

template <class T>
BSTNode<T>* BST<T>::deletion_slave(T data, BSTNode<T>* node){
    BSTNode<T>* tmp;
    if (node == NULL){
        cout<<"Element not found"<<endl;
    } else if (data < node->data){
        node->left = deletion_slave(data, node->left);
    } else if (data > node->data){
        node->right = deletion_slave(data, node->right);
    } else if (node->left && node->right){
        tmp = findmin(node->right);
        node->data = tmp->data;
        node->right = deletion_slave(node->data, node->right);
    } else {
        tmp = node;
        if(node->left!=NULL){
            node = node->left;
        } else if (node->right!=NULL){
            node = node->right;
        } else {
            node = NULL;
        }
        delete tmp;
    }
    return node;
}

template <class T>
void BST<T>::print_slave(BSTNode<T>* node){
    if (node != NULL){
        if (node->left != NULL){
            print_slave(node->left);
        }
        cout<<node->data<<'\t';
        if (node->right != NULL){
            print_slave(node->right);
        }
    }
}

template <class T>
void BST<T>::dtor_slave(BSTNode<T>* node){
    if (node!=NULL){
        if (node->left != NULL){
            dtor_slave(node->left);
        }
        if (node->right != NULL){
            dtor_slave(node->right);
        }
        delete node;
    }
}
