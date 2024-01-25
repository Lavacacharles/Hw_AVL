// AVL.h

#ifndef AVL_H
#define AVL_H

class AVL {
public:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node();
        ~Node();
        Node* insertion(Node* node, int& value);
        Node* remove(Node* node, int& value);
        Node* search(Node* node, int& value);
        void InOrderPrint(Node* node);
        void LetFree(Node* node);
        int Height(Node* node);
        Node* RightRotate(Node* node);
        Node* LeftRotate(Node* node);
        Node* Min(Node* node);
        Node* Balance(Node* node);
        int BalanceFactor(Node* node);
    };

    Node* root;

    AVL();
    ~AVL();
    void insertion(int value);
    void remove(int value);
    bool search(int value);
    void InOrderWalk();
};

#endif // AVL_H
