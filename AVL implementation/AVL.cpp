#include "AVL.h"
#include <iostream>
using namespace std;

AVL::Node::Node() : key(0), height(1), left(nullptr), right(nullptr) {}

AVL::Node::~Node() {
    LetFree(this);
}

AVL::Node* AVL::Node::insertion(Node* node, int& value) {
    if (node == nullptr) {
        node = new Node();
        node->key = value;
        return node;
    }
    if (node->key > value) {
        node->left = insertion(node->left, value);
    } else {
        node->right = insertion(node->right, value);
    }
    
    node->height = 1 + max(Height(node->left), Height(node->right));
    node = Balance(node);
    return node;
}


AVL::Node* AVL::Node::remove(Node* node, int& value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (value < node->key)
        return remove(node->left, value);
    else if (value > node->key)
        return remove(node->right, value);

    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        return nullptr;
    }
    if (node->left == nullptr) {
        Node* temp = node->right;
        node->right = nullptr;
        delete node;
        return temp;
    } else if (node->right == nullptr) {
        Node* temp = node->left;
        node->left = nullptr;
        delete node;
        return temp;
    } else {
        Node* temp = Min(node->right);
        node->key = temp->key;
        node->right = remove(node->right, temp->key);
        return node;
    }
    node->height = 1 + max(Height(node->left), Height(node->right));
    
    return node;
}

AVL::Node* AVL::Node::search(Node* node, int& value) {
    if (node == nullptr || node->key == value) {
        return node;
    }
    if (value < node->key) {
        return search(node->left, value);
    } else {
        return search(node->right, value);
    }
}

void AVL::Node::InOrderPrint(Node* node) {
    if (node == nullptr) {
        return;
    }
    InOrderPrint(node->left);
    cout << node->key << " ";
    InOrderPrint(node->right);
}

void AVL::Node::LetFree(Node* node) {
    if (node == nullptr) {
        return;
    }
    LetFree(node->left);
    LetFree(node->right);
}

int AVL::Node::Height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

AVL::Node* AVL::Node::RightRotate(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = 1 + max(Height(node->left), Height(node->right));
    temp->height = 1 + max(Height(temp->left), Height(temp->right));
    return temp;
}

AVL::Node* AVL::Node::LeftRotate(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = 1 + max(Height(node->left), Height(node->right));
    temp->height = 1 + max(Height(temp->left), Height(temp->right));
    return temp;
}

AVL::Node* AVL::Node::Min(Node* node) {
    if (node->left == nullptr) {
        return node;
    }
    return Min(node->left);
}

//Declare BalaceFactor

AVL::Node* AVL::Node::Balance(Node* node) {
    if (node == nullptr) {
        return node;
    }
    if (BalanceFactor(node) > 1) {
        if (BalanceFactor(node->left) < 0) {
            node->left = LeftRotate(node->left);
        }
        node = RightRotate(node);
    } else if (BalanceFactor(node) < -1) {
        if (BalanceFactor(node->right) > 0) {
            node->right = RightRotate(node->right);
        }
        node = LeftRotate(node);
    }
    return node;
}

int AVL::Node::BalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return Height(node->left) - Height(node->right);
}

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    delete root;
}

void AVL::insertion(int value) {
    root = root->insertion(root, value);
}

void AVL::remove(int value) {
    root = root->remove(root, value);
}

bool AVL::search(int value) {
    return root->search(root, value) != nullptr;
}

void AVL::InOrderWalk() {
    root->InOrderPrint(root);
    cout << endl;
}

int main() {
    AVL tree;

    // Caso de prueba 1: Inserción y recorrido en orden
    tree.insertion(10);
    tree.insertion(20);
    tree.insertion(30);
    tree.insertion(15);
    tree.insertion(5);

    std::cout << "In Order Walk after insertions: ";
    tree.InOrderWalk();
    std::cout << std::endl;

    // Caso de prueba 2: Eliminación y recorrido en orden
    tree.remove(20);
    tree.remove(10);

    std::cout << "In Order Walk after removals: ";
    tree.InOrderWalk();
    std::cout << std::endl;

    // Caso de prueba 3: Búsqueda
    int searchValue = 15;
    std::cout << "Search for " << searchValue << ": " << (tree.search(searchValue) ? "Found" : "Not Found") << std::endl;

    return 0;
}