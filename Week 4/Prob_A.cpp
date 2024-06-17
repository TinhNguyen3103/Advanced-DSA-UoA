// #include <iostream>
#include <bits/stdc++.h>
using namespace std;

// class Node
// {
// public:
//     int key;
//     int pri;
//     Node *left;
//     Node *right;
//     Node(int key_, int pri_){
//         this->key = key_;
//         this->pri = pri_;
//         this->left = NULL;
//         this->right = NULL;
//     }
// };

struct Node {
    int key;
    int pri;
    Node *left, *right;
};
 
// Utility function to create a new tree node
Node* newNode(int key_, int pri_)
{
    Node* temp = new Node;
    temp->key = key_;
    temp->pri = pri_;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

class Balanced_Tree {
public:
    Node* rightRotate(Node *t) {
        Node *s = t->left;
        t->left = s->right;
        s->right = t;
        return s;
    }

    Node* leftRotate(Node *t) {
        Node *s = t->right;
        t->right = s->left;
        s->left = t;
        return s;
    }

    Node* insert(Node *t, int key, int pri){
        if (t == NULL){
            return newNode(key, pri);
        }
        if (key == t->key)
            return t;
        if (key < t->key){
            t->left = insert(t->left, key, pri);
            if (t->pri < t->left->pri)
                t = rightRotate(t);
        } else {
            t->right = insert(t->right, key, pri);
            if (t->pri < t->right->pri)
                t = leftRotate(t);
        }

        return t;
    }

    Node* erase(Node *t, int key){
        if (t == NULL)
            return NULL;
        if (key == t->key){
            if (t->left == NULL && t->right == NULL)
                return NULL;
            else if (t->left == NULL)
                t = leftRotate(t);
            else if (t->right == NULL)
                t = rightRotate(t);
            else {
                if (t->left->pri > t->right->pri)
                    t = rightRotate(t);
                else    
                    t = leftRotate(t);
            }

            return erase(t, key);
        }
        if (key < t->key)
            t->left = erase(t->left, key);
        else 
            t->right = erase(t->right, key);
        
        return t;
    }

    void inOrder(Node* node) {
        if (node == NULL)
            return;
        inOrder(node->left);

        cout << " " << node->key;

        inOrder(node->right);
    }

    void preOrder(Node* node){
        if (node == NULL)
            return;
        cout << " " << node ->key;

        preOrder(node->left);
        preOrder(node->right);
    }

    Node* find(Node* t, int key){
        if (t == NULL)
            return NULL;
        if (key == t->key)
            return t;
        else if (key < t->key){
            Node *node = find(t->left, key);
            return node;
        } else {    
            Node *node = find(t->right, key);
            return node;
        }
    }
};

int main(){
    int m;
    std::cin >> m;

    Balanced_Tree BT;

    Node* root = NULL;

    string quer;
    int k, p;
    for(int j=0; j<m; j++){
        std::cin >> quer;
        if (quer == "insert"){
            std::cin >> k >> p;
            root = BT.insert(root, k, p);
        } 
        if (quer == "find"){
            std::cin >> k;
            Node *node = BT.find(root, k);
            if (node == NULL)
                cout << "no" << endl;
            else
                cout << "yes" << endl;
        } 
        if (quer == "delete"){
            std::cin >> k;
            root = BT.erase(root, k);
        } 
        if (quer == "print"){
            BT.inOrder(root);
            cout << endl;
            BT.preOrder(root);
            cout << endl;
        } 
    }
    return 0;
}