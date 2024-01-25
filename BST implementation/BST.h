#include <iostream>

using namespace std;

class BST{
private:
    struct Node{
        int key;
        Node *right;
        Node *left;
        Node(): key(-1), right(nullptr), left(nullptr){}

        Node* insertion(Node*, int &);
        Node* remove(Node*, int &);
        Node* search(Node*, int &);
        Node* Min(Node* node);
        Node* Max(Node* node);
        void InOrderPrint(Node*);
        void LetFree(Node*);
    };
    Node *root;

public:


    BST(): root(nullptr){}
    ~BST(){
        root->LetFree(root);
        root = nullptr;
    }
    Node* getRoot(){
        return root;
    }
    void insertion(int);
    void remove(int);
    bool search(int);
    void InOrderWalk();  
};