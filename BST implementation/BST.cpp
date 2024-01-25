#include "BST.h"


BST::Node* BST::Node::Min(Node* node) {
    if (node->left == nullptr) {
        return node;
    }
    return Min(node->left);
}

BST::Node* BST::Node::Max(Node *node){
    if (node->left == nullptr) {
        return node;
    }
    return Min(node->right);
}

BST::Node* BST::Node::search(Node *node, int &value){
    if(node->key == value || node == nullptr){
        return node;
    }
    if(value < node->key){
        return search(node->left, value);
    }
    else{
        return search(node->right, value);
        
    }
    
};

BST::Node* BST::Node::insertion(Node *node, int &value){
    if(node == nullptr){
        node = new Node();
        node->key = value;
        return node;
    }
    if(node->key > value){
        node->left = insertion(node->left, value);
    }
    else{
        node->right = insertion(node->right, value);
    }
    return node;

};

BST::Node* BST::Node::remove(Node *node,     int &value){
    if(node == nullptr){
        return nullptr;
    }
    if(value < node->key)
        return remove(node->left, value);
    else if(value > node->key)
        return remove(node->right, value);

    if(node->left == nullptr && node->right == nullptr){
        Node* temp = new Node();
        temp->key = node->key;
        delete node;
        return temp;
    }
    if (node->left == nullptr) {
        Node* temp = node->right;
        Node* output = new Node();
        output->key = node->key;
        delete node;
        node = temp;
        return output;
    }
    else if (node->right == nullptr) {
        Node* temp = node->left;
        Node* output = new Node();
        output->key = node->key;
        delete node;
        node = temp;
        return output;
    }
    else {
        Node* temp = node->right;
        Node* Parent_temp = node;
        while(temp->left != nullptr){
            Parent_temp = temp;
            temp = temp->left;
        }

        Node* output = new Node();
        output->key = node->key;
        node->key = temp->key;

        if(Parent_temp != node){
            Parent_temp->left = temp->right;
        }else{
            node->right = nullptr;
        }
        temp->right = nullptr;

        delete temp;
        
        return output;
    } 
};

void BST::Node::InOrderPrint(Node *node){
    if (node != nullptr) {
        InOrderPrint(node->left);
        cout << node->key << " ";
        InOrderPrint(node->right);
    }
}
void BST::Node::LetFree(Node *node){
    if (node == nullptr) 
        return;
    LetFree(node->left);
    LetFree(node->right);
    delete node;
    node = nullptr;
}

bool BST:: search(int value){
    Node* node = root->search(root, value);
    if(node == nullptr){
        cout << "elemento no encontrado" << endl;
        return false;    
    }
    else{
        cout << "elemento "<< node->key <<" encontrado" << endl;
        return true;    
    }
}
void BST::insertion(int value){
    if (root == nullptr){
        root = new Node();
        root->key = value;
        cout << "elemento " << value << " insertado" << endl;
    } else {
        Node* insertedNode = root->insertion(root, value);
        cout << "elemento " << value << " insertado" << endl;
    }
}
void BST:: remove(int value){
    Node* node = root->remove(root, value); 
    if(node == nullptr)
        cout << "elemento no encontrado" << endl;
    else
        cout << "eliminado el elemento " << node->key << endl;
    delete node;
}

void BST:: InOrderWalk(){
    root->InOrderPrint(root);
}
int main() {
    BST tree;

    // Caso de prueba 1: Inserción
    tree.insertion(5);
    tree.insertion(3);
    tree.insertion(7);
    tree.insertion(2);
    tree.insertion(4);
    tree.insertion(6);
    tree.insertion(8);

    
    // Caso de prueba 2: Impresión en orden
    cout << "In Order Walk: ";
    tree.InOrderWalk();
    cout << endl;

    // Caso de prueba 3: Búsqueda
    int searchValue = 4;
    cout << "Search for " << searchValue << ": " << (tree.search(searchValue) ? "Found" : "Not Found") << endl;

    // Caso de prueba 4: Eliminación
    int removeValue = 3;
    tree.remove(removeValue);

    // Caso de prueba 5: Impresión en orden después de la eliminación
    cout << "In Order Walk after removing " << removeValue << ": ";
    tree.InOrderWalk();
    cout << endl;

    return 0;
}
